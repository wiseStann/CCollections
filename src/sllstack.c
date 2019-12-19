/*

-> Stack collection (Base: Singly Linked List) <-

This software is free and can be used and modifyied by anyone
under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3
of the License, or any later version.

[Development period] -> 30/11/19 - 4/12/19
[Author] -> Stanislav Kerimov
[Github] -> https://github.com/StarKerrr


-> Structure <-

typedef struct Node_type {
    void* data;
    struct Node_type* next;
} Node;

typedef struct Stack_type {
    size_t size;
    Node* head;
    Node* tail;
} Stack;


-> Macroses <-

 -> [_MEMORY_ALLOCATION_ERROR], a macros for notification about memory allocation error

*/

#include "../include/sllstack.h"


static Stack* stackNew();
static Stack* stackFromArr(int* array, int size);
static Node* nodeNew(void* value);
static void stackClear(Stack* stack);
static void stackDelete(Stack* stack);

void stackPush(Stack* stack, void* item);
void* stackPop(Stack* stack);
void* stackTop(Stack* stack);
void* stackTail(Stack* stack);
size_t stackSize(Stack* stack);
bool stackIsEmpty(Stack* stack);
bool stackIsFull(Stack* stack);
bool stackSizeIsValid(Stack* stack);
void print(Stack* stack, bool show_size);


/*

New stack creation.
> Complex time - O(n).

 Parameters [in]:
    -> NULL

 Parameters [out]:
    -> [stack], a new created stack

*/
static Stack* stackNew()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (!stack) {
        free(stack);
        _MEMORY_ALLOCATION_ERROR;
        exit(1);
    }

    stack->size = 0;
    stack->head = NULL;
    stack->tail = NULL;
    return stack;
}

/*

Making a stack from a given array.
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array, which is the base for a new stack

 Parameters [out]:
    -> [stack], the stack, which should be made with the given array

*/
static Stack* stackFromArr(int* array, int size)
{
    Stack* stack = stackNew();

    for (int i = 0; i < size; i++) {
        stackPush(stack, (void*)(size_t)array[i]);
    }
    return stack;
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
    return new_node;
}

/*

Appending new element to the end of a given stack.
> Complex time - O(n).

 Parameters [in]:
    -> [stack], a stack, to which an element should be appended
    -> [value], a value, which should be appended to the stack
 Parameters [out]:
    -> NULL
*/
void stackPush(Stack* stack, void* value)
{
    if (!stack->head) {
        stack->head = nodeNew(value);
        stack->tail = stack->head;
    } else if (stack->size >= MAXSIZE) {
        panic("%s:%d: max size of elements is reached", __FILE__, __LINE__);
        exit(1);
    } else {
        Node* curr_node = stack->head;
        while (curr_node->next) {
            curr_node = curr_node->next;
        }

        curr_node->next = nodeNew(value);
        stack->tail = curr_node->next;
    }
    stack->size++;
}

/*

Remove and return the tail of a given stack.
> Given stack must not be empty.
> Complex time - const.

 Parameters [in]:
    -> [stack], a stack, from which the tail should be removed and returned

 Parameters [out]:
    -> [tail], the first element of stack, which should be removed and returned

*/
void* stackPop(Stack* stack)
{
    if (!stack->head) {
        return NULL;
    }

    void* tail = stack->tail->data;

    Node* curr_node = stack->head;
    while (curr_node->next->next) {
        curr_node = curr_node->next;
    }
    free(curr_node->next);
    curr_node->next = NULL;
    stack->size--;
    
    return tail;
}

/*

Getting the top element of a given stack.
> Given stack must not be empty.
> Complex time - const.

 Parameters [in]:
    -> [stack], a stack, the top of which should be got

 Parameters [out]:
    -> [top], the front element of stack

*/
void* stackTop(Stack* stack)
{
    if (!stack->head) {
        return NULL;
    }

    void* top = stack->head->data;
    return top;
}

/*

Getting the tail of a given stack.
> Given stack must not be empty.
> Complex time - const.

 Parameters [in]:
    -> [stack], a stack, the tail of which should be returned

 Parameters [out]:
    -> [tail], the last element of the given stack

*/
void* stackTail(Stack* stack)
{
    if (!stack->head) {
        return NULL;
    }

    void* tail = stack->tail->data;
    return tail;
}

/*

Getting the size of a given stack.
> Complex time - const.

 Parameters [in]:
    -> [stack], a stack, the size of which should be returned

 Parameters [out]:
    -> [stack_size], the size of the given stack

*/
size_t stackSize(Stack* stack)
{
    size_t stack_size = stack->size;
    return stack_size;
}

/*

Checking if a given stack is full or not.
> Complex time - const.

 Parameters [in]:
    -> [stack], a stack, which should be checked

 Parameters [out]:
    -> [bool], get value 'true' if stack is empty and 'false' otherwise

*/
bool stackIsEmpty(Stack* stack)
{
    if (stack->size == 0)
        return true;
    return false;
}

/*

Checking if a given stack is empty or not.
> Complex time - const.

 Parameters [in]:
    -> [stack], a stack, which should be checked

 Parameters [out]:
    -> [bool], get value 'true' if stack is full and 'false' otherwise

*/
bool stackIsFull(Stack* stack)
{
    if (stack->size >= MAXSIZE)
        return true;
    return false;
}

/*

Checking if the size of a given stack is less than MAXSIZE.
> Complex time - const.

 Parameters [in]:
    -> [stack], a stack, the size of which should be checked

 Parameters [out]:
    -> [bool], get value 'true' if the size is less than MAXSIZE and 'false' otherwise

*/
bool stackSizeIsValid(Stack* stack)
{
    if (stack->size <= MAXSIZE)
        return true;
    return false;
}

/*
 
Clearing a given stack without deleting allocated memory.
> Complex time - O(n).

 Parameters [in]:
    -> [stack], a stack, which should be cleared

 Parameters [out]:
    -> NULL
*/
static void stackClear(Stack* stack)
{
    if (!stack->head) {
        panic("%s:%d: cannot clear empty stack", __FILE__, __LINE__);
        exit(1);          
    }

    while (stack->head->next) {
        stack->head = stack->head->next;
    }
    stack->head = NULL;
    stack->tail = 0;
}

/*

Clearing all memory that was allocated for the stack.
> Complex time - O(n).

 Parameters [in]:
    -> [stack], a stack, which should be deleted

 Parameters [out]:
    -> NULL
*/
static void stackDelete(Stack* stack)
{
    if (!stack->head) {
        panic("%s:%d: cannot remove empty stack", __FILE__, __LINE__);
        exit(1);   
    }

    Node* curr_node = stack->head;
    Node* next;
    while (curr_node) {
        next = curr_node->next;
        free(curr_node);
        curr_node = next;
    }
    stack->head = NULL;
    stack->tail = 0;
}
