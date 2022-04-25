#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "hashmap.h"

int get_new_nonce_map_index(nonce_manager_t *mgr, unsigned int nonce)
{
    if (mgr->nonces + 1 >= NONCE_MAX_COUNT || nonce == NONCE_MAP_GRAVE_MARKER || nonce == 0) {
        return -1;
    }

    int i = nonce % NONCE_MAP_SIZE;
    for (; mgr->nonce_map[i] != 0; i = (i + 1) % NONCE_MAP_SIZE) {
        if (mgr->nonce_map[i] == nonce) {
            return -1;
        }
    }

    return i;
}

int get_nonce_map_index(nonce_manager_t *mgr, unsigned int nonce)
{
    for (int i = nonce % NONCE_MAP_SIZE; 1; i = (i + 1) % NONCE_MAP_SIZE) {
        if (mgr->nonce_map[i] == nonce) {
            return i;
        }

        if (mgr->nonce_map[i] == 0) {
            return -1;
        }
    }

    return -1;
}

status_t nonce_map_recompute(nonce_manager_t *mgr)
{
    memset(mgr->nonce_map, 0, sizeof(* mgr->nonce_map) * NONCE_MAP_SIZE);
    int tmp = mgr->nonces;
    mgr->nonces = 0; // Override the length check

    // All nonces in the queue are placed in the new map
    for (int i = mgr->front_ptr; i != mgr->back_ptr; i = (i + 1) % NONCE_MAX_COUNT) {
        int index = get_new_nonce_map_index(mgr, mgr->nonce_queue[i].nonce);
        if (index == -1) {
            fprintf(stderr, "Internal logical state of nonce manager is corrupt\n");
        } else {
            mgr->nonce_map[index] = mgr->nonce_queue[i].nonce;
        }
    }

    mgr->nonces = tmp; // Replace the length

    return SUCCESS;
}

static void *nonce_manager_poll_thread(void *mgr_in)
{
    nonce_manager_t *mgr = (nonce_manager_t *) mgr_in;
    for (;;) {
        // Invalidate old nonces
        long ct = time(NULL);
        int recomp = mgr->front_ptr != mgr->back_ptr;
        for (int i = mgr->front_ptr; i != mgr->back_ptr; i = (i + 1) % NONCE_MAX_COUNT) {
            if (ct - mgr->nonce_queue[i].issue_time >= NONCE_TIMEOUT_S) {
                mgr->front_ptr = (mgr->front_ptr + 1) % NONCE_MAX_COUNT;
                mgr->nonces--;
            } else {
                break;
            }
        }

        // Recompute map if nonces were removed
        if (recomp) {
            nonce_map_recompute(mgr);
        }
        usleep(NONCE_POLL_TIME_MS * 1000);
    }
}

status_t init_nonce_manager(nonce_manager_t *nonce_mgr)
{
    memset(nonce_mgr, 0, sizeof * nonce_mgr);

    nonce_mgr->nonce_map = malloc(NONCE_MAP_SIZE * sizeof * nonce_mgr->nonce_map);
    if (nonce_mgr->nonce_map == NULL)	{
        fprintf(stderr, "Cannot assign memory\n");
        free_nonce_manager(nonce_mgr);
        return FAIL;
    }

    nonce_mgr->nonce_queue = malloc(NONCE_MAX_COUNT * sizeof * nonce_mgr->nonce_queue);
    if (nonce_mgr->nonce_queue == NULL) {
        fprintf(stderr, "Cannot assign memory\n");
        free_nonce_manager(nonce_mgr);
        return FAIL;
    }

    nonce_mgr->nonces = 0;
    return SUCCESS;
}

void free_nonce_manager(nonce_manager_t *nonce_mgr)
{
    // Free the memory
    if (nonce_mgr->nonce_map != NULL) {
        free(nonce_mgr->nonce_map);
    }

    if (nonce_mgr->nonce_queue != NULL) {
        free(nonce_mgr->nonce_queue);
    }
}

status_t get_nonce(nonce_manager_t *mgr, unsigned int *ret)
{
    status_t status = SUCCESS;
    int cont = 1;
    unsigned int nonce;
    while (cont) {
        nonce = rand();

        if (mgr->nonces + 1 >= NONCE_MAX_COUNT) {
            cont = 0;
            status = FAIL;
        } else {
            int index = get_new_nonce_map_index(mgr, nonce);
            if (index != -1) {
                cont = 0;
                mgr->nonces++;
                mgr->nonce_map[index] = nonce;
                mgr->nonce_queue[mgr->back_ptr].nonce = nonce;
                mgr->nonce_queue[mgr->back_ptr].issue_time = time(NULL);
                mgr->back_ptr = (mgr->back_ptr + 1) % NONCE_MAX_COUNT;
                *ret = nonce;
            }
        }
    }

    return status;
}

status_t use_nonce(nonce_manager_t *mgr, unsigned int nonce)
{
    // FAIL early
    if (nonce == 0 || nonce == NONCE_MAP_GRAVE_MARKER) {
        return FAIL;
    }

    status_t status;
    int index = get_nonce_map_index(mgr, nonce);
    if (index == -1) {
        status = FAIL;
    } else {
        status = SUCCESS;
        mgr->nonce_map[index] = NONCE_MAP_GRAVE_MARKER;
        mgr->nonces--;
    }

    return status;
}

int main()
{
    nonce_manager_t mgr;
    init_nonce_manager(&mgr);
    for (int i = 0; i < 100; i++) {
        int ret;
        get_nonce(&mgr, &ret);
    }
    nonce_manager_poll_thread((void *) &mgr);
    free_nonce_manager(&mgr);
}

