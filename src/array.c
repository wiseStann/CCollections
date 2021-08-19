/*

-> Array (dynamic array) collection <-

This software is free and can be used and modifyied by anyone
under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3
of the License, or any later version.

[Development period] -> 8/11/19 - 13/11/19
[Author] -> Stanislav Kerimov
[Github] -> https://github.com/wiseStann


-> Structure <-

typedef struct Array_type {
    size_t size;
    size_t capacity;
    double exp_val;
    void **buff;
} Array;


-> Macroses <-

Check Error macroses in "include/basic.h" header file.

A short description of all:
 -> [_EMPTY_ARRAY_ERROR], a macros for notification about empty given array
 -> [_MEMORY_ALLOCATION_ERROR], a macros for notification about memory allocation error
 -> [_INDEX_ERROR], a macros for notification about wrong given index
 -> [_VALUE_ERROR], a macros for notification about value, which is not in array

*/

#include "../include/array.h"

/*

New array creation.

* Just because before the work with
this data structure you have to assign array components to
start values *

 Parameters [in]:
    -> [array], an array that should be initialized for furter use

 Parameters [out]:
    -> [arr], a new created array

*/
Array* arrayNew()
{
    Array* arr = (Array*)malloc(sizeof(Array));
    if (!arr) {
        free(arr);
        _MEMORY_ALLOCATION_ERROR;
        exit(1);
    }
    arr->capacity = STANDARD_CAPACITY;
    arr->size = 0;
    arr->exp_val = STANDARD_EXPANSION_VAL;
    arr->buff = malloc(arr->capacity * sizeof(void*));
    return arr;
}

/*

Creating a new configurations for a custom array.
> Given size must be less than the MAX SIZE for Array Data Structure.

 Parameters [in]:
    -> [size], a size for a custom array (will be caught, if it is bigger than actual one)
    -> [cap], a capacity for a custom array
    -> [exp_val], an expansion value for a custom array

 Parameters [out]:
    -> [new_confs], new configurations for creating a custom array

*/
Config* const configsNew(size_t cap, double exp_val)
{
    Config* const new_confs = (Config*)malloc(sizeof(Config));
    if (!new_confs) {
        free(new_confs);
        _MEMORY_ALLOCATION_ERROR;
        exit(1);
    }
    if (cap > MAXSIZE) {
        panic("%s:%d: given capacity is bigger than the possible size of array", __FILE__, __FUNCTION__);
        exit(1);
    }
    new_confs->capacity = cap;
    new_confs->exp_val = exp_val;

    return new_confs;
}

/*

Customization of a given array.
> Complex time - const.

 Parameters [in]:
    -> [array], an array that should be customized
    -> [configuration], a configuration which sould customize a given array

 Parameters [out]:
    -> NULL
*/
Array* arrayCustomNew(Config* const configuration)
{   
    Array* arr_new = arrayNew();

    arr_new->exp_val = configuration->exp_val;
    arr_new->capacity = configuration->capacity;

    return arr_new;
}

/*

Creating an Array from a given array (C embedded).
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array out of which an Array should be created
    -> [size], the size of a given array

 Parameters [out]:
    -> [new_arr], a new created array

*/
Array* arrayFromIntArr(int* array, int size)
{
    Array* new_arr = arrayNew();

    for (int i = 0; i < size; i++) {
        arrayToEnd(new_arr, (void*)(size_t)array[i]);
    }
    
    return new_arr;
}

/*

Appendix an element to the end of the array.
> Size of the given array must be less than the capacity of that array.
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array to which we append element
    -> [element], an element which we want to append to the array

 Parameters [out]:
    -> NULL
*/
void arrayToEnd(Array* array, void* element)
{
    arrayAddAt(array, element, array->size);
}

/*

Appendix an element to the beginnig of the array.
> Size of the given array must be less than the capacity of that array.
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array, to which we append an element
    -> [element], an element which we want to append to the array

 Parameters [out]:
    -> NULL
*/
void arrayToBegin(Array* array, void* element)
{
    arrayAddAt(array, element, 0);
}

/*

Appendix an element in some concrete position in the array.
> Size of the given array must be less than the capacity of that array.
> Given index must be less than the size of the array.
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array, which should be inserted
    -> [element], element that will be inserted in the array
    -> [index], position on which the element will be stored

 Parameters [out]:
    -> NULL
*/
void arrayAddAt(Array* array, void* element, size_t index)
{
    if (index > array->size) {
        _INDEX_ERROR(index);
    } if (array->size >= array->capacity) {
        arrayExpandCapacity(array);
    }

    size_t mem_block = (array->size - index) * sizeof(void*);
    memmove(
        &(array->buff[index + 1]),
        &(array->buff[index]),
        mem_block
    );

    array->buff[index] = element;
    array->size++;
}

/*

Remove last element of the given array.
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array, element of which should be removed

 Parameters [out]:
    -> NULL
*/
void arrayRemoveEnd(Array* array)
{
    arrayRemoveAt(array, array->size - 1);
}

/*

Remove the first element of the given array.
> Complex time - O(n).

 Parameters [in]:
    -> [array] an array, the element of which should be removed

 Parameters [out]:
    -> NULL
*/
void arrayRemoveBegin(Array* array)
{
    arrayRemoveAt(array, 0);
}

/*

Remove an element at the specific position.
> Given array must not be empty.
> Given index must be within the bounds of the array.
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array, the element of which should be removed
    -> [index], a specific position of element

 Parameters [out]:
    -> NULL
*/
void arrayRemoveAt(Array* array, size_t index)
{
    if (array->size == 0) {
        _EMPTY_ARRAY_ERROR;
    } else if (index >= array->size) {
        _INDEX_ERROR(index);
    } else {
        size_t mem_block = (array->size - index) * sizeof(void*);
        memmove (
            &(array->buff[index]),
            &(array->buff[index+1]),
            mem_block
        );
        array->size--;
    }
}

/*

Remove the first element of the array with a given value.
> Given array must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array, the element of which should be removed
    -> [value], the value that should be removed

 Parameters [out]:
    -> NULL
*/
void arrayRemoveFirst(Array* array, void* value)
{
    if (array->size == 0) {
        _EMPTY_ARRAY_ERROR;
    } else {
        size_t index = arrayGetIndex(array, value);
        if (index != -1) {
            arrayRemoveAt(array, index);
        } else {
            _VALUE_ERROR;
        }
    }
}

/*
Remove last element of the array with a given value.
> Given array must be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array, the element of which should be removed
    -> [value], element with this value should be removed

 Parameters [out]:
    -> NULL
*/
void arrayRemoveLast(Array* array, void* value)
{
    if (array->size == 0) {
        _EMPTY_ARRAY_ERROR;
    } else if (!arrayContains(array, value)) {
        _VALUE_ERROR;
    } else {
        size_t last_index;

        for (int i = 0; i < array->size; i++) {
            if (array->buff[i] == value) {
                last_index = i;
            }
        }

        arrayRemoveAt(array, last_index);
    }
}

/*

Remove all elements of the array with a specific value.
> Given array must not be empty.
> Complex time - O(n^2).

 Parameters [in]:
    -> [array], some elements of that array sould be removed
    -> [value], all elements with this value should be removed

 Parameters [out]:
    -> NULL
*/
void arrayRemoveAll(Array* array, void* value)
{
    if (array->size == 0) {
        _EMPTY_ARRAY_ERROR;
    } else {
        int index;
        for (int i = 0; i < array->size; i++) {
            if (array->buff[i] == value) {
                index = i;
                arrayRemoveAt(array, index);
                i--;
            }
        }
    }
}

/*

Reversing a given array.
Complex time - O(n).

 Parameters [in]:
    -> [array], an array, which should be reversed

 Parameters [out]:
    -> NULL
*/
void arrayReverseMut(Array* array)
{
    if (array->size == 0) {
        _EMPTY_ARRAY_ERROR; return;
    }

    void **temp_buff = malloc(array->size * sizeof(void*));

    // An algorithm for writing new buffer in reverse order 
    size_t index = array->size - 1;
    for (int i = 0; i < array->size; i++) {
        temp_buff[i] = array->buff[i + index];
        index -= 2;
    }

    // Copying temporary byffer to array buffer
    memcpy(
        array->buff,
        temp_buff,
        array->size * sizeof(void*)
    );
}

/*

Creating new array, copying elements of old one to that in reverse order.
> Given array nust be not empty.
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array, which elements should be copied to new one in reverse order

 Parameters [out]:
    -> [new_arr], a new array, which is like given array but in reversed order

*/
Array* arrayReverseNew(Array* array)
{
    if (array->size == 0) {
        return arrayNew();
    }

    Array* new_arr = arrayNew();
    for (int i = 0; i < array->size; i++) {
        arrayToBegin(new_arr, array->buff[i]);
    }
    new_arr->size = array->size;
    return new_arr;
}

/*

Getting the index of the given value in the array.
> Given array must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array, the index of which element will be got
    -> [value], value, which index in the array is returned

 Parameters [out]:
    -> [index], the index of the given value in the array

*/
size_t arrayGetIndex(Array* array, void* value)
{
    if (array->size == 0) {
        _EMPTY_ARRAY_ERROR;
        return -1;
    }

    for (int i = 0; i < array->size; i++) {
        if (array->buff[i] == value) {
            return i;
        }
    }
    return -1;
}

/*

Getting the value by the given index.
> Given array must not be empty.
> Given index must be within the bounds of the array
> Complex time - const.

 Parameters [in]:
    -> [array], an array, the value of which will be returned
    -> [index], an index, by which the value will be returned

 Parameters [out]:
    -> [value], the value that is found by index

*/
void* arrayGetAt(Array* array, size_t index)
{
    if (array->size == 0) {
        _EMPTY_ARRAY_ERROR;
        return NULL;
    } else if (index >= array->size) {
        _INDEX_ERROR(index);
        return NULL;
    } else {
        return array->buff[index];
    }
}

/*

Getting the first element of a given array.
> Given array must be not empty.
> Complex time - const.

 Parameters [in]:
    -> [array], an array, the first element of which should be returned

 Parameters [out]:
    -> [first_el], the first element of a given array

*/
void* arrayGetBegin(Array* array)
{
    if (array->size == 0) {
        _EMPTY_ARRAY_ERROR;
        return NULL;
    }

    return array->buff[0];
}

/*

Getting the last element of a given array.
> Given array must be not empty.
> Complex time - const.

 Parameters [in]:
    -> [array], an array, the last element of which should be returned

 Parameters [out]:
    -> [last_el], the last element of a given array

*/
void* arrayGetEnd(Array* array)
{
    if (array->size == 0) {
        _EMPTY_ARRAY_ERROR;
        return NULL;
    }

    return array->buff[array->size - 1];
}

/*

Remove the last element from array and return it.
> Given array must be not empty.
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array, from which the last element should be poped

 Parameters [out]:
    -> [tail], the last element of a given array

*/
void* arrayPop(Array* array)
{
    if (array->size == 0) {
        _EMPTY_ARRAY_ERROR;
        return NULL;
    }

    void* tail = arrayGetAt(array, array->size - 1);
    if (tail != NULL) {
        arrayRemoveEnd(array);
    }
    return tail;
}

/*

Remove the first element from array and return it.
> Given array must be not empty.
> Complex time - const.

 Parameters [in]:
    -> [array], an array, from which the first element should be polled

 Parameters [out]:
    -> [head], the first element of a given array

*/
void* arrayPoll(Array* array)
{
    if (array->size == 0) {
        _EMPTY_ARRAY_ERROR;
        return NULL;
    }

    void* head = array->buff[0];
    if (head != NULL) {
        arrayRemoveBegin(array);
    }
    return head;
}

/*

Getting a number of all elements in the array with a given value.
> Given array must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array, which will be looked up
    -> [value], the value, number in array of which will be searched

 Parameters [out]:
    -> [count], the number of all elements with a given value

*/
size_t arrayCount(Array* array, void* value)
{
    if (array->size == 0) {
        _EMPTY_ARRAY_ERROR;
        return 0;
    }

    size_t count = 0;
    for (int i = 0; i < array->size; i++) {
        if (array->buff[i] == value) {
            count++;
        }
    }
    return count;
}

/*

Creating new array, copying elements from old one to that from begin_index to end_index.
> Given array must be not empty.
> Given indexes must be within the bounds of array.
> Begin index must be less or equal to end index.
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array, using which a new substring should be created
    -> [begin_index], an index of the first (left) bound of substring
    -> [end_index], an index of the second (right) bound of substring

 Parameters [out]:
    -> [substring], a substring, which should be created

*/
Array* arraySubarray(Array* array, size_t begin_index, size_t end_index)
{
    if (array->size == 0) {
        _EMPTY_ARRAY_ERROR;
    } else if (begin_index >= array->size) {
        _INDEX_ERROR(begin_index);
    } else if (end_index >= array->size) {
        _INDEX_ERROR(end_index);
    } else if (begin_index > end_index) {
        panic("%s:%d: begin index of substr must be less than end index", __FILE__, __LINE__);
    } else {
        Array* substring = arrayNew();
        for (int i = begin_index; i <= end_index; i++) {
            arrayToEnd(substring, array->buff[i]);
        }
        substring->size = end_index - begin_index + 1;
        return substring;
    }
    return NULL;
}

/*
Checking if an element with such value is in array ot not.
Complex time - O(n).

 Parameters [in]:
    -> [array], an array which contains or does not contain an element
    -> [value], the value which for checking

 Parameters [out]:
    -> [contains], boolean result of the function

*/
bool arrayContains(Array* array, void* value)
{
    if (arrayGetIndex(array, value) == -1) {
        return false;
    }
    return true;
}

/*

Making a shallow copy of the given array.
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array, which copy the function returned

 Parameters [out]:
    -> [arr_for_copy], a created array, which is a copy of a given array

*/
Array* arrayCopy(Array* array)
{
    // New configurations for a custom array
    Config* new_confs = configsNew(array->capacity, array->exp_val);

    Array* arr_for_copy = arrayCustomNew(new_confs);
    arr_for_copy->size = array->size;

    // Copying temporary buffer to created array buffer
    memcpy(
        arr_for_copy->buff,
        array->buff,
        array->size * sizeof(void*)
    );

    return arr_for_copy;
}

/*

Swapping two elements of the array by their indexes.
> Indexes must be within the bounds of the array.
> Complex time - const.

 Parameters [int]:
    -> [array], an array, elements of which should be swapped
    -> [f_index], an index of the first value
    -> [s_index], an index of the second value

 Parameters [out]:
    -> NULL
*/
void arraySwapByIndexes(Array* array, size_t f_index, size_t s_index)
{   
    if (array->size == 0) {
        _EMPTY_ARRAY_ERROR;
    } else if (f_index >= array->size) {
        _INDEX_ERROR(f_index);
    } else if (s_index >= array->size) {
        _INDEX_ERROR(s_index);
    } else {
        void* temp = array->buff[f_index];
        array->buff[f_index] = array->buff[s_index];
        array->buff[s_index] = temp;
    }
}

/*

Swapping two elements of the array by their values.
> Given values must be in the array.
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array, elements of which should be swapped
    -> [f_value], the first value for swapping
    -> [s_value], the second value for swapping

 Parameters [out]:
    -> NULL
*/
void arraySwapByValues(Array* array, void* f_value, void* s_value)
{
    size_t f_index = arrayGetIndex(array, f_value);
    if (f_index == -1) {
        _VALUE_ERROR; return;
    }

    size_t s_index = arrayGetIndex(array, s_value);
    if (s_index == -1) {
        _VALUE_ERROR; return;
    }

    arraySwapByIndexes(array, f_index, s_index);
}

/*

Replacing an element of array by its index.
> Given array must be not empty.
> Given index must be within the bounds of the array.
> Complex time - const.

 Parameters [in]:
    -> [array], an array, element of which should be replaced
    -> [index], an index of the element, which should be replaced
    -> [value], value, which the element should be replaced by

 Parameters [out]:
    -> NULL
*/
void arrayReplaceByIndex(Array* array, size_t index, void* value)
{
    if (array->size == 0) {
        _VALUE_ERROR;
    } else if (index >= array->size) {
        _INDEX_ERROR(index);
    } else {
        array->buff[index] = value;
    }
}

/*

Replacing an elementof array by its value.
> Given array must be not empty.
> Given value must be in the array.
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array, element of which should be replaced
    -> [value_to_repl], initial value of element that should be replaced
    -> [value_for_repl], value, which the element should be replaced by

 Parameters [out]:
    -> NULL
*/
void arrayReplaceByValue(Array* array, void* value_to_repl, void* value_for_repl)
{
    if (array->size == 0) {
        _EMPTY_ARRAY_ERROR;
    } else {
        size_t index = arrayGetIndex(array, value_to_repl);
        if (index != -1) {
            array->buff[index] = value_for_repl;
        } else {
            _VALUE_ERROR;
        }
    }
}

/*

Extending one array by another one.
> Complex time - O(n).

 Parameters [in]:
    -> [f_arr], an array, which should be extened
    -> [s_arr], an array, which should extend the first array

 Parameters [out]:
    -> NULL
*/
void arrayExtend(Array* f_arr, Array* s_arr)
{
    // Just appending elements from s_arr to f_arr
    for (int i = 0; i < s_arr->size; i++) {
        arrayToEnd(f_arr, s_arr->buff[i]);
    }
}

/*

Swapping two arrays.
> Complex time - O(n).

 Parameters [in]:
    -> [f_arr], the first array for swapping
    -> [s_arr], the second array for swapping

 Parameters [out]:
    -> NULL
*/
void swapArrays(Array* f_arr, Array* s_arr)
{
    Array* temp_arr = arrayCopy(f_arr);
    *f_arr = *s_arr;
    *s_arr = *temp_arr;
}

/*

Sorting a given array in-place, i.e. the given array is mutable.
> Complex time - depending on what kind of sorting algorithm is used here.

 Parameters [in]:
    -> [array], an array, which should be sorted
    -> [func], a function, which should sort the given array

 Parameters [out]:
    -> NULL
*/
void arraySortMut(Array* array, void**(*func)(void**, int))
{
    func(array->buff, array->size);
}

/*

Sorting a given array and return a copy of this array.
> Complex time - depending on what kind of sorting algorithm is used here.

 Parameters [in]:
    -> [array], an array, which sould be sorted and a copy of which should be return
    -> [func], a function, which should sort the given array

 Parameters [out]:
    -> [new_arr], a new array, which is a sorted copy of a given one

*/
Array* arraySortNew(Array* array, void**(*func)(void**, int))
{
    arraySortMut(array, func);

    // Creating new array
    Array* new_arr = arrayNew();

    /* If the capacity of array is bigger than the capacity of a new one,
       we should expand it capacity */
    while (array->capacity > new_arr->capacity) {
        arrayExpandCapacity(new_arr);
    }
    new_arr->size = array->size;
    new_arr->exp_val = array->exp_val;
    new_arr->buff = array->buff;
    return new_arr;
}

/*

Expansion of the capacity when it is necessary.
> Given array must not be empty.
> Complex time - most likely O(n).

* Actually this stuff is made due to dynamic memory allocation, it is very
convenient because we are not to keep array of a huge capacity in our
memory, but just to expand it when it is necessary *

 Parameters [in]:
    -> [array], an array capacity of which should be expanded

 Parameters [out]:
    -> NULL
*/
void arrayExpandCapacity(Array* array)
{
    if (array->capacity >= MAXSIZE) {
        panic("'%s':%d: max capacity size exceeded", __FUNCTION__, __LINE__);
    } else {
        size_t temp_cap = array->capacity * array->exp_val;
        temp_cap = temp_cap > MAXSIZE ? MAXSIZE : temp_cap;

        array->capacity = temp_cap;
        array->buff = realloc(array->buff, array->capacity * sizeof(void*));
    }
}

/*

Cutting the capacity of the array.
> Complex time - const.

* After this action the capacity of the array will be
equals to the number of its elements (size) *

 Parameters [in]:
    -> [array], an array, the capacity of which should be caught

 Parameters [out]:
    -> NULL
*/
void arrayCutCapacity(Array* array)
{
    if (array->size == 0) {
        array->capacity = STANDARD_CAPACITY;
    } else {
        array->capacity = array->size;
    }
}

/*

Clearing array buffer without freeing up memory.
Complex time - const.

 Parameters [in]:
    -> [array], an array that will be cleared
 Parameters [out]:
    -> NULL
*/
void arrayClear(Array* array)
{
    array->size = 0;
    array->capacity = STANDARD_CAPACITY;
    array->exp_val = STANDARD_EXPANSION_VAL;
}

/*

Freeing up all memory that was allocated for the array.
Complex time - const.

 Parameters [in]:
    -> [array], an array that will be freed
 Parameters [out]:
    -> NULL
*/
void arrayFree(Array* array)
{
    free(array->buff);
    free(array);
}


/////////////////////////////////////////////////////////////

/*

-> Iterator structure <-

typedef struct ArrayIter_type {
    Array* arr;
    size_t curr_index;
} ArrayIterator;


This wrapper allows us to iterate over a given array.
It provides some the most useful methods.

*/

/*

New array iterator creation.
> Complex time  - const.

* In order to make an array iterable, we have to wrapp
it in ArrayIterator wrapper *

 Parameters [in]:
    -> [array], an array, which should be wrapped in

 Parameters [out]:
    -> NULL
*/
ArrayIterator* arrayIterNew(Array* array)
{
    ArrayIterator* arrIter = malloc(sizeof(ArrayIterator));
    arrIter->arr = array;
    arrIter->curr_index = 0;
    arrIter->size = array->size;

    return arrIter;
}

/*

Checking if a given array has the next element or not.
> Complex time - const.

 Parameter [in]:
    -> [iterator], an iterator, the next element of which we check

 Parameter [out]:
    -> [bool], the result of checking

*/
bool arrayIterHasNext(ArrayIterator* iterator)
{
    // If there are no next elements avaliable
    if (iterator->curr_index >= iterator->size) {
        return false;
    }
    return true;
}

/*

Checking if a given array has the previous element or not.
> Complex time - const.

 Parameter [in]:
    -> [iterator], an iterator, the previous element of which we check

 Parameter [out]:
    -> [bool], the result of checking

*/
bool arrayIterHasPrev(ArrayIterator* iterator)
{
    // If there are no previous elements avaliable
    if (iterator->curr_index == 0) {
        return false;
    }
    return true;
}

/*

Getting the next element of a wrapped in array.
> Complex time - const.

 Parameters [in]:
    -> [iterator], an iterator, the next element of which should be returned

 Parameters [out]:
    -> [next_el], the next element of wrapped in array

*/
void* arrayIterNext(ArrayIterator* iterator)
{
    // If there are no next elements available
    if (!arrayIterHasNext(iterator)) {
        return NULL;
    }

    void* next_el = iterator->arr->buff[iterator->curr_index];
    iterator->curr_index++;
    return next_el;
}

/*

Getting the previous element of a wrapped in array.
> Complex time - const.

 Parameters [in]:
    -> [iterator], an iterator, the previous element of which should be returned

 Parameters [out]:
    -> [prev_el], the previous element of wrapped in array

*/
void* arrayIterPrev(ArrayIterator* iterator)
{
    if (!arrayIterHasPrev(iterator)) {
        return NULL;
    }

    void* prev_el = iterator->arr->buff[iterator->curr_index - 1];
    iterator->curr_index--;
    return prev_el;
}

/*

Inserting an element at the specific position.
> Complex time - O(n).

 Parameters [in]:
    -> [iterator], an iterator, wrapped array of which should be inserted

 Parameters [out]:
    -> NULL
*/
void arrayIterAddAt(ArrayIterator* iterator, size_t index, void* value)
{
    arrayAddAt(iterator->arr, value, index);
}

/*

Remove element at a specific position.
> Complex time - O(n).

 Parameters [in]:
    -> [iterator], an iterator, the element of which should be removed
    -> [index], an index of element, which should be removed

 Parameters [out]:
    -> NULL
*/
void arrayIterRemoveAt(ArrayIterator* iterator, size_t index)
{
    arrayRemoveAt(iterator->arr, index);
}

/*

Getting an element standing at the specific position.
> Complex time - const.

 Parameters [in]:
    -> [iterator], an iterator, the element of which should be got
    -> [index], an index of element, which should be got

 Parameters [out]:
    -> [element], an element, which should be got

*/
void* arrayIterGetAt(ArrayIterator* iterator, size_t index)
{
    void* element = arrayGetAt(iterator->arr, index);
    return element;
}

/*

Replacing an element standing on a specific position.
> Complex time - const.

 Parameters [in]:
    -> [iterator], an iterator, the element of which should be replaced
    -> [index], an index of element in the array
    -> [value], a value, which should replace an old one

 Parameter [out]:
    -> NULL
*/
void arrayIterReplaceAt(ArrayIterator* iterator, size_t index, void* value)
{
    arrayReplaceByIndex(iterator->arr, index, value);
}

/*

Setting the index of given iterator.
> Complex time - const.

 Parameters [in]:
    -> [iterator], an iterator, the index of which should be set
    -> [new_index], an index, which should replace an old one

 Parameters [out]:
    -> NULL
*/
void arrayIterSetIndex(ArrayIterator* iterator, size_t new_index)
{   
    if (new_index > iterator->size) {
        _INDEX_ERROR(new_index);    
    }

    iterator->curr_index = new_index;
}
