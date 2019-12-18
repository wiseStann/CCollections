#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <limits.h>


// Defining some macroses for handling popular errors
#define _EMPTY_ARRAY_ERROR \
  panic("%s:%d in '%s': given array is empty", __FILE__, __LINE__, __FUNCTION__);
#define _EMPTY_LIST_ERROR \
  panic("%s:%d in '%s': given list is empty", __FILE__, __LINE__, __FUNCTION__);
#define _EMPTY_QUEUE_ERROR \
  panic("%s:%d in '%s': given queue is empty", __FILE__, __LINE__, __FUNCTION__);
#define _EMPTY_STACK_ERROR \
  panic("%s:%d in '%s': given stack is empty", __FILE__, __LINE__, __FUNCTION__);

#define _MEMORY_ALLOCATION_ERROR \
  panic("%s:%d: in '%s': could not allocate memory", __FILE__, __LINE__, __FUNCTION__);
#define _INDEX_ERROR(index_name) \
  panic("%s:%d: in '%s': index %d is not within the bounds of container", __FILE__, __LINE__, __FUNCTION__, (int)index_name)
#define _VALUE_ERROR(value_name) \
  panic("%s:%d: in '%s': value %d is not in container", __FILE__, __LINE__, __FUNCTION__, (int)value_name)

// Showing an error message to a user
static void panic(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    printf("Warning: ");
    vprintf(message, args);
    printf("\n");
    va_end(args);
}
