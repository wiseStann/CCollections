#include "../include/basic.h"


/*

Showing to a user an error message.
> Complex time - const.

 Parameters [in]:
    -> [message], a message which should be shown to a user
 
 Parameters [out]:
    -> NULL
*/
extern void panic(const char* message, ...)
{
    va_list args;
    va_start(args, message);
    printf("Warning: ");
    vprintf(message, args);
    printf("\n");
    va_end(args);
}

/*

Converting a given element of type void* to char* type.
> Complex time - const.

 Parameters [in]:
    -> [element], an element which should be converted

 Parameters [out]:
    -> [element], converted element

*/
extern char* toString(void* element)
{
    return (char*)element;
}

/*

Converting a given element of type void* to int type.
> Complex time - const.

 Parameters [in]:
    -> [element], an element which should be converted

 Parameters [out]:
    -> [element], converted element

*/
extern int toInteger(void* element)
{
    return (int)(size_t)element;
}