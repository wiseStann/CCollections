/*

-> Stack collection (Base: Dynamic Array) <-

This software is free and can be used and modifyied by anyone
under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3
of the License, or any later version.

[Development period] -> 30/11/19 - 31/11/19
[Author] -> Stanislav Kerimov
[Github] -> https://github.com/StarKerrr


-> Structure <-

typedef struct Stack_type {
    size_t size;
    size_t capacity;
    double exp_val;
    void **buff;
} Stack;


-> Macroses <-

 -> [_EMPTY_STACK_ERROR], a macros for notification about empty given stack
 -> [_MEMORY_ALLOCATION_ERROR], a macros for notification about memory allocation error

*/

#include "../include/dastack.h"


static Stack* stackNew();
static Stack* stackFromArr(int* array, int size);

void stackPush(Stack* stack, void* item);
void* stackPop(Stack* stack);
void* stackTop(Stack* stack);
void* stackTail(Stack* stack);
size_t stackSize(Stack* stack);
bool stackIsEmpty(Stack* stack);
bool stackIsFull(Stack* stack);
bool stackSizeIsValid(Stack* stack);
void stackExpandCapacity(Stack* stack);
void stackCutCapacity(Stack* stack);
static void stackClear(Stack* stack);
static void stackDelete(Stack* stack);
void print(Stack* stack, bool show_size, bool show_cap);

/*
   Features which will be added soon:
  - void stackRemove(Stack* stack, void* value);
  - void stackInsert(Stack* stack, size_t index, void* value);
  - size_t stackGetValue(Stack* stack, size_t index);
  - size_t stackCount(Stack* stack, void* value);
  - bool stackContains(Stack* stack, void* value);
*/


/*

Creating a new stack.

* Just because before the work with
this data structure you have to assign stack components to
start values *

 Parameters [in]:
    -> [stack], a stack that should be initialized for furter use

 Parameters [out]:
    -> [stack], a new created stack

*/
static Stack* stackNew()
{
    Stack* new_stack = (Stack*)malloc(sizeof(Stack));
    if (!new_stack) {
        free(new_stack);
        _MEMORY_ALLOCATION_ERROR;
        exit(1);
    }

    new_stack->size = 0;
    new_stack->capacity = STANDARD_CAPACITY;
    new_stack->exp_val = STANDARD_EXPANSION_VAL;
    new_stack->buff = malloc(new_stack->capacity * sizeof(void*));
    return new_stack;
}

/*

Making a stack using a given array.
> Complex time - O(n).

 Parameters [in]:
    -> [array], an array, which should be converted to a stack
    -> [size], the size of a given array

 Parameters [out]:
    -> [stack], a made stack using a given array

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

Appending an element to a given stack.
> Complex time - const.

 Parameters [in]:
    -> [stack], a stack, to the end of which an item should be appended
    -> [stack], an item, which should be appended to a given stack

 Parameters [out]:
    -> NULL
*/
void stackPush(Stack* stack, void* item)
{
    if (stack->size >= stack->capacity) {
        stackExpandCapacity(stack);
    }

    stack->buff[stack->size++] = item;
}

/*

Remove and getting last element of a given stack.
> Given stack must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [stack], a stack, the tail of which should be removed and returned

 Parameters [out]:
    -> [tail], the last element of a given stack

*/
void* stackPop(Stack* stack)
{
    if (stack->size == 0) {
        _EMPTY_STACK_ERROR;
        return NULL;
    }

    void* tail = stack->buff[--stack->size];
    return tail;
}

/*

Getting the top of a given stack.
> Given stack must not be empty.
> Complex time - const.

 Parameters [in]:
    -> [stack], a stack, the top of which should be returned

 Parameters [out]:
    -> [top], the first element of a given stack

*/
void* stackTop(Stack* stack)
{
    if (stack->size == 0) {
        return NULL;
    }

    void* top = stack->buff[0];
    return top;
}

/*

Getting the tail of a given stack.
> Given stack must not be empty.
> Complex time - const.

 Parameters [in]:
    -> [stack], a queue, the tail of which should be returned

 Parameters [out]:
    -> [tail], the last element of a given stack

*/
void* stackTail(Stack* stack)
{
    if (stack->size == 0) {
        return NULL;
    }

    void* tail = stack->buff[stack->size - 1];
    return tail;
}

/*

Getting the size of a given stack.
> Complex time - const.

 Parameters [in]:
    -> [stack], a stack, the size of which should be returned

 Parameters [out]:
    -> [size], the size of a given stack

*/
size_t stackSize(Stack* stack)
{
    return stack->size;
}

/*

Checking if a given stack is empty or not.
> Complex time - const.

 Parameters [in]:
    -> [stack], a stack, which should be checked

 Parameters [out]:
    -> [bool], the boolean result of checking if a given stack is empty or not

*/
bool stackIsEmpty(Stack* stack)
{
    if (stack->size == 0)
        return true;
    return false;
}

/*

Checking if a given stack is full or not.
> Complex time - const.

 Parameters [in]:
    -> [stack], a stack, which should be checked

 Parameters [out]:
    -> [bool], the boolean result of checking if a given stack is full or not

*/
bool stackIsFull(Stack* stack)
{
    if (stack->size >= MAXSIZE)
        return true;
    return false;
}

/*

Checking if the size of a given stack is valid or not.
> Complex time - const.

 Parameters [in]:
    -> [stack], a stack, the size of which should be checked

 Parameters [out]:
    -> [bool], the boolean result of checking if the size of a given stack is valid or not

*/
bool stackSizeIsValid(Stack* stack)
{
    if (stack->size < MAXSIZE)
        return true;
    return false;
}

/*

Expansion of the capacity when it is necessary.
> Given stack must not be empty.
> Complex time - most likely O(n).

* Actually this stuff is made due to dynamic memory allocation, it is very
convenient because we are not to keep stack of a huge capacity in our
memory, but just to expand it when it is necessary *

 Parameters [in]:
    -> [stack], an stack capacity of which should be expanded

 Parameters [out]:
    -> NULL
*/
void stackExpandCapacity(Stack* stack)
{
    if (stack->capacity >= MAXSIZE) {
        panic("'%s':%d: max capacity size exceeded", __FUNCTION__, __LINE__);
    }

    size_t temp_cap = stack->capacity * stack->exp_val;
    temp_cap = temp_cap > MAXSIZE ? MAXSIZE : temp_cap;

    stack->capacity = temp_cap;
    stack->buff = realloc(stack->buff, stack->capacity * sizeof(void*));
}

/*

Cutting the capacity of a given stack.
> Complex time - const.

* After this action the capacity of the stack will be
equals to the number of its elements (size) *

 Parameters [in]:
    -> [stack], an stack, the capacity of which sould be cut

 Parameters [out]:
    -> NULL
*/
void stackCutCapacity(Stack* stack)
{
    if (stack->size == 0) {
        stack->capacity = STANDARD_CAPACITY;
    } else {
        stack->capacity = stack->size;
    }
}

/*

Clearing a given stack without deleting allocated memory.
> Complex time - const.

 Parameters [in]:
    -> [stack], a stack, which should be cleared

 Parameters [out]:
    -> NULL
*/
static void stackClear(Stack* stack)
{
    stack->size = 0;
    stack->capacity = STANDARD_CAPACITY;
    stack->exp_val = STANDARD_EXPANSION_VAL;
}

/*

Clearing all memory that was allocated for the stack.
> Complex time - const.

 Parameters [in]:
    -> [stack], a stack, which should be cleared at all

 Parameters [out]:
    -> NULL
*/
static void stackDelete(Stack* stack)
{
    free(stack->buff);
    free(stack);
}
