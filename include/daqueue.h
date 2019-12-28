/* Insides of Queue data structure with base DA */

#include "basic.h"

#ifndef DA_QUEUE_H
#define DA_QUEUE_H

#define STANDARD_EXPANSION_VAL 1.5
#define STANDARD_CAPACITY 10

// Denote maximum capacity for the queue just for controlling size of allocated memory
#define MAXSIZE INT_MAX

// Queue data structure based on Dynamic Array
typedef struct Queue_type {
    size_t size;
    size_t capacity;
    double exp_val;
    void **buff;
} Queue;


// New queue creation
Queue* daQueueNew();

// New queue creation using a given array
Queue* daQueueFromArr(void** array, int size);

// Appending an element to the end of queue
void daEnqueue(Queue* queue, void* item);

// Remove and return first element of queue
void* daDequeue(Queue* queue);

// Getting the first element of queue
void* daQueueFront(Queue* queue);

// Getting the last element of queue
void* daQueueRear(Queue* queue);

// Getting the size of queue
size_t daQueueSize(Queue* queue);

// Checking if queue is empty or not
bool daQueueIsEmpty(Queue* queue);

// Checking if queue is full or not
bool daQueueIsFull(Queue* queue);

// Checking if the size of queue is less than the MAXSIZE or not
bool daQueueSizeIsValid(Queue* queue);

// Expanding capacity of a given queue
void daQueueExpandCapacity(Queue* queue);

// Cutting capacity of a given queue
void daQueueCutCapacity(Queue* queue);

// Deleting a given queue
 void daQueueClear(Queue* queue);

// Clearing a given queue
 void daQueueDelete(Queue* queue);


#endif // DA_QUEUE_H
