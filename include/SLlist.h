/* Insides of Singly Linked List data structure */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

// Defining some macroses for handling popular errors
#define _EMPTY_LIST_ERROR panic("%s:%d in '%s': given list is empty", __FILE__, __LINE__, __FUNCTION__);
#define _MEMORY_ALLOCATION_ERROR panic("%s:%d: in '%s': could not allocate memory", __FILE__, __LINE__, __FUNCTION__);
#define _INDEX_ERROR(index_name) panic("%s:%d: in '%s': index %d is not within the bounds of list", __FILE__, __LINE__, __FUNCTION__, (int)index_name)
#define _VALUE_ERROR(value_name) panic("%s:%d: in '%s': value %d is not in list", __FILE__, __LINE__, __FUNCTION__, (int)value_name)

// Node structure
typedef struct Node_type {
    void* data;
    struct Node_type* next;
} Node;

// Linked list structure, stores a pointer to linked nodes
typedef struct SLL_type {
    size_t size;
    Node* head;
} List;


// New list creation
static List* listNew();

// New node creation
static Node* nodeNew(void* value);

// Showing an error message
static void panic(const char* message, ...);

// Appending an element to the end of the list
void listPush(List* list, void* value);

// Appending an element to the beginning of the list
void listPrepend(List* list, void* value);

// Inserting an element at the specific position
void listInsert(List* list, size_t index, void* value);

// Remove last element of the list
void listRemoveEnd(List* list);

// Remove the first element of thee list
void listRemoveBegin(List* list);

// Remove an element standing at the specific position
void listRemoveAt(List* list, size_t index);

// Remove last element of the given list
void listRemoveLast(List* list, void* value);

// Remove the first element of the given list
void listRemoveFirst(List* list, void* value);

// Remove all elements with a given value
void listRemoveAll(List* list, void* value);

// Getting index of a given element
size_t listGetIndex(List* list, void* value);

// Getting value standing on a specific position
void* listGetAt(List* list, size_t index);

// Getting the first element of a given list
void* listGetBegin(List* list);

// Getting the last element of a given list
void* listGetEnd(List* list);

// Remove the last element from list and return it
void* listPop(List* list);

// Remove the first element from list and return it
void* listPoll(List* list);

// Getting the number of elements of the list with a given value
size_t listCount(List* list, void* value);

// Getting a substring from list, something like python's slice
List* listSublist(List* list, size_t begin_index, size_t end_index);

// Check if list contains given element or not
bool listContains(List* list, void* value);

// Making a shallow copy of a given list
List* listCopy(List* list);

// Reversing an list in-place 
void listReverseMut(List* list);

// Creating a copy, reversing it and return
List* listReverseNew(List* list);

// Getting the sum of all element of the list
int listSum(List* list);

// Getting an element with the minimum value
void* listMin(List* list);

// Getting an element with the maximum value
void* listMax(List* list);

// Swapping two elements by the given indexes
void listSwapByIndexes(List* list, size_t f_index, size_t s_index);

// Swapping two first elements with the given values
void listSwapValues(List* list, void* f_value, void* s_value);

// Replacing an element by index
void listReplaceByIndex(List* list, size_t index, void* value);

// Replacing an element by value
void listReplaceByValue(List* list, void* value_to_repl, void* value_for_repl);

// Extending one list by another one
void listExtend(List* f_list, List* s_list);

// Swapping two lists
void swapLists(List* f_list, List* s_list);

// Sorting a given list 'in-place' by a chisen sort function
void listSortMut(List* list, List*(*func)(List*));

// Creating a copy, sorting it by a chosen sort function and return
List* listSortNew(List* list, List*(*func)(List*));

// Clear list
static void listClear(List* list);

// Remove list
static void listDelete(List* list);


#endif // SINGLY_LINKED_LIST_H
