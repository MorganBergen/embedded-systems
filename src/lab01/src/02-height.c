/*
 * @file            main.c
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


/*
 * short person     0 - 150 cm
 * medium person    151 - 170 cm
 * tall person      171 - 240 cm
 */

/*
 * int main()       the main function that is ran upon compilation
 */
int main() {

    // initialized a double as 0 prior to use in the program
    double h = 0;

    // print to the console the following string as the user prompt 
    // for the user to enter their height
    // printf does not contain a new line character at the end, thus the 
    // console will not move to the next line when the string is printed
    printf("enter height in centimeters:  ");

    /*
     * scanf("%lf", &h)    scans the console for a double value and stores it in the
     *                     variable h is passed by reference, meaning the address of
     *                     the variable is passed to the function scanf and the value
     *                     is stored in the variable at the address
     *                     %lf is a format specifier for a double
     */
    scanf("%lf", &h);

    /* control flow statements if, else if, else
     *
     * if (boolean conditional) { executable statement block }
     * else if (boolean conditional) { executable statement block }
     * else { executable statement block }
     *
     * any executable statement block can contain declarations 
     * that are only valid within the scope of the block
     */

    // initial if statement to check if the height is less than or equal to 150
    if ((h > 0) && (h <= 150)) {
        /* if the previous conditional is true the following printf statements
         * will be executed by the program and provided to the user
         */
        printf("short interval      0 cm ≤ ");
        // %lf is a format specifier for a double
        // h is the variable that is passed to the function printf
        printf("%lf", h);
        printf(" ≤ 150 cm");

    /* second if statement to check if the height is greater than 150 and less than
     * or equal to 170 cm
     */
    } else if ((h > 150) && (h <= 170)) {
        /* if the previous conditional is true the following printf statements
         * will be executed by the program and provided to the user
         */
        printf("medium interval      151 cm ≤ ");
        // %lf is a format specifier for a double
        // h is the variable that is passed to the function printf
        printf("%lf", h);
        printf(" ≤ 170 cm");

    /* third if statement to check if the height is greater than 170 and less than
     * or equal to 240 cm
     */
    } else if ((h > 170) && (h <= 240)) {
        /* if the previous conditional is true the following printf statements
         * will be executed by the program and provided to the user
         */ 
        printf("tall interval       171 cm ≤ ");
        // %lf is a format specifier for a double
        // h is the variable that is passed to the function printf
        printf("%lf", h);
        printf(" ≤ 240 cm");
    /*
     * else statement is the last statement in the control flow statement
     * if none of the previous conditional statements are true the else statement
     * will be executed
     */
    } else {
        /*
         * we assume that if the user input does not qualify within the ranges
         * of the previous conditional statements that the user input is invalid
         */
        printf("error interval is out of range...\n");
        printf("please recompile and enter range between 0 cm < h ≤ 240 cm");
    }
    
    // adding a new line character to the end of the program for readability
    printf("\n");
    
    // return 0 to the operating system to indicate that the program ran successfully
    return(0);
}

/* we could have used switch statements instead of if, else if, else statements
 * however...
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
    therefore this would cause an error that would like like the following
    main.c:line number:character number: error: statement requires expression of integer type ('double' invalid)
*/


