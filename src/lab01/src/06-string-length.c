/*
 * @file        06-string-length.c
 * @author      morgan bergen
 * @date        feb 9 2023
 * @brief       write a program in c to calculate the length of the string using a pointer
 */

#include <stdio.h>

// main function
int main(void) {
    // declare and initialize str as a pointer to a char with the value "hello world"
    char *str = "hello world";
    // length variable to store the length of the string
    int length = 0;

    // while the value of the pointer is not null
    while (*str != '\0') {
        // increment the length variable
        length++;
        // increment the pointer
        str++;
    }

    // print the length of the string
    printf("The length of the string is %d", length);

    // if the program reaches this point, return 0
    return 0;
}
