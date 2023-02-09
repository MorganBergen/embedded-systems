/*
 * @file        07-calculator.c
 * @date        feb 9 2023
 * @author      morgan bergen
 * @brief       extend assignment 1 by inclyding math.h header file in your program and 
 *              add the following functionalities to your calculator by utilizing the
 *              built-in functions of math.h:
 *              - square root
 *              - ceiling
 *              - floor and power
 *              also create your own function for custom math operations that returns
 *              (a + b)^2 if (a + b)^2 is given as user input
 */

#include <stdio.h>
// math library
#include <math.h>

// main function
int main(void) {
    // declare variables
    int a, b, c;
    // declare the operator variable
    char op;
    // user prompt
    printf("Enter an expression: ");
    // read user input with pass by reference
    scanf("%d %c %d", &a, &op, &b);
    // switch statement that will execute the correct operation based on the user input
    switch (op) {
        // addition operator
        case '+':
            // add a and b
            c = a + b;
            // break out of the switch statement
            break;
        // subtraction operator
        case '-':
            // subtract b from a
            c = a - b;
            // break out of the switch statement
            break;
        // multiplication operator
        case '*':
            // multiply a and b
            c = a * b;
            // break out of the switch statement
            break;
        // division operator
        case '/':
            // divide a by b
            c = a / b;
            // break out of the switch statement
            break;
        // power operator
        case '^':
            // raise a to the power of b
            c = pow(a, b);
            // break out of the switch statement
            break;
        // square root operator
        case 's':
            // square root of a
            c = sqrt(a);
            // break out of the switch statement
            break;
        // ceiling operator
        case 'c':
            // ceiling of a
            c = ceil(a);
            // break out of the switch statement
            break;
        // floor operator
        case 'f':
            // floor of a
            c = floor(a);
            // break out of the switch statement
            break;
        // power operator
        case 'p':
            // raise a to the power of b
            c = pow(a, b);
            // break out of the switch statement
            break;
        // modulus operator
        case 'm':
            // modulus of a and b
            c = pow(a + b, 2);
            break;
        // default case
        default:
            // print error message
            printf("Invalid operator");
            // exit the program
            return 0;
    }

    // print the result
    printf("Result: %d %c %d = %d ", a, op, b, c);
    // return 0
    return 0;
}

