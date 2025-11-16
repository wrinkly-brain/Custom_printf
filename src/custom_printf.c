#include "custom_printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// The second argument lets this be used without trying to free memory
int printString(char *string, bool freeMemory)
{
    // Print string char by char
    int length = strlen(string);
    for (int i = 0; i < length; i++)
    {
        putchar(string[i]);
    }

    // Free memory if allocated
    if (freeMemory)
    {
        free(string);
    }
    return length;
}

// Contains all specifiers for easy checking
char *formats = "csdib%";

int customPrint(char *string, ...)
{
    // NULL check
    if (string == NULL)
    {
        printString("Error: formatString is NULL", false);
        return 0;
    }

    va_list args;
    va_start(args, string);

    // Allocate space for the new string
    int newSize = sizeof(char);
    char *newString = malloc(newSize);
    int newIndex = 0;

    // Builds new string & checks for placeholders
    for (int i = 0; i < (int)strlen(string); i++)
    {
        char current = string[i];
        char specifier = string[i + 1];

        // Checks for % and if the next char is in the formats string
        if (current == '%' && strchr(formats, specifier) != NULL && specifier != '\0')
        {
            i++; // Skips the specifier character

            if (specifier == 'c') // Characters
            {
                char value = va_arg(args, int);

                // Checks if value is a char and throws an error if it isn't
                if (!isalpha(value) && !isdigit(value) && !isspace(value) && !ispunct(value))
                {
                    printString("Format specifier does not match corresponding argument.", false);
                    free(newString);
                    return 0;
                }

                // Increase allocated memory
                newSize += sizeof(char);
                newString = realloc(newString, newSize);

                // Add character
                newString[newIndex] = value;

                newIndex++;
            }
            else if (specifier == 's') // Strings
            {
                char *value = va_arg(args, char *);

                // Throws error if NULL is passed 
                if (!value)
                {
                    printString("Format specifier does not match corresponding argument.", false);
                    free(newString);
                    return 0;
                }

                int length = strlen(value);

                // Increase allocated memory
                newSize += sizeof(char) * (length);
                newString = realloc(newString, newSize);

                // Copy string into new string
                strcpy(&newString[newIndex], value);

                newIndex += length;
            }
            else if (specifier == 'd' || specifier == 'i') // Integers
            {
                int value = va_arg(args, int);

                if (!value)
                {
                    printString("Format specifier does not match corresponding argument.", false);
                    free(newString);
                    return 0;
                }

                // Create string to store converted int with enough memory to store negative sign and null terminator
                char *buffer = malloc(12);

                // Convert int into string
                itoa(value, buffer, 10);

                // Increase allocated memory
                newSize += sizeof(char) * strlen(buffer);
                newString = realloc(newString, newSize);

                // Copy string into new string
                strcpy(&newString[newIndex], buffer);

                newIndex += strlen(buffer);

                free(buffer);
            }
            else if (specifier == 'b') // Binary
            {
                int value = va_arg(args, int);
                
                if (!value)
                {
                    printString("Format specifier does not match corresponding argument.", false);
                    free(newString);
                    return 0;
                }

                // Create string to store binary number with enough memory to store a 32 bit binary value
                char *binaryNum = malloc(33);

                itoa(value, binaryNum, 2);

                // Increase allocated memory
                newSize += sizeof(char) * strlen(binaryNum);
                newString = realloc(newString, newSize);

                // Copy string into new string
                strcpy(&newString[newIndex], binaryNum);

                newIndex += strlen(binaryNum);

                free(binaryNum);
            }
            else if (specifier == '%')
            {
                // Increase allocated memory
                newSize += sizeof(char);
                newString = realloc(newString, newSize);

                // Add % to string
                newString[newIndex] = '%';

                newIndex++;
            }

            continue;
        }
        // Increase allocated memory and add character
        newSize += sizeof(char);
        newString = realloc(newString, newSize);
        newString[newIndex] = current;
        newIndex++;
    }
    // Add null terminator
    newString[newIndex] = '\0';
    va_end(args);
    // This will return the string length
    return printString(newString, true);
}
