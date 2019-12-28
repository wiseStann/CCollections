/*

-> Deque collection (Base: Dynamic Array) <-

This software is free and can be used and modifyied by anyone
under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3
of the License, or any later version.

[Development period] -> 20/12/19 - 21/12/19
[Author] -> Stanislav Kerimov
[Github] -> https://github.com/StarKerrr


-> Structure <-

typedef struct Deque_type {
    size_t size;
    size_t capacity;
    double exp_val;
    void **buff;
} Deque;


-> Macroses <-

 Check Error macroses in "include/basic.h" header file.
 -> [_EMPTY_QUEUE_ERROR], a macros for notification about empty given deque
 -> [_MEMORY_ALLOCATION_ERROR], a macros for notification about memory allocation error

*/

#include "../include/deque.h"

/*
   Features which will be added soon:
  - Deque* dequeCopy(Deque* deque);
  - size_t dequeCount(Deque* deque, void* value);
  - void dequeExtend(Deque* f_deque, Deque* s_deque);
  - void dequeExtendLeft(Deque* f_deque, Deque* s_deque);
  - void dequeRemove(Deque* deque, void* value);
  - void dequeReverse(Deque* deque);
*/


/*

Creating a new deque.

* Just because before the work with
this data structure you have to assign deque components to
start values *

 Parameters [in]:
    -> NULL
 
 Parameters [out]:
    -> [deque], a new created deque

*/
 Deque* dequeNew()
{
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    if (!deque) {
        free(deque);
        _MEMORY_ALLOCATION_ERROR;
        exit(1);
    }

    deque->size = 0;
    deque->capacity = STANDARD_CAPACITY;
    deque->exp_val = STANDARD_EXPANSION_VAL;
    deque->buff = malloc(deque->capacity * sizeof(void*));

    return deque;
}

/*

Making a deque using a given array.
> Complex time - O(n).
 
 Parameters [in]:
    -> [array], an array, which should be converted to a deque
    -> [size], the size of a given array
 
 Parameters [out]:
    -> [deque], a made deque using a given array

*/
 Deque* dequeFromArr(int* array, int size)
{
    Deque* deque = dequeNew();

    for (int i = 0; i < size; i++) {
        dequeAdd(deque, (void*)(size_t)array[i]);
    }
    return deque;
}

/*

Adding an element to a given deque.
> Complex time - const.

 Parameters [in]:
    -> [deque], a deque, to the end of which an item should be added
    -> [item], an item, which should be added to a given deque
 
 Parameters [out]:
    -> NULL

*/
void dequeAdd(Deque* deque, void* item)
{
    if (deque->size >= deque->capacity) {
        dequeExpandCapacity(deque);
    }

    deque->buff[deque->size++] = item;
}

/*

Adding an element to a given deque.
> Complex time - const.

 Parameters [in]:
    -> [deque], a deque, to the beginning of which an item should be added
    -> [item], an item, which should be added to a given deque

 Parameters [out]:
    -> NULL

*/
void dequeAddLeft(Deque* deque, void* item)
{
    if (deque->size >= deque->capacity) {
        dequeExpandCapacity(deque);
    }
	
    size_t mem_block = sizeof(void*) * deque->size;
    memmove (
	&(deque->buff[1]),
	&(deque->buff[0]),
	mem_block
    );

    deque->buff[0] = item;
    deque->size++;
}

/*

Remove and getting the last element of a given deque.
> Given deque must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [deque], a deque, the tail of which should be removed and returned
 
 Parameters [out]:
    -> [tail], the last element of a given deque

*/
void* dequePop(Deque* deque)
{
    if (deque->size == 0) {
        _EMPTY_QUEUE_ERROR;
        return NULL;
    }


    void* tail = deque->buff[--deque->size];
    return tail;
}

/*

Remove and getting the first element of a given deque.
> Given deque must not be empty.
> Complex time - O(n).

 Parameters [in]:
    -> [deque], a deque, the head of which should be removed and returned

 Parameters [out]:
    -> [head], the first element of a given deque

*/
void* dequePopLeft(Deque* deque)
{
    if (deque->size == 0) {
        _EMPTY_QUEUE_ERROR;
        return NULL;
    }


    void* head = deque->buff[0];
    size_t mem_block = sizeof(void*) * deque->size;
    memmove (
        &(deque->buff[0]),
        &(deque->buff[1]),
        mem_block
    );

    deque->size--;
    return head;
}

/*

Getting the head of a given deque.
> Given deque must not be empty.
> Complex time - const.

 Parameters [in]:
    -> [deque], a deque, the head of which should be returned
 
 Parameters [out]:
    -> [head], the first element of a given deque

*/
void* dequeFront(Deque* deque)
{
    if (deque->size == 0) {
        _EMPTY_QUEUE_ERROR;
        return NULL;
    }

    void* head = deque->buff[0];
    return head;
}

/*

Getting the tail of a given deque.
> Given deque must not be empty.
> Complex time - const.

 Parameters [in]:
    -> [deque], a deque, the tail of which should be returned
 
 Parameters [out]:
    -> [tail], the last element of a given deque

*/
void* dequeRear(Deque* deque)
{
    if (deque->size == 0) {
        _EMPTY_QUEUE_ERROR;
        return NULL;
    }

    void* tail = deque->buff[deque->size - 1];
    return tail;
}

/*

Getting the size of a given deque.
> Complex time - const.

 Parameters [in]:
    -> [deque], a deque, the size of which should be returned
 
 Parameters [out]:
    -> [size], the size of a given deque

*/
size_t dequeSize(Deque* deque)
{
    size_t size = deque->size;
    return size;
}

/*
Checking if a given deque is empty or not.
> Complex time - const.
 
 Parameters [in]:
    -> [deque], a deque, which should be checked if it's empty or not
 
 Parameters [out]:
    -> [bool], the boolean result of checking if a given deque is empty or not

*/
bool dequeIsEmpty(Deque* deque)
{
    if (deque->size == 0)
        return true;
    return false;
}

/*
Checking if a given deque is full or not.
> Complex time - const.
 
 Parameters [in]:
    -> [deque], a deque, which should be checked
 
 Parameters [out]:
    -> [bool], the boolean result of checking if a given deque is full or not

*/
bool dequeIsFull(Deque* deque)
{
    if (deque->size == MAXSIZE)
        return true;
    return false;
}

/*

Checking is the size of a given deque is valid or not.
> Complex time - const.
 
 Parameters [in]:
    -> [deque], a deque, the size of which should be checked
 
 Parameters [out]:
    -> [bool], the boolean result of checking if the size of a given deque is valid or not

*/
bool dequeSizeIsValid(Deque* deque)
{
    if (deque->size <= MAXSIZE)
        return true;
    return false;
}

/*

Expansion of the capacity when it is necessary.
> Given deque must not be empty.
> Complex time - most likely O(n).

* Actually this stuff is made due to dynamic memory allocation, it is very
convenient because we are not to keep deque of a huge capacity in our
memory, but just to expand it when it is necessary *
 
 Parameters [in]:
    -> [deque], an deque capacity of which should be expanded
 
 Parameters [out]:
    -> NULL
*/
void dequeExpandCapacity(Deque* deque)
{
    if (deque->capacity >= MAXSIZE) {
        panic("'%s':%d: max capacity size exceeded", __FUNCTION__, __LINE__);
        exit(1);
    }

    size_t temp_cap = deque->capacity * deque->exp_val;
    temp_cap = temp_cap > MAXSIZE ? MAXSIZE : temp_cap;

    deque->capacity = temp_cap;
    deque->buff = realloc(deque->buff, deque->capacity * sizeof(void*));
}

/*

Cutting the capacity of a given deque.
> Complex time - const.

* After this action the capacity of the deque will be
equals to the number of its elements (size) *
 
 Parameters [in]:
    -> [deque], an deque, the capacity of which sould be cut
 
 Parameters [out]:
    -> NULL
*/
void dequeCutCapacity(Deque* deque)
{
    if (deque->size == 0) {
        deque->capacity = STANDARD_CAPACITY;
    } else {
        deque->capacity = deque->size;
    }
}

/*

Clearing a given deque without deleting allocated memory.
> Complex time - const.
 
 Parameters [in]:
    -> [deque], a deque, which should be cleared
 
 Parameters [out]:
    -> NULL
*/
 void dequeClear(Deque* deque)
{
    deque->size = 0;
    deque->capacity = STANDARD_CAPACITY;
    deque->exp_val = STANDARD_EXPANSION_VAL;
}

/*

Clearing all memory that was allocated for the deque.
> Complex time - const.
 
 Parameters [in]:
    -> [deque], a deque, which should be cleared
 
 Parameters [out]:
    -> NULL
*/
 void dequeDelete(Deque* deque)
{
    free(deque->buff);
    free(deque);
}
