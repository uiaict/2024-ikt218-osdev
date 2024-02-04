#include "libc/stdlib.h"
#include "libc/string.h"
#include "libc/math.h"

// Implementation of the itoa function adapted from https://www.geeksforgeeks.org/implement-itoa/
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;
 
    /* Handle 0 explicitly, otherwise empty string is
     * printed for 0 */
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled
    // only with base 10. Otherwise numbers are
    // considered unsigned.
    if (num < 0 && base == 10) {
        isNegative = true;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    strrev(str, i);
 
    return str;
}

char* utoa(unsigned int num, char* str, int base)
{
    unsigned int i = 0;
 
    /* Handle 0 explicitly, otherwise empty string is
     * printed for 0 */
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // Process individual digits
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    strrev(str, i);
 
    return str;
}



// Implementation of the ftoa function. Adapted from https://www.geeksforgeeks.org/convert-floating-point-number-string/
void ftoa(float n, char* res, int afterpoint) {
    int intPart = (int)n;

    float floatPart = n - (float)intPart;

    itoa(intPart, res, 10);  // Convert integer part to a string

    // Find the length of integer part
    int i = 0;
    while (res[i] != '\0') {
        i++;
    }

    if (afterpoint != 0) {
        res[i] = '.';

        // Calculate the power of 10 for the fractional part
        int power = 1;
        for (int j = 0; j < afterpoint; j++) {
            power *= 10;
        }

        floatPart = floatPart * power;

        itoa((int)floatPart, res + i + 1, 10);  // Convert fractional part to a string
    }
}


// Implementation of the atoi function from https://www.geeksforgeeks.org/write-your-own-atoi/
int atoi(char *str)
{
    int res = 0;
    int sign = 1;
    int i = 0;
 
    // Update sign if negative
    if (str[0] == '-') {
        sign = -1;
 
        i++;
    }
 
    // Iterate through all characters of input string and update result
    for (; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';
 
    // Return result with sign
    return sign * res;
}