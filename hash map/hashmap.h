#pragma once

#define NONCE_MULT 30
#define NONCE_BASE 4096
#define NONCE_MAP_SIZE (NONCE_BASE * NONCE_MULT)
#define NONCE_MAX_COUNT NONCE_BASE
#define NONCE_TIMEOUT_S 10
#define NONCE_POLL_TIME_MS 10
#define NONCE_MAP_GRAVE_MARKER 1

typedef struct nonce_t {
    long issue_time;
    unsigned int nonce;
} nonce_t;
typedef enum status_t {SUCCESS = 1, FAIL = 0} status_t;
typedef struct nonce_manager_t {
    int front_ptr, back_ptr, nonces;
    nonce_t *nonce_queue;
    unsigned int *nonce_map;
} nonce_manager_t;

status_t init_nonce_manager(nonce_manager_t *nonce_mgr);
void free_nonce_manager(nonce_manager_t *nonce_mgr);
status_t get_nonce(nonce_manager_t *nonce_mgr, unsigned int *ret);
status_t use_nonce(nonce_manager_t *mgr, unsigned int nonce);

// Internal logical functions exposed for testing.
int get_new_nonce_map_index(nonce_manager_t *mgr, unsigned int nonce); // not thread safe
int get_nonce_map_index(nonce_manager_t *mgr, unsigned int nonce);     // not thread safe

