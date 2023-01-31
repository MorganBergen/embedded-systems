/*
 * @file            02-prog.c
 * @autjor          morgan bergen
 * @date            jan 27 2023
 * @brief           program 2 for lab01
 * @description     write a c program to accept the height of a person in 
 *                  centimeters and categorize the person
 *                  according to their height whether the person is tall / medium / short
 */

/* #include <stdio.h>   
 * preprocessor directive refering to source file for input/output standard library
 * 
 * @description         
 * when the name is bracketed by < and > a search is made for the header 
 * in a standard set of places
 * for example in my system the stdio.h file is located in the following path
 * /Library/Developer/CommandLineTools/SDKs/MacOSX13.0.sdk/usr/include/stdio.h
 */
#include <stdio.h>

int main() {
    
    double h = 0;
    
    printf("enter height in centimeters");
    scanf("%lf", &h);

    if (h == 0) {
        printf("%lf", h);
    } else {
        printf("%lf", h);
    }

    return(0);
}

/*
 * switch statement conditional are only valid for integral types
    switch (h) {
        case (h == 0):
            printf("%lf", h);
            break;
        case (h >= 0 && h <= 10):
            printf("%lf", h)
            break;
        default (h > 10):
            printf("%lf", h)
            break;
    }
*/


