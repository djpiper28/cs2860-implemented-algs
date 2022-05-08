#include <stdio.h>
#include <stdlib.h>

#define swap(a, b) \
  int tmp = a; \
  a = b; \
  b = tmp;

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2; 

    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }
 
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }
 
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}
 
void heap_sort(int *arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
 
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main()
{
  int arr[] = {3, 2, 1, 4 ,5 ,6, 7, 10, 8, 9};
  heap_sort(arr, sizeof(arr) / sizeof(*arr));
  for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
    printf("%d ", arr[i]);
  }

  puts("");
}

