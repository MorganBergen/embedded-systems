/*
 * @author          morgan bergen
 * @date            wed feb 8 2023
 * @file            04-program.c
 * @brief           write a c program to create a converter from binary to hexadecimal
 *                  and vice versa
 */

#include <stdio.h>
#include <math.h>

int binary_to_hex(int binary[], int size, char hex[]);
int hex_to_binary(char hex[], int size, int binary[]);

int main() {
    
    // initialize variables, binary array, and hex array
    int binary[4] = {1, 0, 1, 1};
    char hex[2] = {'A', 'B'};
    int size = 4;
    int size2 = 2;

    // call functions to convert binary to hex and hex to binary
    // parameters are the array, the size of the array, and the array to be converted to
    // the function returns the size of the converted array
    binary_to_hex(binary, size, hex);
    hex_to_binary(hex, size2, binary);

    // if the function returns 0, the conversion was unsuccessful
    return 0;
}

// function to convert binary to hex, returns the size of the converted array
int binaryToHexadecimal(int binary[], int size, char hexadecimal[]) {
    // initialize variables, and a counter
    int decimal, i, j;
    // counter for the hexadecimal array will start at 0
    j = 0;
    // as long as the counter is less than the size of the array, the loop will continue
    for (i = 0; i < size; i += 4) {
        // initialize decimal to 0
        decimal = 0;
        // convert the binary to decimal
        decimal += binary[i] * 8 + binary[i + 1] * 4 + binary[i + 2] * 2 + binary[i + 3];
        // if the decimal is less than 10, add the decimal to the hexadecimal array
        hexadecimal[j++] = decimalToHex(decimal);
    }
}

// function to convert hex to binary, returns the size of the converted array
int hexadecimalToBinary(char hexadecimal[], int size, int binary[]) {
    // initialize variables, and a counter
    int decimal, i, j;
    // counter for the binary array will start at 0
    j = 0;
    // as long as the counter is less than the size of the array, the loop will continue
    for (i = 0; i < size; i++) {
        // initialize decimal to 0
        decimal = hexToDecimal(hexadecimal[i]);
        // convert the decimal to binary
        decimalToBinary(decimal, binary + j, 4);
        // increment the counter by 4
        j += 4;
    }
}


