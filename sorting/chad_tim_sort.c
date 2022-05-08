// The cooler merge sort
#include <stdio.h>
#include <stdlib.h>

void swap(int *array, int indexA, int indexB) {
  int temp = array[indexA];
  array[indexA] = array[indexB];
  array[indexB] = temp;
}

// Don't call this as the sort as this needs the value of n to init
void insertionSortR(int *array, int n) {
  if (n > 0) {
    insertionSortR(array, n - 1);

    int temp = array[n];
    int j = n - 1;
    for (; j >= 0 && array[j] > temp; j--) {
      array[j + 1] = array[j];
    }

    array[j + 1] = temp;
  }
}

void insertionSort(int *array, int n) { insertionSortR(array, n - 1); }

// Bounded insertion sort for tim sort
void insertionSortRBound(int *array, int min, int max) {
  if (max > min) {
    insertionSortRBound(array, min, max - 1);

    int temp = array[max];
    int j = max - 1;
    for (; j >= min && array[j] > temp; j--) {
      array[j + 1] = array[j];
    }

    array[j + 1] = temp;
  }
}

void insertionSortBound(int *array, int min, int max) {
  insertionSortRBound(array, min, max - 1);
}

void merge(int *array, int min1, int max1, int min2, int max2) {
  int arrayOnePointer = min1;
  int arrayTwoPointer = min2;
  while (arrayOnePointer <= max1 && arrayTwoPointer <= max2) {
    if (array[arrayOnePointer] < array[arrayTwoPointer]) {
      // Swap element in array 1 and 2, inc array 1 pointer
      swap(array, arrayOnePointer, arrayTwoPointer);
      arrayOnePointer++;
    } else {
      // Swap element in array 2 and 1, inc array 2 pointer
      swap(array, arrayOnePointer, arrayTwoPointer);
      arrayTwoPointer++;
    }
  }
}

#define segmentLength 10
void insertionSortSegments(int *array, int size) {
  for (int i = 0; i * segmentLength < size; i += segmentLength + 1) {
    // Assert that i is within the length
    if (i >= size)
      i = size - 1;
    // Insertion sort the segment
    insertionSortBound(array, i, i + segmentLength);
  }
}

void mergeSegments(int *array, int size) {
  int runLength = segmentLength;
  while (runLength < size) {
    // Assert the merge length is a valid
    if (runLength >= size) {
      runLength = size - 1;
    }

    for (int i = 0; i * runLength < size; i += runLength + 1) {
      int chunkLength = runLength / 2;
      merge(array, i, i + chunkLength, i + chunkLength + 1, i + runLength);
    }

    runLength *= 2;
  }
}

void timSort(int *array, int length) {
  insertionSortSegments(array, length);
  mergeSegments(array, length);
}

int main()
{
  int arr[10000];
  for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
    arr[i] = rand();
  }

  timSort(arr, sizeof(arr) / sizeof(*arr));
  for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
    printf("%d ", arr[i]);
  }

  puts("");
}

