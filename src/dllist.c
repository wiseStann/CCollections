/*

-> Doubly Linked List collection <-

This software is free and can be used and modifyied by anyone
under the terms of the GNU Lesser General Public License as
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
    Node* tail;
} List;


-> Macroses <-

Check Error macroses in "include/utils/basic.h" header file.

A short description of all:
 -> [_EMPTY_LIST_ERROR], a macros for notification about empty given list
 -> [_MEMORY_ALLOCATION_ERROR], a macros for notification about memory allocation error
 -> [_INDEX_ERROR], a macros for notification about wrong given index
 -> [_VALUE_ERROR], a macros for notification about value, which is not in list
 
*/

#include "../include/dllist.h"

static DList* listNew();
static Node* nodeNew(void* value);
static void listClear(DList* list);
static void listDelete(DList* list);

void listPush(DList* list, void* value);
void listPrepend(DList* list, void* value);
void listInsert(DList* list, void* value, size_t index);
void listRemoveEnd(DList* list);
void listRemoveBegin(DList* list);
void listRemoveAt(DList* list, size_t index);
void listRemoveLast(DList* list, void* value);
void listRemoveFirst(DList* list, void* value);
void listRemoveAll(DList* list, void* value);
DList* listReverseNew(DList* list);
size_t listGetIndex(DList* list, void* value);
void* listGetAt(DList* list, size_t index);
void* listGetBegin(DList* list);
void* listGetEnd(DList* list);
void* listPop(DList* list);
void* listPoll(DList* list);
DList* listShallCopy(DList* list);
DList* listDeepCopy(DList* list);
size_t listCount(DList* list, void* value);
DList* listSublist(DList* list, size_t begin_index, size_t end_index);
bool listContains(DList* list, void* value);
void listSwapByIndexes(DList* list, size_t f_index, size_t s_index);
void listSwapValues(DList* list, void* f_value, void* s_value);
void listReplaceByIndex(DList* list, size_t index, void* value);
void listReplaceByValue(DList* list, void* value_to_repl, void* value_for_repl);
void listExtend(DList* f_list, DList* s_list);
void swapLists(DList* f_list, DList* s_list);
void listSortMut(DList* list, DList*(*func)(DList*));
DList* listSortNew(DList* list, DList*(*func)(DList*));

/*
    Features which will be added/fixed soon:
   - void listReverseMut(DList* list);
   - void listSortMut(DList* list, DList*(*func)(DList*));
   - DList* listSortNew(DList* list, DList*(*func)(DList*));
*/


/*

New list creation.
> Complex time - O(n).

 Parameters [in]:
    -> NULL

 Parameters [out]:
    -> [list], a new created list

*/
static DList* listNew()
{
    DList* new_list = (DList*)malloc(sizeof(DList));
    if (!new_list) {
        free(new_list);
        _MEMORY_ALLOCATION_ERROR;
        exit(1);
    }

    new_list->size = 0;
    new_list->head = NULL;
    new_list->tail = NULL;

    return new_list;
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
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        free(new_node);
        _MEMORY_ALLOCATION_ERROR;
        exit(1);
    }

	new_node->data = value;
	new_node->next = NULL;
	new_node->prev = NULL;

    return new_node;
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
void listPush(DList* list, void* value)
{
	if (!list->head) {
		list->head = nodeNew(value);
        list->tail = list->head;
	} else {
		Node* curr_node = list->head;
		while (curr_node->next) {
			curr_node = curr_node->next;
		}

		curr_node->next = nodeNew(value);
		curr_node->next->prev = curr_node;
        list->tail = curr_node->next;
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
void listPrepend(DList* list, void* value)
{
    Node* new_node = nodeNew(value);
    if (!list->head) {
        list->head = new_node;
        list->tail = list->head;
    } else {
        new_node->next = list->head;
        list->head->prev = new_node;
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
void listInsert(DList* list, void* value, size_t index)
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
                new_node->prev = curr_node;
                new_node->next = next_node;
                if (index < listSize(list)) {
                    next_node->prev = new_node;
                }
            }
            curr_node = curr_node->next;
            curr_index++;
        }

        if (index == listSize(list)) {
            list->tail = new_node;
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
void listRemoveEnd(DList* list)
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
        list->tail = curr_node;
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
void listRemoveBegin(DList* list)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR; return;
    } else if (list->size == 1) {
        free(list->head);
        free(list->tail);
        list->head->data = NULL;
        list->tail->data = NULL;
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
void listRemoveAt(DList* list, size_t index)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
    } else if (index >= list->size) {
        _INDEX_ERROR(index);
    } else if (index == 0) {
        listRemoveBegin(list);
    } else if (index == list->size - 1) {
        listRemoveEnd(list);
    } else {
        size_t curr_index = 0;
        Node* curr_node = list->head;
        Node* last_node;
        while (curr_node) {
            if (curr_index == index) {
                last_node->next = curr_node->next;
                curr_node->next->prev = last_node;
            }
            last_node = curr_node;
            curr_node = curr_node->next;
            curr_index++;
        }
        list->size--;
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
void listRemoveLast(DList* list, void* value)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
      // If list doesn't contain an item then just throw the error
    } else if (!listContains(list, value)) {
        _VALUE_ERROR;
    } else {

        /*  We start the counter and increment it every time. When the value of current node
         * is equal to a given value, we assign the value of counter to special variable 'last_index'.
         * So, when the loop ends, this variable will store the index of the element with given value
         * with the last occurrence.
         */
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
        // And now we just invoke 'listRemoveAt' function with last_index as a parameter
        listRemoveAt(list, last_index);
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
void listRemoveFirst(DList* list, void* value)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
    } else if (!listContains(list, value)) {
        _VALUE_ERROR;
    } else if (list->head->data == value) {
        listRemoveBegin(list);
    } else {
        size_t curr_index = 0;
        Node* curr_node = list->head;
        while (curr_node) {
            if (curr_node->data == value) {
                listRemoveAt(list, curr_index);
                break;
            }
            curr_node = curr_node->next;
            curr_index++;
        }
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
void listRemoveAll(DList* list, void* value)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
      // If list doesn't contain an item then just throw the error
    } else if (!listContains(list, value)) {
        _VALUE_ERROR;
    } else {

        /*  We start the counter and increment it every time. When the value of current node
         * is equal to a given value, we invoke 'listRemoveAt' function with the counter as the parameter
         * and remove the node which is standing at the index with the counter value.
         */
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

Creating a new copy, reversing it and return, i.e. not 'in-place'.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, a copy of which should be reversed and returned

 Parameters [out]:
    -> [reversed_list], reversed copy of a given list

*/
DList* listReverseNew(DList* list)
{
    if (!list->head) {
        return list;
    }

    DList* reversed_list = listNew();
    Node* curr_node = list->tail;
    while (curr_node) {
        listPush(reversed_list, curr_node->data);
        curr_node = curr_node->prev;
    }

    return reversed_list;
}

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
size_t listGetIndex(DList* list, void* value)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return -1;
    }

    /*  We start the counter and increment it every time. When the value of given
     * node is equal to a given value, we return the value of counter. This way we
     * can find index of element easily.
     */
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
void* listGetAt(DList* list, size_t index)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return NULL;
      // If a given index is bigger than the list size then throw the error
    } if (index >= list->size) {
        _INDEX_ERROR(index);
        return NULL;
    }

    /*  We start the counter and increment it every time. When the counter is
     * equal to a given index, we return the data of node standing at the
     * corresponding position.
     */
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
void* listGetBegin(DList* list)
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
> Complex time - const.

 Parameters [in]:
    -> [list], a list, the last element of which should be returned

 Parameters [out]:
    -> [tail], the last element of a given list

*/
void* listGetEnd(DList* list)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return NULL;
    }

    void* tail = list->tail->data;
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
void* listPop(DList* list)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return NULL;
    }

    // Getting the last element of the list
    void* tail = listGetEnd(list);
    // Remove the tail of the list making the previous element as the tail
    listRemoveEnd(list);
    return tail;
}

/*

Remove and getting the first element of a given list.
> Given list must not be empty.
> Complex time - const.

 Parameters [in]:
    -> [list], a list, the first element of which should be removed and returned

 Parameters [out]:
    -> [end], the first element of a given list

*/
void* listPoll(DList* list)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return NULL;
    }

    // Getting the first element of the list
    void* head = listGetBegin(list);
    // Remove the head of the list making the next element as the head
    listRemoveBegin(list);
    return head;
}

/*

Making and return a shallow copy of a given list.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, a shallow copy of which should be returned

 Parameters [out]:
    -> [copied_list], a shallow copy of a given list

*/
DList* listShallCopy(DList* list)
{
    if (!list->head) {
        return listNew();
    }

    /*  Creating a new list and copying all elements from
       the old one to the new.
     */
    DList* copied_list = listNew();
    Node* curr_node = list->head;
    while (curr_node) {
        listPush(copied_list, curr_node->data);
        curr_node = curr_node->next;
    }
    return copied_list;
}

/*

Making and return a deep copy of a given list.
> Complex time - const.

 Parameters [in]:
    -> [list], a list, a deep copy of which should be returned

 Parameters [out]:
    -> [copied_list], a deep copy of a given list

*/
DList* listDeepCopy(DList* list)
{
    if (!list->head) {
        return list;
    }

    DList* copied_list = listNew();

    /*  Here we directly assign the head node of a given list
     * to the head of a new one, that's why all changes in the new list
     * will affect the old one.
     */
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
    -> [counter], the number of appearences of a given element in the list

*/
size_t listCount(DList* list, void* value)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return 0;
    }

    size_t counter = 0;
    Node* curr_node = list->head;
    while (curr_node) {
        if (curr_node->data == value) {
            counter++;
        }
        curr_node = curr_node->next;
    }
    return counter;
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
DList* listSublist(DList* list, size_t begin_index, size_t end_index)
{
    if (!list->head || begin_index >= list->size) {
        return listNew();
    } if (end_index >= list->size && begin_index <= end_index) {
        end_index = list->size - 1;
    } if (begin_index > end_index) {
        panic("%s:%d: begin index of substr must be less than end index", __FILE__, __LINE__);
        return listNew();
    }

    DList* sublist = listNew();

    /*  We start the counter (current index of element in list) and
     * start infinite loop. When the counter is within the bounds of two
     * given indexes we push current element into the new list. When current
     * index (counter) is equal to end index (border) then we push current
     * element into the list and break the loop. Thus, the list that will be
     * returned will contain all elements from the given list from 'begin index'
     * to 'end index' inclusively.
     */
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
bool listContains(DList* list, void* value)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
    } else {

        /*  We iterate over the given list and every time check
         * if the value of current node is equal to the given value.
         * If it's true then the list contains this value, else not.
         */
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

Swapping two elements of a given list by indexes.
> Given list must not be empty.
> First index must be within the bounds of a given list.
> Second index must be within the bounds of a given list.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, two elements of which should be swapped
    -> [f_index], index of the first element for swapping
    -> [s_index], index of the second element for swapping

 Parameters [out]:
    -> NULL
*/
void listSwapByIndexes(DList* list, size_t f_index, size_t s_index)
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

Swapping two elements of a given list by values.
> Given list must not be empty.
> First value must be in a given list.
> Second index must be in a given list.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, two elements of which should be swapped
    -> [f_value], value of the first element for swapping
    -> [s_value], value of the second element for swapping

 Parameters [out]:
    -> NULL
*/
void listSwapValues(DList* list, void* f_value, void* s_value)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
    } if (!listContains(list, f_value)) {
        _VALUE_ERROR;
    } else if (!listContains(list, s_value)) {
        _VALUE_ERROR;
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
void listReplaceByIndex(DList* list, size_t index, void* value)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
    } if (index >= list->size) {
        _INDEX_ERROR(index);
    } else {

        /*  We start the counter (current index of element) and increment
         * it every time. When the counter value is equal to a given index,
         * we change the value of current node to a given value thereby replacing
         * an old one by a new one.
         */
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
void listReplaceByValue(DList* list, void* value_to_repl, void* value_for_repl)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
    } if (!listContains(list, value_to_repl)) {
        _VALUE_ERROR;
    } else {

        /*  We iterate over the list and compare current node value to a
         * given value that should be replaced. If current node is equal to
         * a given value, we replace the value of this node by another given value.
         */
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
void listExtend(DList* f_list, DList* s_list)
{
    if (!f_list->head) {
        f_list->head = s_list->head;
        f_list->size = s_list->size;
    } else {
        /*  Appending nodes from the second list to the first list
         * thereby extending the first one.
         */
        Node* s_list_node = s_list->head;
        while (s_list_node) {
            listPush(f_list, s_list_node->data);
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
void swapLists(DList* f_list, DList* s_list)
{
    Node* temp_head = f_list->head;
    Node* temp_tail = f_list->tail;
    size_t temp_size = f_list->size;
    
    // Just swap the head nodes of two lists.
    f_list->head = s_list->head;
    f_list->tail = s_list->tail;
    f_list->size = s_list->size;

    s_list->head = temp_head;
    s_list->tail = temp_tail;
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
void listSortMut(DList* list, DList*(*func)(DList*))
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
    }
    
    func(list);
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
DList* listSortNew(DList* list, DList*(*func)(DList*))
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return listNew();
    }

    // Create a shallow copy of a give list
    DList* sorted_list = listShallCopy(list);
    func(sorted_list);

    return sorted_list;
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
static void listClear(DList* list)
{
    if (!list->head) {
        panic("%s:%d: cannot clear empty list", __FILE__, __LINE__);
        exit(1);
    }

    while (list->head->next) {
        list->head = list->head->next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

/*

Clearing a given list with deleting allocated memory, actually remove.
> Given list must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, which should be removed

 Parameters [out]:
    -> NULL
*/
static void listDelete(DList* list)
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
    list->tail = NULL;
    list->size = 0;
}
