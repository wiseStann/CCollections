/* Insides of Double-end Queue data structure with base DA */

#include "utils/basic.h"

#ifndef _DOUBLE_END_Q_H_
#define _DOUBLE_END_Q_H_

#define STANDARD_EXPANSION_VAL 1.5
#define STANDARD_CAPACITY 10

// Denote maximum capacity for the queue just for controlling size of allocated memory
#define MAXSIZE INT_MAX

// Deque data structure based on Dynamic Array
typedef struct Deque_type {
	size_t size;
	size_t capacity;
	double exp_val;
	void **buff;
} Deque;


// New deque creation
static Deque* dequeNew();

// New deque creation using a given array
static Deque* dequeFromArr(int* array, int size);

// Appending an element to the end of deque
void dequeAdd(Deque* deque, void* item);

// Appending an element to the beginning of deque
void dequeAddLeft(Deque* deque, void* item);

// Remove and return the last element of deque
void* dequePop(Deque* deque);

// Remove and return the first element of deque
void* dequePopLeft(Deque* deque);

// Getting the first element of deque
void* dequeFront(Deque* deque);

// Getting the last element of deque
void* dequeRear(Deque* deque);

// Getting the size of deque
size_t dequeSize(Deque* deque);

// Checking if deque is empty or not
bool dequeIsEmpty(Deque* deque);

// Checking if deque is full or not
bool dequeIsFull(Deque* Deque);

// Checking if the size of deque is less than the MAXSIZE or not
bool dequeSizeIsValid(Deque* deque);

// Expanding capacity of a given queue
void dequeExpandCapacity(Deque* deque);

// Cutting capacity of a given deque
void dequeCutCapacity(Deque* deque);

// Deleting a given deque
static void dequeClear(deque* deque);

// Clearing a given deque
static void dequeDelete(Deque* deque);


#endif // _DOUBLE_END_Q_H_
