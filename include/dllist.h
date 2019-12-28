/* Insides of Doubly Linked List data structure */

#include "basic.h"

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#define dlistSize(x) (x->size)

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
DList* dlistNew();

// New node creation
Node* dnodeNew(void* value);

// Appending an element to the end of the list
void dlistPush(DList* list, void* value);

// Appending an element to the beginning of the list
void dlistPrepend(DList* list, void* value);

// Inserting an element at the specific position
void dlistInsert(DList* list, void* value, size_t index);

// Remove last element of the list
void dlistRemoveEnd(DList* list);

// Remove the first element of thee list
void dlistRemoveBegin(DList* list);

// Remove an element standing at the specific position
void dlistRemoveAt(DList* list, size_t index);

// Remove last element of the given list
void dlistRemoveLast(DList* list, void* value);

// Remove the first element of the given list
void dlistRemoveFirst(DList* list, void* value);

// Remove all elements with a given value
void dlistRemoveAll(DList* list, void* value);

// Getting index of a given element
size_t dlistGetIndex(DList* list, void* value);

// Getting value standing on a specific position
void* dlistGetAt(DList* list, size_t index);

// Getting the first element of a given list
void* dlistGetBegin(DList* list);

// Getting the last element of a given list
void* dlistGetEnd(DList* list);

// Remove the last element from list and return it
void* dlistPop(DList* list);

// Remove the first element from list and return it
void* dlistPoll(DList* list);

// Getting the number of elements of the list with a given value
size_t dlistCount(DList* list, void* value);

// Getting a substring from list, something like python's slice
DList* dlistSublist(DList* list, size_t begin_index, size_t end_index);

// Check if list contains given element or not
bool dlistContains(DList* list, void* value);

// Making a shallow copy of a given list
DList* dlistCopy(DList* list);

// Reversing an list in-place 
void dlistReverseMut(DList* list);

// Creating a copy, reversing it and return
DList* dlistReverseNew(DList* list);

// Swapping two elements by the given indexes
void dlistSwapByIndexes(DList* list, size_t f_index, size_t s_index);

// Swapping two first elements with the given values
void dlistSwapValues(DList* list, void* f_value, void* s_value);

// Replacing an element by index
void dlistReplaceByIndex(DList* list, size_t index, void* value);

// Replacing an element by value
void dlistReplaceByValue(DList* list, void* value_to_repl, void* value_for_repl);

// Extending one list by another one
void dlistExtend(DList* f_list, DList* s_list);

// Swapping two lists
void dswapLists(DList* f_list, DList* s_list);

// Clear list
void dlistClear(DList* list);

// Remove list
void dlistDelete(DList* list);


#endif // DOUBLY_LINKED_LIST_H
