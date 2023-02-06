/* write a c program that converts binary to hexadecimal */

#include <stdio.h>
#include <math.h>

void decimal_to_hex();

int main() {


    

    return (0);
}

void decimal_to_hex() {
    // converting decimal to hexadecimal
    int hex[100];
    int j = 0;
    int decimal = 10;
    while (decimal != 0) {
        hex[j] = decimal % 16;
        decimal = decimal / 16;
        j++;
    }
    printf("hexadecimal number = ");
    for (int i = j - 1; i >= 0; i--) {
        if (hex[i] > 9) {
            printf("%c\n", hex[i] + 55);
        }
        else {
            printf("%d\n", hex[i]);
        }
    }
}
