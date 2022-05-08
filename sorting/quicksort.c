#include <stdio.h>
#include <stdlib.h>

void quick_sortR(int min, int max, int *array) {
  if (min < max) {
    int pointer = min + (max - min) / 2;

    // Iterate over the array
    for (int i = min; i <= max; i++) {
      // Put all numbers less than the pointer before it
      if (array[i] > array[pointer] && i < pointer) {
        int temp = array[i];

        // Move elements from i to pointer - 1 up by 1
        for (int j = i; j < pointer; j++) {
          array[j] = array[j + 1];
        }

        // Put the original element where the pointer used to be
        array[pointer] = temp;
        // The pointer has moved in the array
        pointer--;
        // The element has moved forwards so we are looking at another element
        i--;
        // Put all larger numbers after the pointer
      } else if (array[i] < array[pointer] && i > pointer) {
        int temp = array[i];

        // Move all elements from the pointer + 1 up by 1
        for (int j = i; j > pointer; j--) {
          array[j] = array[j - 1];
        }

        // Put the original element at i at the pointer
        array[pointer] = temp;
        // The pointer has moved
        pointer++;
      }
    }

    quick_sortR(min, pointer - 1, array);
    quick_sortR(pointer + 1, max, array);
  }
}

void quick_sort(int *array, int length) { quick_sortR(0, length - 1, array); }

int main()
{
  int arr[] = {3, 2, 1, 4 ,5 ,6, 7, 10, 8, 9};
  quick_sort(arr, sizeof(arr) / sizeof(*arr));
  for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
    printf("%d ", arr[i]);
  }

  puts("");
}

