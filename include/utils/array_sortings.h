/* Implementations of popular sorting algorithms for Array data structure */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef ARRAY_SORTINGS_H
#define ARRAY_SORTINGS_H


static void swap(void** a, void** b)
{
    int* temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble sort algorithm
void** bubbleSort(void** array, int n)
{
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i = 0, j = 1; i < n && j < n; i++, j++) {
            if (array[i] > array[j]) {
                swap(&array[i], &array[j]);
                swapped = true;
            }
        }
    }
    return array;
}

// Selection sort algorithm
void** selectionSort(void** array, int n) 
{ 
    int i, j, min_idx;
 
    for (i = 0; i < n - 1; i++) 
    { 
        min_idx = i; 
        for (j = i + 1; j < n; j++) 
          if (array[j] < array[min_idx]) 
            min_idx = j;
        swap(&array[min_idx], &array[i]); 
    }
    return array;
} 


#endif // ARRAY_SORTINGS_H
