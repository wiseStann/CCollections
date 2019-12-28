/* Insides of Queue data srtucture with base SSL */

#include "basic.h"

#ifndef SSL_QUEUE_H
#define SSL_QUEUE_H

#define MAXSIZE INT_MAX

// Node structure
typedef struct Node_type {
    void* value;
    struct Node_type* next;
} Node;

// Queue data structure, based on Linked List
typedef struct Queue_type {
    size_t size;
    Node* front;
    Node* back;
} Queue;


// New queue creation
 Queue* queueNew();

// New queue creation using a given array
 Queue* queueFromArr(void** array, int size);

// New node creation
 Node* qnodeNew(void* value);

// Appending an element to the end of queue
void enqueue(Queue* queue, void* item);

// Remove and return first element of queue
void* dequeue(Queue* queue);

// Getting the first element of queue
void* queueFront(Queue* queue);

// Getting the last element of queue
void* queueRear(Queue* queue);

// Getting the size of queue
size_t queueSize(Queue* queue);

// Checking if queue is empty or not
bool queueIsEmpty(Queue* queue);

// Checking if queue is full or not
bool queueIsFull(Queue* queue);

// Checks if the size of queue is less than the MAXSIZE or not
bool queueSizeIsValid(Queue* queue);

// Clearing a given queue
 void queueClear(Queue* queue);

// Deleting a given queue
 void queueDelete(Queue* queue);


#endif // SSL_QUEUE_H
