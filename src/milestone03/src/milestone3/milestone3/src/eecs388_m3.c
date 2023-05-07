include <stdio.h>
#include <stdint.h>
#include "eecs388_lib.h"
#include "metal/i2c.h"


struct metal_i2c *i2c;
uint8_t bufWrite[9];
uint8_t bufRead[1];


//The entire setup sequencebigNum
void set_up_I2C(){
    uint8_t oldMode;
    uint8_t newMode;
    _Bool success;


    bufWrite[0] = PCA9685_MODE1;
    bufWrite[1] = MODE1_RESTART;
    printf("%d\n",bufWrite[0]);
   
    i2c = metal_i2c_get_device(0);

    if(i2c == NULL){
        printf("Connection Unsuccessful\n");
    }
    else{
        printf("Connection Successful\n");
    }
   
    //Setup Sequence
    metal_i2c_init(i2c,I2C_BAUDRATE,METAL_I2C_MASTER);
    success = metal_i2c_write(i2c,PCA9685_I2C_ADDRESS,2,bufWrite,METAL_I2C_STOP_DISABLE);//reset
    delay(100);
    printf("resetting PCA9685 control 1\n");

    //Initial Read of control 1
    bufWrite[0] = PCA9685_MODE1;//Address
    success = metal_i2c_transfer(i2c,PCA9685_I2C_ADDRESS,bufWrite,1,bufRead,1);//initial read
    printf("Read success: %d and control value is: %d\n", success, bufWrite[0]);
   
    //Configuring Control 1
    oldMode = bufRead[0];
    newMode = (oldMode & ~MODE1_RESTART) | MODE1_SLEEP;
    printf("sleep setting is %d\n", newMode);
    bufWrite[0] = PCA9685_MODE1;//address
    bufWrite[1] = newMode;//writing to register
    success = metal_i2c_write(i2c,PCA9685_I2C_ADDRESS,2,bufWrite,METAL_I2C_STOP_DISABLE);//sleep
    bufWrite[0] = PCA9685_PRESCALE;//Setting PWM prescale
    bufWrite[1] = 0x79;
    success = metal_i2c_write(i2c,PCA9685_I2C_ADDRESS,2,bufWrite,METAL_I2C_STOP_DISABLE);//sets prescale
    bufWrite[0] = PCA9685_MODE1;
    bufWrite[1] = 0x01 | MODE1_AI | MODE1_RESTART;
    printf("on setting is %d\n", bufWrite[1]);
    success = metal_i2c_write(i2c,PCA9685_I2C_ADDRESS,2,bufWrite,METAL_I2C_STOP_DISABLE);//awake
    delay(100);
    printf("Setting the control register\n");
    bufWrite[0] = PCA9685_MODE1;
    success = metal_i2c_transfer(i2c,PCA9685_I2C_ADDRESS,bufWrite,1,bufRead,1);//initial read
    printf("Set register is %d\n",bufRead[0]);

}


/* defining the breakup function
 * task 1: breaking 12 bit into two 8-bit define the function created that recieves a 12 bit number,
 * 0 to 4096 and breaks it up into two 8 bit numbers. assign these values to a referenced
 * value handed into the function.
 *
 * ex:
 * uint8_t variable1;
 * uint8_t variable2;
 * breakup(2000,&variable1,&variable2);
 * variable1 -> low 8 bits of 2000
 * variable2 -> high 8 bits of 2000
 */   
void breakup(int bigNum, uint8_t* low, uint8_t* high){

    *low = bigNum & 0x00ff;

    *high = (bigNum >> 8) & 0xff;
}

/*
 * changing Steering Heading
 * task 2: using getServoCycle(), bufWrite, bufRead, breakup(), and and metal_i2c_transfer(),
 * implement the function defined above to control the servo by sending it an angle ranging
 * from -45 to 45. use the getServoCycle function to get the value to breakup.
 *
 * ex:
 * int valToBreak = getServoCycle(45);
 * >>>sets valToBreak to 355
 *
 * note: the motor's speed controller is either LED0 or LED1 depending on where its plugged into
 * the board. If its LED1, simply add 4 to the LED0 address
 * ex: steering(0); -> driving angle forward
 */

void steering(int angle){

    int cycleVal = getServoCycle(angle);
   
    bufWrite[0] = PCA9685_LED0_ON_L+4;
    bufWrite[1] = 0;
    bufWrite[2] = 0;

    breakup(cycleVal, &bufWrite[3], &bufWrite[4]);
 
    metal_i2c_transfer(i2c, PCA9685_I2C_ADDRESS, bufWrite, 5, bufRead, 1);
}

/*
 * motor config/stop. This will cause a second beep upon completion
 * task 3: using bufWrite, bufRead, breakup(), and metal_i2c_transfer(), implement the
 * funcion made above. This function configure the motor by writing a value of 280 to the motor.
 * include a 2 second delay after calling this function in order to calibrate
 *
 * note: the motor's speed controller is either LED0 or LED1 depending on where its plugged into
 * the board. If its LED1, simply add 4 to the LED0 address
 * ex: stopMotor();
 */

void stopMotor() {

    breakup(280, &bufWrite[3], &bufWrite[4]);

    bufWrite[0] = PCA9685_LED0_ON_L ;

    bufWrite[1] = 0;

    bufWrite[2] = 0;

    metal_i2c_transfer(i2c,PCA9685_I2C_ADDRESS,bufWrite,5,bufRead,1);
}
/*
 * ###########################################################################################
 * ATTENTION: The following section will cause the wheels to move. confirm that the robot
 * is propped up to avoid it driving away, as well as that nothing is touching the wheels
 * and can get caught in them if anything goes wrong, unplug the hifive board from the
 * computer to stop the motors from moving avoid sticking your hand inside the car while
 * its wheels are spinning
 * ###########################################################################################
 */

/*
 * motor forward
 * task 4: using bufWrite, bufRead, breakup(), and metal_i2c_transfer(), implement the function
 * made above to Drive the motor forward. the given speedFlag will alter the motor speed as follows
 *
 * speedFlag = 1 -> value to breakup = 313
 * speedFlag = 2 -> value to breakup = 315 (optional)
 * speedFlag = 3 -> value to breakup = 317 (optional)
 *
 * note 1: the motor's speed controller is either LED0 or LED1 depending on where its plugged into
 * the board. If its LED1, simply add 4 to the LED0 address or type and replace LED1 with LED0
 * ex: driveForward(1);
 */

void driveForward(int speedFlag){

    bufWrite[0] = PCA9685_LED0_ON_L;
    bufWrite[1] = 0;
    bufWrite[2] = 0;

    if (speedFlag == 1) {

        breakup(313, &bufWrite[3], &bufWrite[4]);

    } else if (speedFlag == 2) {

        breakup(315, &bufWrite[3], &bufWrite[4]);

    } else if (speedFlag == 3) {

        breakup(317, &bufWrite[3], &bufWrite[4]);
    }

   
   printf("Drive forward\n");

    metal_i2c_transfer(i2c, PCA9685_I2C_ADDRESS, bufWrite, 5, bufRead, 1);
}

/*
 * motor Reverse commenting
 * task 5: using bufWrite, bufRead, breakup(), and metal_i2c_transfer(), implement the function
 * made above to Drive the motor backward. the given speedFlag will alter the motor speed as follows:
 *
 * speedFlag = 1 -> value to breakup = 267
 * speedFlag = 2 -> value to breakup = 265 (optional)
 * speedFlag = 3 -> value to breakup = 263 (optional)
 *
 * note 1: the motor's speed controller is either LED0 or LED1 depending on where its plugged into
 * the board.4 if its LED1, simply add  to the LED0 address or type and replace LED1 with LED0
 * ex: driveReverse(1);
 */

void driveReverse( int speedFlag){
   
    bufWrite[0] = PCA9685_LED0_ON_L ;
    bufWrite[1] = 0;
    bufWrite[2] = 0;
   
    if (speedFlag == -1) {
        breakup(267, &bufWrite[3], &bufWrite[4]);
    } else if (speedFlag == -2) {
        breakup(265, &bufWrite[3], &bufWrite[4]);
    } else if (speedFlag == -3) {
        breakup(263, &bufWrite[3], &bufWrite[4]);
    }
    printf("Drive reverse \n");
    metal_i2c_transfer(i2c, PCA9685_I2C_ADDRESS, bufWrite, 5, bufRead, 1);
}

int raspberrypi_int_handler(int devid, int * angle, int * speed, int * duration) {
    char * str = malloc(50 * sizeof(char));
    int serial;  
    ser_readline(devid,50, str);
    sscanf(str, "%d %d %d ", angle, speed, duration);
    printf("Received values: angle=%d, speed=%d, duration=%d\n", *angle, *speed, *duration);
    printf(str.len());
    free(str);
    return (serial);
}


int main() {
    // initialize I2C
    set_up_I2C();
    delay(2000);
    // calibrate motor
    printf("calibrate motor \n");
    stopMotor();
    delay(2000);
    // initialize UART channels
    ser_setup(0); // uart0 (receive from raspberry pi)
    ser_setup(1);
    printf("setup completed.\n");
    printf("begin the main loop.\n");
    // drive loop
    int angle, speed, duration;
    while (true) {
        if (ser_isready(1)) {
            printf("data is available\n");
            duration = 0;
            int serial = raspberrypi_int_handler(1, &angle, &speed, &duration);
            printf("received values outside pi hivefive: angle=%d, speed=%d, duration=%d\n", angle, speed, duration);
            steering(angle);
            printf("Steering \n");
            if (-4 < speed && speed < 0) {
                driveReverse(speed);
                printf("reverse driving\n");
            }
            else if (4 > speed && speed > 0) {
                driveForward(speed);
                printf("drive forward\n");
            }
            else if (speed == 0) {
                stopMotor();
                printf("motor stopped\n");
            }
            delay(duration * 1000);
            printf("Delaying %d seconds\n",duration);
        }
    }

    return(0);
}
