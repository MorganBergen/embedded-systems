/**
 * This program reads the distance data from the TFmini lidar sensor,  
 * prints the read data and controls an LED depending on the measured distance.
 */
#include <stdint.h>
#include <stdio.h>

#include "eecs388_lib.h"

int main() {
    gpio_mode(RED_LED, OUTPUT);
    gpio_mode(GREEN_LED, OUTPUT);
    ser_setup();

    // ser_printline() can be used to print to the serial monitor
    ser_printline("Setup completed.\n"); 
    printf("Setup completed.\n");

    // LIDAR distance data is 16 bits.
    uint16_t dist = 0;

    while (1) {
/* 
Task 2.1: 
- read a data frame from the TFmini sensor
- from Table 6, we know each LIDAR measurement sends 9 bytes
- the function `ser_read()` can process 1 byte per function call
- This if-statement below will read (and check) the first two bytes of a valid data frame
- You will need to write code to read the subsequent bytes to get the distance data
- You will need to process the data received from the sensor to get the correct distance value

`ser_read()` returns 1 byte of data, 
-  byte1 - 0x59 = Y is the first byte of a valid data frame
-  byte2 - 0x59 = Y is the second byte of a valid data frame
-  byte3 - Dist_L is the low 8 bits 
-  byte3 - Dist_H is the high 8 bits
-  8 bits + 8 bits = 16 bits = 2 bytes
-  `uint16_t dist = 0;` is a 16 bit variable
-  in order to obtain the correct distance value, you will need to process the data received from the sensor

plan to read Byte3 and Byte4
-  create two temporary variables, capable of holding 1 byte of data / 8 bits
-  `unit8_1` is the data type for 1 byte of data
-  dist_1 is the variable name for the low 8 bits of the distance data
-  we will assign dist_1 to the return value from ser_read()
-  note that each function call to ser_read() will return 1 byte of data
-  dist_2 is the variable name for the high 8 bits of the distance data
-  we will assign dist_2 to the return value from ser_read()

-  we have previously declared the `uint16_t dist = 0;` variable
-  in order to assign it to the correct distance

-  `dist_2 << 8` is the high 8 bits of the distance data
-  << is a bitwise shift operator
-  << 8 shifts the high 8 bits to the left by 8 bits
-  | is the bitwise OR operator
-  what we want to combine is the remainder, so the low 8 bits of the distance data
-  01010101 | 10101010 = 11111111

LOW dist_1 = [bit1][bit2][bit3][bit4][bit5][bit6][bit7][bit8]
HIGH dist_2 = [bit1][bit2][bit3][bit4][bit5][bit6][bit7][bit8]

dist = dist_2 << 8 | dist_1


*/
        if ('Y' == ser_read() && 'Y' == ser_read()) {
            // read the low 8 bits of the distance data
            uint8_t dist_1 = ser_read();
            // read the high 8 bits of the distance data
            uint8_t dist_2 = ser_read();
            // combine the two 8 bits to get the 16 bits distance data
            // dist is assigned to the 16 bits distance data
            // (dist_2 << 8) is the high 8 bits of the distance data
            // << 8 shifts the high 8 bits to the left by 8 bits
            // | is the bitwise OR operator which combines the two 8 bits
            // what we want to combine is the remainder, so the low 8 bits of the distance data
            dist = (dist_2 << 8) | dist_1;
        /* 
            Task 2.2: 
            - turn on the red LED if the distance measured is less than 50 cm. 
            - otherwise turn on the green LED 
            
            - print the measured value to the console (i.e. the serial monitor) 
            - You can use printf() or ser_printline() or ser_write()
            
            - Helpful guide for printing with printf()
            - https://en.cppreference.com/w/cpp/io/c/fprintf
        */
            if (dist < 50) {
                gpio_write(RED_LED, ON);
                printf("Distance: %d cm:", dist);
            } else {
                gpio_write(GREEN_LED, ON);
                printf("Distance: %d cm:", dist);
            }
        }
    }
}    