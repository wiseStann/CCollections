/*

-> Singly Linked List collection <-

This software is free and can be used and modifyied by anyone
under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3
of the License, or any later version.

[Development period] -> 13/11/19 - 20/11/19
[Author] -> Stanislav Kerimov
[Github] -> https://github.com/StarKerrr


-> Structure <-

typedef struct Node_type {
    void* data;
    struct Node_type* next;
} Node;

typedef struct SLL_type {
    size_t size;
    Node* head;
} List;


-> Macroses <-

Check Error macroses in header file.

A short description of all:
 -> [_EMPTY_LIST_ERROR], a macros for notification about empty given list
 -> [_MEMORY_ALLOCATION_ERROR], a macros for notification about memory allocation error
 -> [_INDEX_ERROR], a macros for notification about wrong given index
 -> [_VALUE_ERROR], a macros for notification about value, which is not in list

*/

#include "../include/sllist.h"

#define listSize(x) (x->size)

static List* listNew();
static Node* nodeNew(void* value);
static void listClear(List* list);
static void listDelete(List* list);
static void print(List* list, bool show_size);

void listPush(List* list, void* value);
void listPrepend(List* list, void* value);
void listInsert(List* list, size_t index, void* value);
void listRemoveEnd(List* list);
void listRemoveBegin(List* list);
void listRemoveAt(List* list, size_t index);
void listRemoveLast(List* list, void* value);
void listRemoveFirst(List* list, void* value);
void listRemoveAll(List* list, void* value);
void listReverseMut(List* list);
List* listReverseNew(List* list);
size_t listGetIndex(List* list, void* value);
void* listGetAt(List* list, size_t index);
void* listGetBegin(List* list);
void* listGetEnd(List* list);
void* listPop(List* list);
void* listPoll(List* list);
List* listCopy(List* list);
size_t listCount(List* list, void* value);
List* listSublist(List* list, size_t begin_index, size_t end_index);
bool listContains(List* list, void* value);
int listSum(List* list);
void* listMin(List* list);
void* listMax(List* list);
void listSwapByIndexes(List* list, size_t f_index, size_t s_index);
void listSwapValues(List* list, void* f_value, void* s_value);
void listReplaceByIndex(List* list, size_t index, void* value);
void listReplaceByValue(List* list, void* value_to_repl, void* value_for_repl);
void listExtend(List* f_list, List* s_list);
void swapLists(List* f_list, List* s_list);
void listSortMut(List* list, List*(*func)(List*));
List* listSortNew(List* list, List*(*func)(List*));

/*

New list creation.
> Complex time - O(n).

 Parameters [in]:
    -> NULL

 Parameters [out]:
    -> [list], a new created list

*/
static List* listNew()
{
    List* list = (List*)malloc(sizeof(List));
    if (!list) {
        _MEMORY_ALLOCATION_ERROR;
        exit(1);
    }
    list->size = 0;
    list->head = NULL;
    return list;
}

/*

New node creation.
> Complex time - O(n).

 Parameters [in]:
    -> [value], a value, which should be the data of new node

 Parameters [out]:
    -> [node], a new created node

*/
static Node* nodeNew(void* value)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        _MEMORY_ALLOCATION_ERROR;
        exit(1);
    }
    node->data = value;
    node->next = NULL;
    return node;
}

/*

Appending a given element to the end of the list.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, to the end of which the element should be appended
    -> [value], an element, which should be added to the list

 Parameters [out]:
    -> NULL
*/
void listPush(List* list, void* value)
{
    if (!list->head) {
        list->head = nodeNew(value);
    } else {
        Node* curr_node = list->head;
        while (curr_node->next) {
            curr_node = curr_node->next;
        }
        curr_node->next = nodeNew(value);
    }
    list->size++;
}

/*

Prepending a given element to the beginning of the list.
> Complex time - const.

 Parameters [in]:
    -> [list], a list, to the beg of which the element should be prepended
    -> [value], an element, which should be prepened

 Parameters [out]:
    -> NULL
*/
void listPrepend(List* list, void* value)
{
    Node* new_node = nodeNew(value);
    if (!new_node) {
        _MEMORY_ALLOCATION_ERROR;
        exit(1);
    } else if (!list->head) {
        list->head = new_node;
    } else {
        new_node->next = list->head;
        list->head = new_node;
    }
    list->size++;
}

/*

Insertion a given element to a specific position.
> Given list must not be empty.
> Index must be within the bounds of the list.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, which should be inserted by
    -> [index], a specific position, at which an element should be inserted
    -> [value], an element, which should be inserted in the list

 Parameters [out]:
    -> NULL
*/
void listInsert(List* list, size_t index, void* value)
{
    if (index == 0) {
        listPrepend(list, value);
    } else if (!list->head && index > 0) {
        _EMPTY_LIST_ERROR;
    } else if (index > list->size) {
        _INDEX_ERROR(index);
    } else {
        size_t curr_index = 1;
        Node* new_node = nodeNew(value);
        Node* curr_node = list->head;
        while (curr_node) {
            Node* next_node = curr_node->next;
            if (curr_index == index) {
                curr_node->next = new_node;
                new_node->next = next_node;
            }
            curr_node = curr_node->next;
            curr_index++;
        }
        list->size++;
    }
}

/*

Remove the last element of a given list.
> Given list must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, the last element of which should be removed

 Parameters [out]:
    -> NULL
*/
void listRemoveEnd(List* list)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR; return;
    } else if (!list->head->next) {
        free(list->head);
        list->head = NULL;
    } else {
        Node* curr_node = list->head;
        while (curr_node->next->next) {
            curr_node = curr_node->next;
        }
        free(curr_node->next);
        curr_node->next = NULL;
    }
    list->size--;
}

/*

Remove the first element of a given list.
> Given list must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, the first element of which should be removed

 Parameters [out]:
    -> NULL
*/
void listRemoveBegin(List* list)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR; return;
    } else if (list->size == 1) {
        free(list->head);
        list->head->data = NULL;
    } else {
        free(list->head);
        list->head = list->head->next;
    }
    list->size--;
}

/*

Remove an element of a given list standing at the specific position.
> Given list must not be empty.
> Given index must be within the bounds of the list.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, an element of which should be removed

 Parameters [out]:
    -> NULL
*/
void listRemoveAt(List* list, size_t index)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
    } else if (index >= list->size) {
        _INDEX_ERROR(index);
    } else if (index == 0) {
        listRemoveBegin(list);
    } else {
        size_t curr_index = 0;
        Node* curr_node = list->head;
        Node* last_node;
        while (curr_node) {
            if (curr_index == index) {
                last_node->next = curr_node->next;
            }
            last_node = curr_node;
            curr_node = curr_node->next;
            curr_index++;
        }
        list->size--;
    }
}

/*

Remove the first element of a given list with a given value.
> Given list must not be empty.
> Given value should be in the list.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, an element of which should be removed
    -> [value], a value, which should be removed from the list

 Parameters [out]:
    -> NULL
*/
void listRemoveFirst(List* list, void* value)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
    } else if (!listContains(list, value)) {
        _VALUE_ERROR(value);
    } else {
        size_t curr_index = 0;
        Node* curr_node = list->head;
        while (curr_node) {
            if (curr_node->data == value) {
                break;
            }
            curr_node = curr_node->next;
            curr_index++;
        }
        listRemoveAt(list, curr_index);
    }
}

/*

Remove the last element of a given list with a given value.
> Given list must not be empty.
> Given value should be in the list.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, an element of which should be removed
    -> [value], a value, which should be removed from the list

 Parameters [out]:
    -> NULL
*/
void listRemoveLast(List* list, void* value)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
    } else if (!listContains(list, value)) {
        _VALUE_ERROR(value);
    } else {
        size_t curr_index = 0;
        Node* curr_node = list->head;
        size_t last_index;
        while (curr_node) {
            if (curr_node->data == value) {
                last_index = curr_index;
            }
            curr_node = curr_node->next;
            curr_index++;
        }
        listRemoveAt(list, last_index);
    }
}

/*

Remove all elements of a given list with a given value.
> Given list must not be empty.
> Given value should be in the list.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, all elements with a specific value should be removed
    -> [value], all elements with this value should be removed

 Parameters [out]:
    -> NULL
*/
void listRemoveAll(List* list, void* value)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
    } else if (!listContains(list, value)) {
        _VALUE_ERROR(value);
    } else {
        size_t curr_index = 0;
        Node* curr_node = list->head;
        while (curr_node) {
            if (curr_node->data == value) {
                listRemoveAt(list, curr_index);
                curr_index--;
            }
            curr_node = curr_node->next;
            curr_index++;
        }
    }
}

/*

Reversing a given list 'in-place', i.e. the list is mutable.
> Given list must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, which should be reversed

 Parameters [out]:
    -> NULL
*/
void listReverseMut(List* list)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR; return;
    }

    Node* prev = NULL; 
    Node* current = list->head; 
    Node* next = NULL;
    while (current != NULL) { 
        next = current->next; 
        current->next = prev; 
        prev = current; 
        current = next;
    }
    list->head = prev;
}

/*

Creating a new copy, reversing it and return, i.e. not 'in-place'.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, a copy of which should be reversed and returned

 Parameters [out]:
    -> [reversed_list], reversed copy of a given list


List* listReverseNew(List* list)
{
    if (!list->head) {
        return list;
    }

    List* reversed_list = listNew();
    if (!reversed_list) {
        _MEMORY_ALLOCATION_ERROR;
        listRemove(reversed_list);
        exit(1);
    }

    reversed_list->head = list->head;
    reversed_list->size = list->size;
    listReverseMut(reversed_list);
    return reversed_list;
}
*/

/*

Getting an index of a given element, or -1 if there is no elements with a such value.
> Given list must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, an index of element of which should be returned
    -> [value], a value, the index of which should be returned

 Parameters [out]:
    -> [curr_index], an index of the given value

*/
size_t listGetIndex(List* list, void* value)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR; return -1;
    }

    size_t curr_index = 0;
    Node* curr_node = list->head;
    while (curr_node) {
        if (curr_node->data == value) {
            return curr_index;
        }
        curr_node = curr_node->next;
        curr_index++;
    }

    return -1;
}

/*

Getting a value of a given list standing at the specific position.
> Given list must not be empty.
> Given index must be within the bounds of the list.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, an element of which should be returned
    -> [index], a specific position of element, which should be returned

 Parameters [out]:
    -> [curr_node], an element standing at the specific position

*/
void* listGetAt(List* list, size_t index)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return NULL;
    } if (index >= list->size) {
        _INDEX_ERROR(index);
        return NULL;
    }

    size_t curr_index = 0;
    Node* curr_node = list->head;
    while (curr_node) {
        if (curr_index == index) {
            return curr_node->data;
        }
        curr_node = curr_node->next;
        curr_index++;
    }
    return NULL;
}

/*

Getting the first element of a given list.
> Given list must not be empty.
> Complex time - const.

 Parameters [in]:
    -> [list], a list, the first element of which should be returned

 Parameters [out]:
    -> [head], the first element of a given list

*/
void* listGetBegin(List* list)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return NULL;
    }

    void* head = list->head->data;
    return head;
}

/*

Getting the last element of a given list.
> Given list must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, the last element of which should be returned

 Parameters [out]:
    -> [tail], the last element of a given list

*/
void* listGetEnd(List* list)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return NULL;
    }
    
    Node* curr_node = list->head;
    while (curr_node->next) {
        curr_node = curr_node->next;
    }

    void* tail = curr_node->data;
    return tail;
}

/*

Remove and getting the last element of a given list.
> Given list must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, the last element of which should be removed and returned

 Parameters [out]:
    -> [end], the last element of a given list

*/
void* listPop(List* list)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return NULL;
    }
    void* end = listGetEnd(list);
    listRemoveEnd(list);
    return end;
}

/*

Remove and getting the first element of a given list.
> Given list must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, the first element of which should be removed and returned

 Parameters [out]:
    -> [end], the first element of a given list

*/
void* listPoll(List* list)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return NULL;
    }
    void* begin = listGetBegin(list);
    listRemoveBegin(list);
    return begin;
}

/*

Making and return a shallow copy of a given list.
> Complex time - const.

 Parameters [in]:
    -> [list], a list, a copy of which should be returned

 Parameters [out]:
    -> [copied_list], a copy of a given list

*/
List* listCopy(List* list)
{
    List* copied_list = listNew();
    if (!copied_list) {
        _MEMORY_ALLOCATION_ERROR;
        exit(1);
    }

    copied_list->head = list->head;
    copied_list->size = list->size;
    return copied_list;
}

/*

Counting the number of appearences of a given value in the list.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, an element of which should be counted
    -> [value], an element, number of which in the list should be returned

 Parameters [out]:
    -> [count], the number of appearences of a given element in the list

*/
size_t listCount(List* list, void* value)
{
    size_t count = 0;
    Node* curr_node = list->head;
    while (curr_node) {
        if (curr_node->data == value) {
            count++;
        }
        curr_node = curr_node->next;
    }
    return count;
}

/*

Making a sublist of a given list.
> Given list must not be empty.
> Begin index must be within of the bounds of the list and must be less than end index.
> End index must be within of the boudns of the list and must be bigger than begin index.
> Both begin and end bounds are included in sublist scope.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, the sublist of which should be returned
    -> [begin_index], left bound of a new sublist
    -> [end_index], right bound of a new sublist

 Parameters [out]:
    -> [sublist], a sublist of a given list

*/
List* listSublist(List* list, size_t begin_index, size_t end_index)
{
    
    if (!list->head || begin_index >= list->size) {
        return listNew();
    } if (end_index >= list->size && begin_index <= end_index) {
        end_index = list->size - 1;
    } if (begin_index > end_index) {
        panic("%s:%d: begin index of substr must be less than end index", __FILE__, __LINE__);
        return listNew();
    }

    List* sublist = listNew();
    size_t curr_index = 0;
    Node* curr_node = list->head;
    while (true) {
        if (curr_index >= begin_index && curr_index < end_index) {
            listPush(sublist, curr_node->data);
        }
        if (curr_index == end_index) {
            listPush(sublist, curr_node->data);
            break;
        }
        curr_node = curr_node->next;
        curr_index++;
    }
    return sublist;
}

/*

Checking if a given list contains a given value or not.
> Given list must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, which should be checked
    -> [value], a value for checking if it's in list or not

 Parameters [out]:
    -> [bool], the result of checking if a given value is in list or not

*/
bool listContains(List* list, void* value)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
    } else {
        Node* curr_node = list->head;
        while (curr_node) {
            if (curr_node->data == value) {
                return true;
            }
            curr_node = curr_node->next;
        }
    }
    return false;
}

/*

Getting the sum of all elements of a given list.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, the sum of which should be found

 Parameters [out]:
    -> [sum], the sum of all elements of a given list

*/
int listSum(List* list)
{
    if (!list->head) {
        return 0;
    }

    int sum;
    Node* curr_node = list->head;
    while (curr_node) {
        sum += (double)(int)curr_node->data;
        curr_node = curr_node->next;
    }
    return sum;
}

/*

Getting an element of a given list with the minimum value.
> Given list must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, the minimum element of which should be found

 Parameters [out]:
    -> [min_el], a minimum element of a given list

*/
void* listMin(List* list)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return NULL;
    }

    void* min_el = list->head->data;
    Node* curr_node = list->head->next;
    while (curr_node) {
        if (curr_node->data < min_el) {
            min_el = curr_node->data;
        }
        curr_node = curr_node->next;
    }
    return min_el;
}

/*

Getting an element of a given list with the maximum value.
> Given list must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, the maximum element of which should be found

 Parameters [out]:
    -> [min_el], a maximum element of a given list
    
*/
void* listMax(List* list)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return NULL;
    }

    void* max_el = list->head->data;
    Node* curr_node = list->head->next;
    while (curr_node) {
        if (curr_node->data > max_el) {
            max_el = curr_node->data;
        }
        curr_node = curr_node->next;
    }
    return max_el;
}

/*

Swappin two elements of a given list by indexes.
> Given list must not be empty.
> First index must be within the bounds of a given list.
> Second index must be within the bounds of a given list.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, two elements of which should be swapped by their indexes
    -> [f_index], index of the first element for swapping
    -> [s_index], index of the second element for swapping

 Parameters [out]:
    -> NULL
*/
void listSwapByIndexes(List* list, size_t f_index, size_t s_index)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
    } if (f_index >= list->size) {
        _INDEX_ERROR(f_index);
    } else if (s_index >= list->size) {
        _INDEX_ERROR(s_index);
    } else {
        void* f_value = listGetAt(list, f_index);
        void* s_value = listGetAt(list, s_index);

        listReplaceByIndex(list, f_index, s_value);
        listReplaceByIndex(list, s_index, f_value);
    }
}

/*

Swappin two elements of a given list by values.
> Given list must not be empty.
> First value must be in a given list.
> Second value must be in a given list.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, two elements of which should be swapped
    -> [f_value], value of the first element for swapping
    -> [s_value], value of the second element for swapping

 Parameters [out]:
    -> NULL
*/
void listSwapValues(List* list, void* f_value, void* s_value)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
    } if (!listContains(list, f_value)) {
        _VALUE_ERROR(f_value);
    } else if (!listContains(list, s_value)) {
        _VALUE_ERROR(s_value);
    } else {
        // Getting indexes of given values
        size_t f_index = listGetIndex(list, f_value);
        size_t s_index = listGetIndex(list, s_value);

        listReplaceByIndex(list, f_index, s_value);
        listReplaceByIndex(list, s_index, f_value);
    }
}

/*

Replacing an element of a given list by index.
> Given list must not be empty.
> Given index must be within the bounds of a given list.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, an element of which should be replaced by index
    -> [index], an index of element, which should be replaced
    -> [value], a new value for an element, which should be replaced

 Parameters [out]:
    -> NULL
*/
void listReplaceByIndex(List* list, size_t index, void* value)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
    } if (index >= list->size) {
        _INDEX_ERROR(index);
    } else {
        size_t curr_index = 0;
        Node* curr_node = list->head;
        while (true) {
            if (curr_index == index) {
                curr_node->data = value;
                break;
            }
            curr_node = curr_node->next;
            curr_index++;
        }
    }
}

/*

Replacing an element of a given list by value.
> Given list must not be empty.
> Given value for replacing must be in a given list.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, an element of which should be replaced by index
    -> [value_to_repl], a value of an element, which should be replaced
    -> [value_for_repl], a new value for an element, which should be replaced

 Parameters [out]:
    -> NULL
*/
void listReplaceByValue(List* list, void* value_to_repl, void* value_for_repl)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
    } if (!listContains(list, value_to_repl)) {
        _VALUE_ERROR(value_to_repl);
    } else {
        Node* curr_node = list->head;
        while (true) {
            if (curr_node->data == value_to_repl) {
                curr_node->data = value_for_repl;
                break;
            }
            curr_node = curr_node->next;
        }
    }
}

/*

Extending a given list by another one.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, which should be extended
    -> [s_list], a second list by which the first one should be extended

 Parameters [out]:
    -> NULL
*/
void listExtend(List* f_list, List* s_list)
{
    if (!f_list->head) {
        f_list->head = s_list->head;
        f_list->size = s_list->size;
    } else {
        Node* curr_node = f_list->head;
        Node* s_list_node = s_list->head;
        
        while (curr_node->next) {
            curr_node = curr_node->next;
        }
        for (int i = 0; i < s_list->size; i++) {
            curr_node->next = s_list_node;
            curr_node = curr_node->next;
            s_list_node = s_list_node->next; 
        }
    }
}

/*

Swapping two given lists.
> Complex time - const.

 Parameters [in]:
    -> [f_list], first list for swapping
    -> [s_list], second list for swapping

 Parameters [out]:
    -> NULL
*/
void swapLists(List* f_list, List* s_list)
{
    Node* temp_head = f_list->head;
    size_t temp_size = f_list->size;

    f_list->head = s_list->head;
    f_list->size = s_list->size;

    s_list->head = temp_head;
    s_list->size = temp_size;
}

/*

Sorting a given list 'in-place', i.e. the list is mutable.
> Type of a given data structure must be List.
> Complex time - depending on what kind of sorting algorithm is used here.

 Parameters [in]:
    -> [list], a list, which should be sorted by a given function
    -> [func], a function, which should sort a given list

 Parameters [out]:
    -> NULL
*/
void listSortMut(List* list, List*(*func)(List*))
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
    } else {
        func(list);
    }
}

/*

Creating a copy of a given list, sorting it and return.
> Given list must not be empty.
> Type of a given data structure must be List.
> Complex time - depending on what kind of sorting algorithm is used here.

 Parameters [in]:
    -> [list], a list, a copy of which sould be sorted
    -> [func], a function, which should sort a given list

 Parameters [out]:
    -> [new_list], a sorted copy of given list

*/
List* listSortNew(List* list, List*(*func)(List*))
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return listNew();
    }

    func(list);

    // Creating new list
    List* new_list = listNew();
    new_list->size = list->size;
    new_list->head = list->head;

    return new_list;
}

/*

Clearing a given list without deleting allocated memory, shallow clearing.
> Given list must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, which should be shallowly cleared

 Parameters [out]:
    -> NULL
*/
static void listClear(List* list)
{
    if (!list->head) {
        panic("%s:%d: cannot clear empty list", __FILE__, __LINE__);
        exit(1);
    }

    while (list->head->next) {
        list->head = list->head->next;
    }
    list->head = NULL;
    list->size = 0;
}

/*

Clearing all memory that was allocated for the list.
> Given list must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, which should be removed

 Parameters [out]:
    -> NULL
*/
static void listDelete(List* list)
{
    if (!list->head) {
        panic("%s:%d: cannot remove empty list", __FILE__, __LINE__);
        exit(1);   
    }

    Node* curr_node = list->head;
    Node* next;
    while (curr_node) {
        next = curr_node->next;
        free(curr_node);
        curr_node = next;
    }
    list->head = NULL;
    list->size = 0;
}
