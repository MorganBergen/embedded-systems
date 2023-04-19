#include <stdio.h>
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
    /*breakup(280, &bufWrite[3], &bufWrite[4]);
    bufWrite[0] = PCA9685_LED0_OFF_L + 4;
    bufWrite[1] = 0;
    bufWrite[2] = 0;
    metal_i2c_transfer(i2c,PCA9685_I2C_ADDRESS,bufWrite,5,bufRead,1);*/
    breakup(280, &bufWrite[3], &bufWrite[4]);
    bufWrite[0] = PCA9685_LED0_ON_L ;
    printf(PCA9685_LED0_ON_L);
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

    breakup(313, &bufWrite[3], &bufWrite[4]);

    // if (speedFlag == 1) {

    //     breakup(313, &bufWrite[3], &bufWrite[4]);

    // } else if (speedFlag == 2) {

    //     breakup(315, &bufWrite[3], &bufWrite[4]);

    // } else if (speedFlag == 3) {

    //     breakup(317, &bufWrite[3], &bufWrite[4]);
    // }
  
    metal_i2c_transfer(i2c, PCA9685_I2C_ADDRESS, bufWrite, 5, bufRead, 1);
}

/* 
 * motor Reverse
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

void driveReverse(uint8_t speedFlag){

    if (speedFlag == 1) {

        breakup(267, &bufWrite[3], &bufWrite[4]);

    } else if (speedFlag == 2) {

        breakup(265, &bufWrite[3], &bufWrite[4]);

    } else if (speedFlag == 3) {

        breakup(263, &bufWrite[3], &bufWrite[4]);
    }

    bufWrite[0] = PCA9685_LED0_ON_L ;
    bufWrite[1] = 0;
    bufWrite[2] = 0;
    metal_i2c_transfer(i2c, PCA9685_I2C_ADDRESS, bufWrite, 5, bufRead, 1);
}

int main() {

/*
 * fully controlling the PCA9685
 * task 6: using previously defined functions, perform the following sequence of actions
 *
 *    -  configure the motors (wait for 2 seconds)
 *    -  set the steering heading to 0 degrees 
 *    -  drive forward (wait for 2 seconds)
 *    -  change the steering heading to 20 degrees (wait for 2 seconds)
 *    -  stop the motor (wait for 2 seconds)
 *    -  drive forward (wait for 2 seconds)
 *    -  set steering heading to 0 degrees (wait for 2 seconds)
 *    -  stop the motor
 */
    
    
   

    set_up_I2C();
    printf("setup\n");

    stopMotor();
     printf("stopmotor\n");
     delay(2000);  
    

     steering(20);
    printf("steering\n");
     delay(2000);
   
    driveForward(1);
    printf("drive\n");
     delay(2000);

     stopMotor();
     printf("stopmotor\n");
     delay(2000);
    
     driveReverse(1);
     printf("drivereverse\n");
     delay(2000);
  

     steering(0);
     printf("steering\n");
     delay(2000);
    

     stopMotor();

     printf("completed");
}
