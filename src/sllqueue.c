/*

-> Queue collection (Base: Singly Linked List) <-

This software is free and can be used and modifyied by anyone
under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3
of the License, or any later version.

[Development period] -> 25/11/19 - 26/11/19
[Author] -> Stanislav Kerimov
[Github] -> https://github.com/StarKerrr


-> Structure <-

typedef struct Node_type {
    void* data;
    struct Node_type* next;
} Node;

typedef struct Queue_type {
    size_t size;
    Node* front;
    Node* back;
} Queue;


-> Macroses <-

 -> [_MEMORY_ALLOCATION_ERROR], a macros for notification about memory allocation error

*/

#include "../include/sllqueue.h"


static Queue* queueNew();
static Queue* queueFromArr(int* array, int size);
static Node* nodeNew(void* value);
static void queueClear(Queue* queue);
static void queueDelete(Queue* queue);

void enqueue(Queue* queue, void* item);
void* dequeue(Queue* queue);
void* queueFront(Queue* queue);
void* queueRear(Queue* queue);
size_t queueSize(Queue* queue);
bool queueIsEmpty(Queue* queue);
bool queueIsFull(Queue* queue);
bool queueSizeIsValid(Queue* queue);


/*

New queue creation.
> Complex time - O(n).

 Parameters [in]:
    -> NULL

 Parameters [out]:
    -> [queue], a new created queue

*/
static Queue* queueNew()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (!queue) {
        _MEMORY_ALLOCATION_ERROR;
        exit(1);
    }
    queue->size = 0;
    queue->front = NULL;
    queue->back = NULL;
    return queue;
}

/*

Making a queue from a given array.
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array, which is the base for a new queue

 Parameters [out]:
    -> [queue], the queue, which should be made with the given array

*/
static Queue* queueFromArr(int* array, int size)
{   
    Queue* queue = queueNew();

    for (int i = 0; i < size; i++) {
        enqueue(queue, (void*)(size_t)array[i]);
    }
    return queue;
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
    node->value = value;
    node->next = NULL;
    return node;
}

/*

Appending new element to the end of a given queue.
> Complex time - O(n).

 Parameters [in]:
    -> [queue], a queue, to which an element should be appended
    -> [item], an item, which should be appended to the queue
 Parameters [out]:
    -> NULL
*/
void enqueue(Queue* queue, void* item)
{
    if (!queue->front) {
        queue->front = nodeNew(item);
        queue->back = queue->front;
    } else if (queue->size == MAXSIZE) {
        panic("%s:%d: max size of elements is reached", __FILE__, __LINE__);
        exit(1);
    } else {
        Node* curr_node = queue->front;
        while (curr_node->next) {
            curr_node = curr_node->next;
        }
        curr_node->next = nodeNew(item);
        queue->back = curr_node->next;
    }
    queue->size++;
}

/*

Remove and return the front of a given queue.
> Given queue must not be empty.
> Complex time - const.

 Parameters [in]:
    -> [queue], a queue, from which the front should be removed and returned

 Parameters [out]:
    -> [front], the first element of queue, which should be removed and returned

*/
void* dequeue(Queue* queue)
{
    if (!queue->front) {
        return NULL;
    }

    void* front = queue->front->value;
    queue->front = queue->front->next;
    queue->size--;
    return front;
}

/*

Getting the front element of a given queue.
> Given queue must not be empty.
> Complex time - const.

 Parameters [in]:
    -> [queue], a queue, the front of which should be got

 Parameters [out]:
    -> [front], the front element of queue

*/
void* queueFront(Queue* queue)
{
    if (!queue->front) {
        return NULL;
    }

    void* front = queue->front->value;
    return front;
}

/*

Getting the last element of a given queue.
> Given queue must not be empty.
> Complex time - const.

 Parameters [in]:
    -> [queue], a queue, the last element of which should be returned

 Parameters [out]:
    -> [back], the last element of the given queue

*/
void* queueRear(Queue* queue)
{
    if (!queue->front) {
        return NULL;
    }

    void* back = queue->back->value;
    return back;
}

/*

Getting the size of a given queue.
> Complex time - const.

 Parameters [in]:
    -> [queue], a queue, the size of which should be returned

 Parameters [out]:
    -> [queue_size], the size of the given queue

*/
size_t queueSize(Queue* queue)
{
    size_t queue_size = queue->size;
    return queue_size;
}

/*

Checking if a given queue is full or not.
> Complex time - const.

 Parameters [in]:
    -> [queue], a queue, which should be checked

 Parameters [out]:
    -> [bool], get value 'true' if queue is empty and 'false' otherwise

*/
bool queueIsEmpty(Queue* queue)
{
    if (queue->size == 0)
        return true;
    return false;
}

/*

Checking if a given queue is empty or not.
> Complex time - const.

 Parameters [in]:
    -> [queue], a queue, which should be checked

 Parameters [out]:
    -> [bool], get value 'true' if queue is full and 'false' otherwise

*/
bool queueIsFull(Queue* queue)
{
    if (queue->size < MAXSIZE)
        return false;
    return true;
}

/*

Checking if the size of a given queue is less than MAXSIZE.
> Complex time - const.

 Parameters [in]:
    -> [queue], a queue, the size of which should be checked

 Parameters [out]:
    -> [bool], get value 'true' if the size is less than MAXSIZE and 'false' otherwise

*/
bool queueSizeIsValid(Queue* queue)
{
    if (queue->size <= MAXSIZE)
        return true;
    return false;
}

/*
 
Clearing a given queue without deleting allocated memory.
> Complex time - O(n).

 Parameters [in]:
    -> [queue], a queue, which should be cleared

 Parameters [out]:
    -> NULL
*/
static void queueClear(Queue* queue)
{
    if (!queue->front) {
        panic("%s:%d: cannot clear empty queue", __FILE__, __LINE__);
        exit(1);          
    }

    while (queue->front->next) {
        queue->front = queue->front->next;
    }
    queue->front = NULL;
    queue->size = 0;
}

/*

Clearing all memory that was allocated for the queue.
> Complex time - O(n).

 Parameters [in]:
    -> [queue], a queue, which should be deleted

 Parameters [out]:
    -> NULL
*/
static void queueDelete(Queue* queue)
{
    if (!queue->front) {
        panic("%s:%d: cannot remove empty queue", __FILE__, __LINE__);
        exit(1);   
    }

    Node* curr_node = queue->front;
    Node* next;
    while (curr_node) {
        next = curr_node->next;
        free(curr_node);
        curr_node = next;
    }
    queue->front = NULL;
    queue->size = 0;
}
