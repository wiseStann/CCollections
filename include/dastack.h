/* Insides of Stack data structure with base Dynamic Array */

#include "utils/basic.h"

#ifndef DA_STACK_H
#define DA_STACK_H

#define STANDARD_EXPANSION_VAL 1.5
#define STANDARD_CAPACITY 10

// Denote maximum capacity for the queue just for controlling size of allocated memory
#define MAXSIZE INT_MAX

// Stack data structure, based on Dynamic array
typedef struct Stack_type {
    size_t size;
    size_t capacity;
    double exp_val;
    void **buff;
} Stack;


// New stack creation
static Stack* stackNew();

// New stack creation using a given array
static Stack* stackFromArr(int* array, int size);

// Appending an element to the end of stack
void stackPush(Stack* stack, void* item);

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


#endif // DA_STACK_H
