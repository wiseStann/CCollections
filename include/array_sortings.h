/* 
    Implementations of popular sorting algorithms for Array data structure

    ALL THESE ALGORITHMS ARE INTENDED TO SORT ONLY NUMERICAL ARRAYS.
*/

#ifndef ARRAY_SORTINGS_H
#define ARRAY_SORTINGS_H


 void swap(void** a, void** b)
{
    int* temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble sort algorithm
void** bubbleSort(void** array, int size)
{
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i = 0, j = 1; i < size && j < size; i++, j++) {
            if (array[i] > array[j]) {
                swap(&array[i], &array[j]);
                swapped = true;
            }
        }
    }
    return array;
}

// Selection sort algorithm
void** selectionSort(void** array, int size) 
{ 
    int i, j, min_idx;
 
    for (i = 0; i < size - 1; i++) 
    { 
        min_idx = i; 
        for (j = i + 1; j < size; j++) 
          if (array[j] < array[min_idx]) 
            min_idx = j;
        swap(&array[min_idx], &array[i]); 
    }
    return array;
} 

// Insertion sort algorithm
void** insertionSort(void** array, int size) 
{ 
    int i, j; 
    for (i = 1; i < size; i++) { 
        void* key = array[i]; 
        j = i - 1;
        while (j >= 0 && array[j] > key) { 
            array[j + 1] = array[j]; 
            j = j - 1; 
        } 
        array[j + 1] = key; 
    }
    return array;
}

#endif // ARRAY_SORTINGS_H
