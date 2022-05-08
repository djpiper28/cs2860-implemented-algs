#include <stdio.h>
#include <stdlib.h>

void shuffle(int *arr, int pos, int length) {
  for (int i = length - 1; i > pos; i--) {
    arr[i] = arr[i - 1];
  }
}

void insertion_sort_in_place(int *arr, size_t length) {
    int i, key, j;
    for (i = 1; i < length; i++) {
        key = arr[i];
        j = i - 1;
 
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// This is not in place.
void insertion_sort(int *arr, size_t length) {
  int *out = malloc(sizeof(int) * length);
  size_t end_len = 1;
  out[0] = arr[0];

  for (int i = 1; i < length; i++) {
    int inserted = 0;
    for (int j = 0; j < end_len && !inserted; j++) {
      if (arr[i] < out[j]) {
        shuffle(out, j, ++end_len);
        out[j] = arr[i];
        inserted = 1;
      }
    }

    if (!inserted) {
      out[end_len++] = arr[i];
    }
  }

  for (int i = 0; i < length; i ++) {
    arr[i] = out[i];
  }
  free(out);
}

int main()
{
  int arr[] = {3, 2, 1, 4 ,5 ,6, 7, 10, 8, 9};
  insertion_sort(arr, sizeof(arr) / sizeof(*arr));
  for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
    printf("%d ", arr[i]);
  }

  puts("");
  
  insertion_sort_in_place(arr, sizeof(arr) / sizeof(*arr));
  for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
    printf("%d ", arr[i]);
  }

  puts("");
}

