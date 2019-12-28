/* Insides of Stack data structure with base Dynamic Array */

#include "basic.h"

#ifndef DA_STACK_H
#define DA_STACK_H

#define STANDARD_EXPANSION_VAL 1.5
#define STANDARD_CAPACITY 10

// Denote maximum capacity for the queue just for controlling size of allocated memory
#define MAXSIZE INT_MAX

// Stack data structure based on Dynamic array
typedef struct Stack_type {
    size_t size;
    size_t capacity;
    double exp_val;
    void **buff;
} Stack;


// New stack creation
 Stack* daStackNew();

// New stack creation using a given array
 Stack* daStackFromArr(void** array, int size);

// Appending an element to the end of stack
void daStackPush(Stack* stack, void* item);

// Remove and return first element of stack
void* daStackPop(Stack* stack);

// Getting the first element of stack
void* daStackTop(Stack* stack);

// Getting the last element of stack
void* daStackTail(Stack* stack);

// Getting the size of stack
size_t daStackSize(Stack* stack);

// Checking if stack is empty or not
bool daStackIsEmpty(Stack* stack);

// Checking if stack is full or not
bool daStackIsFull(Stack* stack);

// Checks if the size of a given stack is less than the MAXSIZE or not
bool daStackSizeIsValid(Stack* stack);

// Expanding capacity of stack
void daStackExpandCapacity(Stack* stack);

// Cutting capacity of stack
void daStackCutCapacity(Stack* stack);

// Deleting a given stack
 void daStackClear(Stack* stack);

// Clearing a given stack
 void daStackDelete(Stack* stack);


#endif // DA_STACK_H
