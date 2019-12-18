/* Insides of Stack data structure with base Singly Linked List */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <math.h>


#ifndef SLL_STACK_H
#define SLL_STACK_H

#define MAXSIZE pow(2, 31)

// Defining a macrose for handling popular error
#define _MEMORY_ALLOCATION_ERROR panic("%s:%d: in '%s': could not allocate memory", __FILE__, __LINE__, __FUNCTION__);

// Node structure
typedef struct Node_type {
    void* data;
    struct Node_type* next;
} Node;

// Queue data structure, based on Linked List
typedef struct Stack_type {
    size_t size;
    Node* head;
    Node* tail;
} Stack;


// New stack creation
static Stack* stackNew();

// New stack creation using a given array
static Stack* stackFromArr(int* array, int size);

// Showing an error message
static void panic(const char* message, ...);

// Appending an element to the end of stack
void stackPush(Stack* stack, void* value);

// Remove and return first element of stack
void* stackPop(Stack* stack);

// Getting the first element of stack
void* stackTop(Stack* stack);

// Getting the last element of stack
void* stackTail(Stack* stack);

// Getting the size of stack
size_t stackSize(Stack* stack);

// Checking if stack is empty or not
bool stackIsEmpty(Stack* stack);

// Checking if stack is full or not
bool stackIsFull(Stack* stack);

// Checks if the size of a given stack is less than the MAXSIZE or not
bool stackSizeIsValid(Stack* stack);

// Expanding capacity of stack
void stackExpandCapacity(Stack* stack);

// Cutting capacity of stack
void stackCutCapacity(Stack* stack);

// Deleting a given stack
static void stackClear(Stack* stack);

// Clearing a given stack
static void stackDelete(Stack* stack);


#endif // SLL_STACK_H
