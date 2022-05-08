#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int *arr, size_t length) {
  int changed = 1;
  while (changed) {
    changed = 0;
    for (int i = 0; i < length - 1; i++) {
      if (arr[i] > arr[i + 1]) {
        changed = 1;
        int tmp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = tmp;
      }
    }
  }
}

int main()
{
  int arr[] = {3, 2, 1, 4 ,5 ,6, 7, 10, 8, 9};
  bubble_sort(arr, sizeof(arr) / sizeof(*arr));
  for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
    printf("%d ", arr[i]);
  }

  puts("");
}

