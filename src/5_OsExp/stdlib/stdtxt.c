#include "stdtxt.h"

int strlen(unsigned char *string)
{
    int i;

    // This loop considers a dereferenced pointer to a string variable and self-terminates when
    // it encounters the null character '\0'
    for (i = 0; *string; string++) {
        i++;
     }

    return i;
}