
// Including base libs
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

// Showing an error message to a user
extern void panic(const char* message, ...);

// Convert void* to string (char*) for customary printing
extern char* toString(void* element);

// Convert void* to string (char*) for customary printing
extern int toInteger(void* element);

// Defining some macroses for handling popular errors
#define _EMPTY_ARRAY_ERROR \
  panic("in '%s': given array is empty", __FUNCTION__)
#define _EMPTY_LIST_ERROR \
  panic("in '%s': given list is empty", __FUNCTION__)
#define _EMPTY_QUEUE_ERROR \
  panic("in '%s': given queue is empty", __FUNCTION__)
#define _EMPTY_STACK_ERROR \
  panic("in '%s': given stack is empty", __FUNCTION__)
#define _EMPTY_TREE_ERROR \
  panic("in '%s': given tree is empty", __FUNCTION__)
#define _MEMORY_ALLOCATION_ERROR \
  panic("in '%s': could not allocate memory", __FUNCTION__)
#define _INDEX_ERROR(index) \
  panic("in '%s': given index %d is not within the bounds of container", __FUNCTION__, (int)index)
#define _VALUE_ERROR \
  panic("in '%s': given value is not in container", __FUNCTION__)

