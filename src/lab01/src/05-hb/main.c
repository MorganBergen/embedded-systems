#include <stdio.h>
#include <math.h>

int main() {
    int binary[100];  // array to store binary number
    int k = 0;        // counter for binary array
    int decimal = 14;  // variable to store decimal equivalent
    int i = 0;        // counter for binary array
    char hexa[100];   // array to store hexadecimal equivalent

    // convert decimal to binary
    while (decimal != 0) {
        binary[k] = decimal % 2;
        decimal = decimal / 2;
        k++;
    }

    // reverse the binary number
    int l = 0;
    for (i = k - 1; i >= 0; i--) {
        binary[l++] = binary[i];
    }

    // convert binary to decimal
    decimal = 0;
    for (i = 0; i < k; i++) {
        decimal += binary[i] * pow(2, i);
    }

    // convert decimal to hexadecimal
    k = 0;
    while (decimal != 0) {
        int rem = decimal % 16;
        if (rem < 10) {
            hexa[k] = rem + 48;
        } else {
            hexa[k] = rem + 55;
        }
        k++;
        decimal /= 16;
    }

    printf("decimal = %d\n", decimal);
    // reverse the hexadecimal number
    printf("hexadecimal number: ");
    for (i = k - 1; i >= 0; i--) {
        printf("%c", hexa[i]);
    }
    printf("\n");


    printf("binary number: ");
    for (int i = 0; i < k; i--) {
        printf("%d", binary[i]);
    }

    return (0);
}

