/*
 * @file            03-prog.c
 * @author          morgan bergen
 * @date            jan 31 2023
 * @brief           program 3 for lab00
 * @description     write a c proggram to print all the prime numbers within
 *                  a limit set by a user input
 *
 */

#include <stdio.h>

int main() {
    
    /* cp   check prime
     * 
     * this will be used as a boolean variable to check if a value within
     * the following loops are prime or not
     * currently cp is undefined
     */
    int cp;
    int limit;
    printf("enter a limit: ");
    scanf("%d", &limit);
    /* initialization   i = 2, starts at 2
     * condition        i < 100, stops looping at 99
     * increment        i + 1, increments by 1 after each loop
     */
    for (int i = 2; i < limit; i++) {
        /* check prime is initialized as true
         * we start with assuming that it's true
         */
        cp = 1; 

        /* initialization   j = 2, starts at 2
         * condition        j < i, loops until j sees all of the the ith integers
         * increment        j + 1, increments by 1 after each loop
         */
        for (int j = 2; j < i; j++) {

            // if i/j has a no remainder then it is not a prime
            if (i % j == 0) {

                // check prime initialized back to false
                cp = 0; 
                // we break out of the inner for loop
                break;
            }
        }
        // if check prime is true print it, otherwise increment i and reloop
        if (cp == 1) {
            printf("prime: %d\n", i);
        }
    }

    // end of program
    return(0);
}
