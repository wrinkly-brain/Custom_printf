#include <stdio.h>
#include "custom_printf.h"

int main()
{
    customPrint("Character: %c", 'A');
    printf("\n");
    customPrint("String: %s", "Hello, World!");
    printf("\n");
    customPrint("Integer: %d", 42);
    printf("\n");
    customPrint("Binary: %b", 5);
    printf("\n");
    customPrint("Percent sign: %%");
    printf("\n");
    customPrint("Nonspecifier");
    printf("\n");
    customPrint(NULL);
    printf("\n");
}