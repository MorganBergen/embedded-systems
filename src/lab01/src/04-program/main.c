/*
 * @file            main.c
 * @date            feb 2 2023
 * @author          morgan bergen
 * @brief           program 4 for lab01
 * @description     create a converter from binary -> hexadecimal & hexadecimal -> binary
 * @hints
 *
 * 1. remember the following table
 *
 *  decimal     hex     binary
 *  0           0       0000
 *  1           1       0001
 *  2           2       0010
 *  3           3       0011
 *  4           4       0100
 *  5           5       0101
 *  6           6       0110
 *  7           7       0111
 *  8           8       1000
 *  9           9       1001
 *  10          A       1010
 *  11          B       1011
 *  12          C       1100
 *  13          D       1101
 *  14          E       1110
 *  15          F       1111
 *  
 * 2. convert binary to hex
 * - starting from the right take the first 4 bits and convert to hex
 * - divide the input binary string from right side by four of them at once
 * - assign the corresponding hex value 
 *
 *
 *
 */

#include <stdio.h>

int main() {


    /* binary base 2 allowed digits 0, 1
     * 
     * b_7 b_6 b_5 b_4 b_3 b_2 b_1 b_0
     * 2^7 2^6 2^5 2^4 2^3 2^2 2^1 2^0
     * 128 +64 +32 +16 + 8 + 4 + 2 + 1 = 255
     *   0   0   0   0   0   0   0   1 = 1
     *   0   0   0   0   0   0   1   0 = 2
     *   0   0   0   0   0   0   1   1 = 3
     *   0   0   0   0   0   1   0   0 = 4
     *   0   0   0   0   0   1   0   1 = 5
     *   0   0   0   0   0   1   1   0 = 6
     *   0   0   0   0   0   1   1   1 = 7
     *   0   0   0   0   1   0   0   0 = 8
     *   0   0   0   0   1   0   0   1 = 9
     *   0   0   0   0   1   0   1   0 = 10
     */

    /* decimal base 10 allowed digits 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
     * 
     *  d_3    d_2    d_1    d_0
     * 10^3   10^2   10^1   10^0
     * 1000 +  200 +   30 +    4 = 1234
     *   1       2      3      4
     */

    /*  hexadecimal - base 16 - allowed digits 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F
     *                                                                      10,11,12,13,14,15
     *
     *  h_15    h_14    h_13    h_12    h_11    h_10    h_9    h_8    h_7    h_6    h_5    h_4    h_3    h_2    h_1    h_0
     *  16^15  16^14   16^13   16^12   16^11   16^10   16^9   16^8   16^7   16^6   16^5   16^4   16^3   16^2   16^1   16^0
     *  
     */

    /*  table
     *
     *  decimal     hex     binary
     *  0           0       0000
     *  1           1       0001
     *  2           2       0010
     *  3           3       0011
     *  4           4       0100
     *  5           5       0101
     *  6           6       0110
     *  7           7       0111
     *  8           8       1000
     *  9           9       1001
     *  10          A       1010
     *  11          B       1011
     *  12          C       1100
     *  13          D       1101
     *  14          E       1110
     *  15          F       1111
     */

    /* example to convert binary to hex
     *
     * 1 1111 0111 0111 0010    // starting from the right divide up into blocks of 4 digits
     * 1    F    7    7    2    // convert each block to hex
     * 1   15    7    7    2    // convert each block to decimal
     * -   --   --   --   --
     * 5    4    3    2    1    // index position
     *
     */


    return(0);
}







/*
   binary constants from `0b` prefix
   integer constants can be written as binary constants consisting of a sequence
   of `0` and `1` digits prefixed by `0b` 

   int i = 42;
   int b = 0b101010;
   int hex = 0x2A;
*/
