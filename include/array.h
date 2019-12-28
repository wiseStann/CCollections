/* Insides of Dynamic Array data structure */

#include "basic.h"

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#define STANDARD_EXPANSION_VAL 1.5
#define STANDARD_CAPACITY 10

// Denote maximum capacity for the queue just for controlling size of allocated memory
#define MAXSIZE INT_MAX

#define arrayCapacity(x) (x->capacity)
#define arraySize(x) (x->size)
#define arrayIterSize(x) (x->arr->size)

// Array data structure
typedef struct Array_type {
    // The size of array, i.e. how many elements it contains
    size_t size;
    // The capacity of array, i.e. dynamic memory block
    size_t capacity;
    // The expansion value, i.e. how rapidly the capacity will expand
    double exp_val;
    // The buffer of array, i.e. the storage of elements
    void **buff;
} Array;

// Configuration structure for customization
typedef struct Config_type {
    // Almost the same stuff, but now for the customization
    size_t capacity;
    double exp_val;
} Config;


// New array creation
Array* arrayNew();
 
// New configurations for creating custom array
Config* const configsNew(size_t cap, double exp_val);

// Custom initialization of array
Array* arrayCustomNew(Config* const configuration);

// Creating an array from a given array
Array* arrayFromIntArr(int* array, int size);

// Appending an element to the end of the array
void arrayToEnd(Array* array, void* value);

// Appending an element to the beginning of the array
void arrayToBegin(Array* array, void* value);

// Inserting an element at the specific position
void arrayAddAt(Array* array, void* value, size_t index);

// Remove last element of the array
void arrayRemoveEnd(Array* array);

// Remove the first element of thee array
void arrayRemoveBegin(Array* array);

// Remove an element standing at the specific position
void arrayRemoveAt(Array* array, size_t index);

// Remove last element of the given array
void arrayRemoveLast(Array* array, void* value);

// Remove the first element of the given array
void arrayRemoveFirst(Array* array, void* value);

// Remove all elements with a given value
void arrayRemoveAll(Array* array, void* value);

// Reversing an array in-place 
void arrayReverseMut(Array* array);

// Creating a copy, reversing it and return
Array* arrayReverseNew(Array* array);

// Getting index of element
size_t arrayGetIndex(Array* array, void* value);

// Getting value standing on a specific position
void* arrayGetAt(Array* array, size_t index);

// Getting the first element of a given array
void* arrayGetBegin(Array* array);

// Getting the last element of a given array
void* arrayGetEnd(Array* array);

// Remove the last element from array and return it
void* arrayPop(Array* array);

// Remove the first element from array and return it
void* arrayPoll(Array* array);

// Getting the number of elements of the array with a given value
size_t arrayCount(Array* array, void* value);

// Getting a substring from array, something like python's slice
Array* arraySubarray(Array* array, size_t begin_index, size_t end_index);

// Getting an element with the maximum value
void* arrayMax(Array* array);

// Checking if array contains the value or not
bool arrayContains(Array* array, void* value);

// Making a shallow copy of the given array
Array* arrayCopy(Array* array);

// Swapping two elements by the given indexes
void arraySwapByIndexes(Array* array, size_t f_index, size_t s_index);

// Swapping two first elements with the given values
void arraySwapByValues(Array* array, void* f_value, void* s_value);

// Replacing an element by index
void arrayReplaceByIndex(Array* array, size_t index, void* value);

// Replacing an element by value
void arrayReplaceByValue(Array* array, void* value_to_repl, void* value_for_repl);

// Extending one array by another one
void arrayExtend(Array* f_arr, Array* s_arr);

// Swapping two arrays
void swapArrays(Array* f_arr, Array* s_arr);

// Sorting a given array 'in-place' by a chosen sort function
void arraySortMut(Array* array, void**(*func)(void**, int));

// Creating a copy, sorting it by a chosen sort function and return
Array* arraySortNew(Array* array, void**(*func)(void**, int));

// Expanding the capacity of the given array
void arrayExpandCapacity(Array* array);

// Cutting the capacity of the array
void arrayCutCapacity(Array* array);

// Clear array
void arrayClear(Array* array);

// Freeing up memory that was allocated for the array
void arrayFree(Array* array);

//////////////////////////////////////


// Wrapper for Array type
typedef struct ArrayIter_type {
    // An array that should be wrapped in
    Array* arr;

    // Position of iterator pointer, i.e. on which element it points now
    size_t curr_index;

    // Just size of buffer of wrapped array
    size_t size;
} ArrayIterator;

// Just something like Python's iter()
ArrayIterator* arrayIterNew(Array* array);

// Check if a given array has next element
bool arrayIterHasNext(ArrayIterator* iterator);

// Check if a given array has prev element
bool arrayIterHasPrev(ArrayIterator* iterator);

// Getting the next element of iterator
void* arrayIterNext(ArrayIterator* iterator);

// Getting the previous element of iterator
void* arrayIterPrev(ArrayIterator* iterator);

// Appending an element to the iterator
void arrayIterAddAt(ArrayIterator* iterator, size_t index, void* value);

// Remove an element standing at the specific position
void arrayIterRemoveAt(ArrayIterator* iterator, size_t index);

// Getting an element standing on a specific position
void* arrayIterGetAt(ArrayIterator* iterator, size_t index);

// Replacing an element by index
void arrayIterReplaceAt(ArrayIterator* iterator, size_t index, void* value);

// Setting a new index for 'curr_index' field
void arrayIterSetIndex(ArrayIterator* iterator, size_t new_index);


#endif // DYNAMIC_ARRAY_H
