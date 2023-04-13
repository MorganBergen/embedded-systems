#include <stdio.h>
#include <stdint.h>

#include "eecs388_lib.h"

#define SERVO_PULSE_MAX 2400    /* 2400 us */
#define SERVO_PULSE_MIN 544     /* 544 us */
#define SERVO_PERIOD    20000   /* 20000 us (20ms) */

/**
 * Generate a pwm signal
 * 
 * Input:
 *  @gpio   gpio number
 *  @pos    degree [0,180]
 */
void servo(int gpio, int pos)
{
    // YOUR CODE HERE
    // Basically, you need to take the input angle "pos" and generate the corresponding pwm signal
    // To generate the pwm signals, use gpio_write() and delay_usec()
    //makes the signal and delay
    
   int pwm = ((SERVO_PULSE_MAX-SERVO_PULSE_MIN)*pos)/ 180 + SERVO_PULSE_MIN; 
   int delay = SERVO_PERIOD-pwm;
   
    int pwm2=pwm;
    int delay2=delay;
    
    
    //5v pulse starts motor
    gpio_write(gpio,ON);
    
    //delay for amount on
    delay_usec(pwm);
    //0v pulse stops motor
    gpio_write(gpio,OFF);
    //second delay for amount of time off
    
    delay_usec(delay);

        

}

int main()
{
    int gpio = PIN_19;
    gpio_mode(gpio, OUTPUT);

    while (1) {
        
        /**delay_usec(SERVO_PULSE_MAX);
    d on the servo for ~1 second. 
         * 
         * Do you understand why 1 second?
         * 
         */
        for (int pos = 0; pos <= 180; pos += 30) {
            printf("pos: %d (degree)\n", pos);
            /* control the servo for 1 sec duration */
            for (int i = 0; i < 50; i++)
                servo(gpio, pos);
        }
    }
}
