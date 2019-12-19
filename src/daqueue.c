/*

-> Queue collection (Base: Dynamic Array) <-

This software is free and can be used and modifyied by anyone
under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3
of the License, or any later version.

[Development period] -> 29/11/19 - 30/11/19
[Author] -> Stanislav Kerimov
[Github] -> https://github.com/StarKerrr


-> Structure <-

typedef struct Queue_type {
    size_t size;
    size_t capacity;
    double exp_val;
    void **buff;
} Queue;


-> Macroses <-

 -> [_EMPTY_QUEUE_ERROR], a macros for notification about empty given queue
 -> [_MEMORY_ALLOCATION_ERROR], a macros for notification about memory allocation error

*/

#include "../include/daqueue.h"

static Queue* queueNew();
static Queue* queueFromArr(int* array, int size);
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
void queueExpandCapacity(Queue* queue);
void queueCutCapacity(Queue* queue);
void print(Queue* queue, bool show_size, bool show_cap);


/*

Creating a new queue.

* Just because before the work with
this data structure you have to assign queue components to
start values *

 Parameters [in]:
    -> [queue], a queue that should be initialized for furter use

 Parameters [out]:
    -> [queue], a new created queue

*/
static Queue* queueNew()
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (!queue) {
        free(queue);
        _MEMORY_ALLOCATION_ERROR;
        exit(1);
    }

    queue->size = 0;
    queue->capacity = STANDARD_CAPACITY;
    queue->exp_val = STANDARD_EXPANSION_VAL;
    queue->buff = malloc(queue->capacity * sizeof(void*));

    return queue;
}

/*

Making a queue using a given array.
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array, which should be converted to a queue
    -> [size], the size of a given array

 Parameters [out]:
    -> [queue], a made queue using a given array

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

Appending an element to a given queue.
> Complex time - const.

 Parameters [in]:
    -> [queue], a queue, to the end of which an item should be appended
    -> [item], an item, which should be appended to a given queue

 Parameters [out]:
    -> NULL
*/
void enqueue(Queue* queue, void* item)
{   
    if (queue->size >= queue->capacity) {
        queueExpandCapacity(queue);
    }

    queue->buff[queue->size++] = item;
}

/*

Remove and getting the first element of a given queue.
> Given queue must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [queue], a queue, the head of which should be removed and returned

 Parameters [out]:
    -> [head], the first element of a given queue

*/
void* dequeue(Queue* queue)
{
    if (queue->size == 0) {
        _EMPTY_QUEUE_ERROR;
        return NULL;
    }

    void* head = queue->buff[0];
    memmove (
        &(queue->buff[0]),
        &(queue->buff[1]),
        sizeof(void*) * queue->size
    );
    queue->size--;
    return head;
}

/*

Getting the head of a given queue.
> Given queue must not be empty.
> Complex time - const.

 Parameters [in]:
    -> [queue], a queue, the head of which should be returned

 Parameters [out]:
    -> [head], the first element of a given queue

*/
void* queueFront(Queue* queue)
{
    if (queue->size == 0) {
        _EMPTY_QUEUE_ERROR;
        return NULL;
    }

    void* head = queue->buff[0];
    return head;
}

/*

Getting the tail of a given queue.
> Given queue must not be empty.
> Complex time - const.

 Parameters [in]:
    -> [queue], a queue, the tail of which should be returned

 Parameters [out]:
    -> [tail], the last element of a given queue

*/
void* queueRear(Queue* queue)
{   
    if (queue->size == 0) {
        _EMPTY_QUEUE_ERROR;
        return NULL;
    }

    void* tail = queue->buff[queue->size - 1];
    return tail;
}

/*

Getting the size of a given queue.
> Complex time - const.

 Parameters [in]:
    -> [queue], a queue, the size of which should be returned

 Parameters [out]:
    -> [size], the size of a given queue

*/
size_t queueSize(Queue* queue)
{   
    size_t size = queue->size;
    return size;
}

/*

Checking if a given queue is empty or not.
> Complex time - const.

 Parameters [in]:
    -> [queue], a queue, which should be checked if it's empty or not

 Parameters [out]:
    -> [bool], the boolean result of checking if a given queue is empty or not

*/
bool queueIsEmpty(Queue* queue)
{
    if (queue->size == 0)
        return true;
    return false;
}

/*

Checking if a given queue is full or not.
> Complex time - const.

 Parameters [in]:
    -> [queue], a queue, which should be checked

 Parameters [out]:
    -> [bool], the boolean result of checking if a given queue is full or not

*/
bool queueIsFull(Queue* queue)
{
    if (queue->size == MAXSIZE)
        return true;
    return false;
}

/*

Checking is the size of a given queue is valid or not.
> Complex time - const.

 Parameters [in]:
    -> [queue], a queue, the size of which should be checked

 Parameters [out]:
    -> [bool], the boolean result of checking if the size of a given queue is valid or not

*/
bool queueSizeIsValid(Queue* queue)
{
    if (queue->size <= MAXSIZE)
        return true;
    return false;
}

/*

Expansion of the capacity when it is necessary.
> Given queue must not be empty.
> Complex time - most likely O(n).

* Actually this stuff is made due to dynamic memory allocation, it is very
convenient because we are not to keep queue of a huge capacity in our
memory, but just to expand it when it is necessary *

 Parameters [in]:
    -> [queue], an queue capacity of which should be expanded

 Parameters [out]:
    -> NULL
*/
void queueExpandCapacity(Queue* queue)
{
    if (queue->capacity >= MAXSIZE) {
        panic("'%s':%d: max capacity size exceeded", __FUNCTION__, __LINE__);
        exit(1);
    }

    size_t temp_cap = queue->capacity * queue->exp_val;
    temp_cap = temp_cap > MAXSIZE ? MAXSIZE : temp_cap;

    queue->capacity = temp_cap;
    queue->buff = realloc(queue->buff, queue->capacity * sizeof(void*));
}

/*

Cutting the capacity of a given queue.
> Complex time - const.

* After this action the capacity of the queue will be
equals to the number of its elements (size) *

 Parameters [in]:
    -> [queue], an queue, the capacity of which sould be cut

 Parameters [out]:
    -> NULL
*/
void queueCutCapacity(Queue* queue)
{
    if (queue->size == 0) {
        queue->capacity = STANDARD_CAPACITY;
    } else {
        queue->capacity = queue->size;
    }
}

/*

Clearing a given queue without deleting allocated memory.
> Complex time - const.

 Parameters [in]:
    -> [queue], a queue, which should be cleared

 Parameters [out]:
    -> NULL
*/
static void queueClear(Queue* queue)
{
    queue->size = 0;
    queue->capacity = STANDARD_CAPACITY;
    queue->exp_val = STANDARD_EXPANSION_VAL;
}

/*

Clearing all memory that was allocated for the queue.
> Complex time - const.

 Parameters [in]:
    -> [queue], a queue, which should be cleared

 Parameters [out]:
    -> NULL
*/
static void queueDelete(Queue* queue)
{
    free(queue->buff);
    free(queue);
}
