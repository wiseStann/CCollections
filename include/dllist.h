/* Insides of Doubly Linked List data structure */

#include "utils/basic.h"

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#define listSize(x) (x->size)

// Node structure
typedef struct Node_type {
    void* data;
    struct Node_type* next;
    struct Node_type* prev;
} Node;

// Linked list structure, stores a pointer to linked nodes
typedef struct DLL_type {
    size_t size;
    Node* head;
    Node* tail;
} DList;


// New list creation
static DList* listNew();

// New node creation
static Node* nodeNew(void* value);

// Appending an element to the end of the list
void listPush(DList* list, void* value);

// Appending an element to the beginning of the list
void listPrepend(DList* list, void* value);

// Inserting an element at the specific position
void listInsert(DList* list, size_t index, void* value);

// Remove last element of the list
void listRemoveEnd(DList* list);

// Remove the first element of thee list
void listRemoveBegin(DList* list);

// Remove an element standing at the specific position
void listRemoveAt(DList* list, size_t index);

// Remove last element of the given list
void listRemoveLast(DList* list, void* value);

// Remove the first element of the given list
void listRemoveFirst(DList* list, void* value);

// Remove all elements with a given value
void listRemoveAll(DList* list, void* value);

// Getting index of a given element
size_t listGetIndex(DList* list, void* value);

// Getting value standing on a specific position
void* listGetAt(DList* list, size_t index);

// Getting the first element of a given list
void* listGetBegin(DList* list);

// Getting the last element of a given list
void* listGetEnd(DList* list);

// Remove the last element from list and return it
void* listPop(DList* list);

// Remove the first element from list and return it
void* listPoll(DList* list);

// Getting the number of elements of the list with a given value
size_t listCount(DList* list, void* value);

// Getting a substring from list, something like python's slice
DList* listSublist(DList* list, size_t begin_index, size_t end_index);

// Check if list contains given element or not
bool listContains(DList* list, void* value);

// Making a shallow copy of a given list
DList* listCopy(DList* list);

// Reversing an list in-place 
void listReverseMut(DList* list);

// Creating a copy, reversing it and return
DList* listReverseNew(DList* list);

// Getting the sum of all element of the list
int listSum(DList* list);

// Getting an element with the minimum value
void* listMin(DList* list);

// Getting an element with the maximum value
void* listMax(DList* list);

// Swapping two elements by the given indexes
void listSwapByIndexes(DList* list, size_t f_index, size_t s_index);

// Swapping two first elements with the given values
void listSwapValues(DList* list, void* f_value, void* s_value);

// Replacing an element by index
void listReplaceByIndex(DList* list, size_t index, void* value);

// Replacing an element by value
void listReplaceByValue(DList* list, void* value_to_repl, void* value_for_repl);

// Extending one list by another one
void listExtend(DList* f_list, DList* s_list);

// Swapping two lists
void swapLists(DList* f_list, DList* s_list);

// Sorting a given list 'in-place' by a chisen sort function
void listSortMut(DList* list, DList*(*func)(DList*));

// Creating a copy, sorting it by a chosen sort function and return
DList* listSortNew(DList* list, DList*(*func)(DList*));

// Clear list
static void listClear(DList* list);

// Remove list
static void listDelete(DList* list);


#endif // DOUBLY_LINKED_LIST_H
