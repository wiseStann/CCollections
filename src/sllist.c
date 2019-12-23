/*

-> Singly Linked List collection <-

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

#include "../include/sllist.h"

#define listSize(x) (x->size)

static List* listNew();
static Node* nodeNew(void* value);
static void listClear(List* list);
static void listDelete(List* list);

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
List* listShallCopy(List* list);
List* listDeepCopy(List* list);
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
> Complex time - const.

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
    list->tail = NULL;
    return list;
}

/*

New node creation.
> Complex time - const.

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
    
    /*  So now we have a new node like that:
     *      |NEW NODE(value)| -> NULL
     */
    
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
    /*  If the list is absolutely empty, we create the head.
       Also we assign the value of the head to the tail */ 
    if (!list->head) {
        list->head = nodeNew(value);
        list->tail = list->head;
    } else {
    /*  Because we want to append an item to the end of the list, we
     * have to traverse it to the end.
     */ 
        Node* curr_node = list->head;
        while (curr_node->next) {
            curr_node = curr_node->next;
        }
        
    /*  Now we create a new node, assign it to the tail of the list
     * and connect the last one to the new tail.
     *
     *   head             tail          |new node|
     *  | 1 | -> | 2 | -> | 3 | -> NULL     v
     *
     */
        list->tail = nodeNew(value);
        curr_node->next = list->tail;
    }
    /*  Now our list looks like that:
     *  | 1 | -> | 2 | -> | 3 | -> |new node| -> NULL
     */
    
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
    /*  Create a new node that should be prepended to the list, i.e:
     *
     *  |new node|                     * LIST *
     *      |       head                                        tail
     *      V      | 1 | -> | 2 | -> | 3 | -> | 4 | -> | 5 | -> | 6 |
     *
     */
    Node* new_node = nodeNew(value);
    
    if (!list->head) {
        list->head = new_node;
    } else {
        new_node->next = list->head;
        list->head = new_node;
    }
    /*  Now we have the next case:
     *      head                                                    tail 
     *  |new node| -> | 1 | -> | 2 | -> | 3 | -> | 4 | -> | 5 | -> | 6 |
     */
    
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
void listInsert(List* list, void* value, size_t index)
{
    // If a given index is 0 then we just prepend new node to the list
    if (index == 0) {
        listPrepend(list, value);
    // Some error cases
    } else if (!list->head && index > 0) {
        _EMPTY_LIST_ERROR;
    } else if (index > list->size) {
        _INDEX_ERROR(index);
    } else {
        
        /*  We start the counter and increment it every time. When the counter
         * will be equal to given index, we split two nodes, i.e. disconnect
         * the first node standing on the given index from the second and insert a new one between them, i.e:
         * 
         *       head                *LIST*         tail
         *      | 1 | -> | 2 | -> | 3 | -> | 4 | -> | 5 | -> NULL
         *   |                                            
         *   V   head                   |new node|          tail
         *      | 1 | -> | 2 | -> | 3 |      v     | 4 | -> | 5 | -> NULL
         *   |
         *   V   head                                             tail
         *      | 1 | -> | 2 | -> | 3 | -> |new node| -> | 4 | -> | 5 | -> NULL 
         * 
         *  For insert operation we just connect left node (in our case 3) to a new one
         * and a new one connect to the right node (in out case 4).
         */
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
        // Traverse the list to the end
        Node* curr_node = list->head;
        while (curr_node->next->next) {
            curr_node = curr_node->next;
        }
        // Free the last node, i.e. clear allocated memory
        free(curr_node->next);
        // Equate this node to NULL, in order to make right border of list
        curr_node->next = NULL;
        
        /*      head             tail
         *     | 1 | -> | 2 | -> | 3 | -> NULL
         *  |
         *  V   head    tail
         *     | 1 | -> | 2 | -> NULL
         */
    }
    list->size--;
}

/*

Remove the first element of a given list.
> Given list must not be empty.
> Complex time - const.

 Parameters [in]:
    -> [list], a list, the first element of which should be removed

 Parameters [out]:
    -> NULL
*/
void listRemoveBegin(List* list)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR; return;
    } else {
        
        /*  Create a new variable equals to node standing after the head node,
         * Free head node, i.e. clear allocated memory, assign the next_node to
         * the head of list, so now the head of list is the second node in initial list.
         */
        Node* next_node = list->head->next;
        free(list->head);
        list->head = next_node;
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
        
        /*  We start the counter and increment it every time. When it will be equal to 
         * a given index, we connect left and right neighbours of the node with this index
         * together. Thus, the node, index of which was given, just goes out of linked list:
         *      head                                                 tail
         *     | 1 | -> | 2 | -> | 3 | -> | 4 | -> | 5 | -> | 6 | -> | 7 | -> NULL
         *  |
         *  V   head                                                            tail
         *     | 1 | -> | 2 | -> | 3 | -> | 4 | -> |Desirable Node| -> | 6 | -> | 7 | -> NULL
         *  |
         *  V   head                                        tail  
         *     | 1 | -> | 2 | -> | 3 | -> | 4 | -> | 6 | -> | 7 | -> NULL
         */
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
    } else if (list->head->data == value) {
        listRemoveBegin(list);
    } else {
        
        /*  We traverse the list and search a node with a given value. When it is found, 
         * we connect left and right neighbours of this node together and break the loop.
         * Thus, the node, the value of which was given, just goes out of linked list:
         *      head                                                 tail
         *     | 1 | -> | 2 | -> | 3 | -> | 4 | -> | 5 | -> | 6 | -> | 7 | -> NULL
         *  |
         *  V   head                                                            tail 
         *     | 1 | -> | 2 | -> | 3 | -> | 4 | -> |Desirable Node| -> | 6 | -> | 7 | -> NULL
         *  |
         *  V   head                                        tail  
         *     | 1 | -> | 2 | -> | 3 | -> | 4 | -> | 6 | -> | 7 | -> NULL
         */
        Node* curr_node = list->head;
        Node* last_node;
        while (curr_node) {
            if (curr_node->data == value) {
                last_node->next = curr_node->next;
                break;
            }
            last_node = curr_node;
            curr_node = curr_node->next;
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
void listRemoveLast(List* list, void* value)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
      // If list doesn't contain an item then just throw the error
    } else if (!listContains(list, value)) {
        _VALUE_ERROR(value);
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
      // If list doesn't contain an item then just throw the error
    } else if (!listContains(list, value)) {
        _VALUE_ERROR(value);
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
    
    /* 
     *   Check out this video for detailed explanation:
     *   https://www.youtube.com/watch?v=O0By4Zq0OFc
     */
    Node* current = list->head; 
    Node* next = NULL;
    Node* prev = NULL;
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

*/
List* listReverseNew(List* list)
{
    if (!list->head) {
        return list;
    }
    
    /*  We make a shallow copy of a given list and
     * and reverse it.
     *  We can't apply deep copy here because we want that
     * further manipulations with reversed list don't affect
     * the given list.
     */ 
    List* reversed_list = listShallCopy(list);
    listReverseMut(reversed_list);
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
size_t listGetIndex(List* list, void* value)
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
void* listGetAt(List* list, size_t index)
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
void* listGetBegin(List* list)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return NULL;
    }
    
    // Just directly get the data of the head node of the list and return it
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
void* listGetEnd(List* list)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return NULL;
    }
    
    // Just directly get the data of the tail node of the list and return it
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
void* listPop(List* list)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return NULL;
    }
    
    // Get the tail of the list
    void* end = listGetEnd(list);
    // Remove the tail of the list making the previous element as the tail
    listRemoveEnd(list);
    return end;
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
void* listPoll(List* list)
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return NULL;
    }
    
    // Get the head of the list
    void* begin = listGetBegin(list);
    // Remove the head of the list making the next element as the head
    listRemoveBegin(list);
    return begin;
}

/*

Making and return a shallow copy of a given list.
> Complex time - O(n).

 Parameters [in]:
    -> [list], a list, a shallow copy of which should be returned

 Parameters [out]:
    -> [copied_list], a shallow copy of a given list

*/
List* listShallCopy(List* list)
{
    if (!list->head) {
        return listNew();
    }
    
    /*  Creating a new list and copying all elements from
       the old one to the new.
     */
    List* copied_list = listNew();
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
List* listDeepCopy(List* list)
{
    if (!list->head) {
        return list;
    }

    List* copied_list = listNew();
    
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
    -> [count], the number of appearences of a given element in the list

*/
size_t listCount(List* list, void* value)
{
    /*  We start the counter and increment it every time when
     * the value of current node is equal to the given value.
     */
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
bool listContains(List* list, void* value)
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

Swappin two elements of a given list by indexes.
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
> Second index must be in a given list.
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
void listExtend(List* f_list, List* s_list)
{
    if (!f_list->head) {
        f_list->head = s_list->head;
        f_list->size = s_list->size;
    } else {
        Node* curr_node = f_list->head;
        Node* s_list_node = s_list->head;
        
        /*  Iterate over the list until we get to the end in order
         * to add nodes from the second list to the last node of the first one.
         */
        while (curr_node->next) {
            curr_node = curr_node->next;
        }
        
        /*  Appending nodes from the second list to the first list
         * thereby extending the first one.
         */
        while (s_list_node) {
            curr_node->next = s_list_node;
            curr_node = curr_node->next;
            s_list_node = s_list_node->next;
            f_list->size++;
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
    
    /*  Just swap the head nodes of two lists.
     */
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
List* listSortNew(List* list, List*(*func)(List*))
{
    if (!list->head) {
        _EMPTY_LIST_ERROR;
        return listNew();
    }

    // Create a shallow copy of a give list
    List* sorted_list = listShallCopy(list);
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

Clearing a given list with deleting allocated memory, actually remove.
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
