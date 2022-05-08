#include <stdio.h>
#include <stdlib.h>

void selection_sort(int *arr, size_t length) {
  if (length == 0) {
    return;
  }

  int min = arr[0], min_ptr = 0;
  for (int i = 1; i < length; i++) {
    if (arr[i] < min) {
      min_ptr = i;
      min = arr[i];
    }
  }

  int tmp = arr[0];
  arr[0] = arr[min_ptr];
  arr[min_ptr] = tmp;

  selection_sort(++arr, --length);
}

int main()
{
  int arr[] = {3, 2, 1, 4 ,5 ,6, 7, 10, 8, 9};
  selection_sort(arr, sizeof(arr) / sizeof(*arr));
  for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
    printf("%d ", arr[i]);
  }

  puts("");
}

