/*
 * @file            main.c
 * @date            feb 2 2023
 * @author          morgan bergen
 * @brief           program 4 for lab01
 * @description     create a converter from binary -> hexadecimal
 *                  hexadecimal -> binary
 */

#include <stdio.h>
#include <math.h>

int main() {

    // converting decimal to binary
    int binary[100];
    int k = 0;
    int decimal = 14;
    int dtemp = decimal;
    
    // scanf("%d", &decimal);

    while (decimal != 0) {
        binary[k] = decimal % 2;
        decimal = decimal / 2;
        k++;
    }

    printf("binary number: ");
    for (int i = k - 1; i >= 0; i--) {
        printf("%d", binary[i]);
    }
    printf(" = %d", dtemp);

    int i = 0;
    char hexa[100];

    // reverse the binary number


    // converting binary to decimal

    // converting binary to hexadecimal
   

    return(0);
}


