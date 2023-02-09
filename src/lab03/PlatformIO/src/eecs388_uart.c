#include <stdint.h>

#include "eecs388_lib.h"

/*
    This program is supposed to read a chacter from the UART0 serial port and 
    turn on/off the appropriate LED based on the read chacter. 
    (r -> red led, g - > green led, b -> blue led)
     
    Task 1. Read the following sections in docs/FE310-G002.pdf
    - Chapter 4. Memory Map 
    - Chapter 18. UART

    Task 2. review provided ser_setup(), ser_write(), ser_printline() functions in eecs388_lib.c

    Task 3. implement ser_read() function in eecs388_lib.c.
 */

int main()
{
    char c;
    int led_gpio = GREEN_LED; 

    gpio_mode(RED_LED, OUTPUT);
    gpio_mode(GREEN_LED, OUTPUT);
    gpio_mode(BLUE_LED, OUTPUT);
    
    ser_setup();
    
    while(1)
    {
        ser_printline("\ntype 'r' or 'g' or 'b': "); 
        c = ser_read();        
        gpio_write(led_gpio, OFF);

        // Echo/write back the character to UART
        ser_write(c);  
        
        switch (c) {
            case 'r':
                led_gpio = RED_LED; 
                break;
            case 'g':
                led_gpio = GREEN_LED; 
                break;
            case 'b':
                led_gpio = BLUE_LED; 
                break;
            default:
                ser_printline("ERROR");
                break;
        }
        gpio_write(led_gpio, ON);
    }
}