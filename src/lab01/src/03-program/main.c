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

    int limit = 0;

    printf("enter limit of primes: ");
    scanf("%d", &limit);

    printf("%d%s", limit, "\n");

    for (int i = 2; i <= limit; i++) {
        printf("%d", i);
        printf("is looked at \n");
        for (int j = 2; (j % i == 0); j++) {
            printf("%d", i);
            printf("if prime \n");
        }
    }



    return(0);
}
/*
    for (int i = 0; i < limit; i++) {
        for (int j = 0; j % i != 0; j++) {
            printf("%d", j);
        }
    }
*/

