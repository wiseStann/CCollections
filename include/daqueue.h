/* Insides of Queue data structure with base DA */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>


#ifndef DA_QUEUE_H
#define DA_QUEUE_H

#define STANDARD_EXPANSION_VAL 1.5
#define STANDARD_CAPACITY 10
#define MAXSIZE pow(2, 31)

// Defining a macrose for handling popular errors
#define _EMPTY_QUEUE_ERROR panic("%s:%d in '%s': given queue is empty", __FILE__, __LINE__, __FUNCTION__);
#define _MEMORY_ALLOCATION_ERROR panic("%s:%d: in '%s': could not allocate memory", __FILE__, __LINE__, __FUNCTION__);

// Queue data structure, based on Linked List
typedef struct Queue_type {
    size_t size;
    size_t capacity;
    double exp_val;
    void **buff;
} Queue;


// New queue creation
static Queue* queueNew();

// New queue creation using a given array
static Queue* queueFromArr(int* array, int size);

// Showing an error message
static void panic(const char* message, ...);

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

// Expanding capacity of a given queue
void queueExpandCapacity(Queue* queue);

// Cutting capacity of a given queue
void queueCutCapacity(Queue* queue);

// Deleting a given queue
static void queueClear(Queue* queue);

// Clearing a given queue
static void queueDelete(Queue* queue);


#endif // DA_QUEUE_H
