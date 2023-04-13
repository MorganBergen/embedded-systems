ls
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


/*
 * When looking at the register summary, note that each LEDn has 4 components, ON_L, ON_H, OFF_L, and OFF_H. 
 This is because 4096 is a 12-bit number, so it must be broken up to fit into two 8-bit numbers, as I2C writes a byte at a time. 
 L refers to the lower 8 bits, and H refers to the higher 8 bits. 
 Your task will be to define a function that takes an integer and breaks it down into the high 8-bits and low 8-bits, a
 ssigning the references high and low to these values. (Implement void breakup function in milestone1/src/eecs388_i2c.c)
 */
void breakup(int bigNum, uint8_t* low, uint8_t* high){
    high = uint8_t( bigNum >> 8);
    low = uint8_t (bigNum);
}

/*
 *  before we define steering you need info about the servo motors on the car
 *  controlling the servo and motor electronic speed controller with pwm
 *  is very similar to how we did so in the actuator lab
 *  (reference lab05 for steering)
 *  however in this case we will be converting values 
 *  ranging from 0 to 20 ms to 0 to 4095 cycles
 * 
 *  the getservocycle function converts an angle between -45 to 45 to
 *  a servo duty cycle 
 *  you need to write the return cycle into LED1_OFF and LED1_OFF_H
 *  to change the angle of the tires
 * 
 * int map(int angle, int lowIn, int highIn, int lowOut, int highOut)
 * int getServoCycle(int angle)
 * 
 * 
 * use the getServoCycle, breakup, and transfer functionn to 
 * implement the steering function to control the streering of the car
 * you need to alter the pwn of the servo motor
 * angle is between the range of -45 to 45
 * 
 */
void steering(int angle){

    uint8_t cycleValLow;
    uint8_t cycleValHigh;

    int cycleVal;
    _Bool success;
    cycleVal = getServoCycle(angle);
    
    breakup(cycleVal, &cycleValLow, &cycleValHigh);

    bufWrite[0] = PCA9685_LED0_ON_L;
    bufWrite[1] = 0;
    bufWrite[2] = 0;
    bufWrite[3] = cycleValLow;
    bufWrite[4] = cycleValHigh;

    success = metal_i2c_transfer(i2c, PCA9685_I2C_ADDRESS, bufWrite, 5, bufRead, 1);
}

void stopMotor(){
    /*
        Write Task 3 code here
    */
}

void driveForward(uint8_t speedFlag){
    /*
        Write Task 4 code here
    */
}

void driveReverse(uint8_t speedFlag){
    /*
        Write task 5 code here
    */
}

int main()
{
    set_up_I2C();
    
    //Defining the breakup function
    /*
        Task 1: breaking 12 bit into two 8-bit
        Define the function created that recieves a 12 bit number,
        0 to 4096 and breaks it up into two 8 bit numbers.

        Assign these values to a referenced value handed into
        the function. 

        ex: 
        uint8_t variable1;
        uint8_t variable2;
        breakup(2000,&variable1,&variable2);
        variable1 -> low 8 bits of 2000
        variable2 -> high 8 bits of 2000


    */    
    
    //Changing Steering Heading
    /*
        Task 2: using getServoCycle(), bufWrite, bufRead, 
        breakup(), and and metal_i2c_transfer(), implement 
        the function defined above to control the servo
        by sending it an angle ranging from -45 to 45.

        Use the getServoCycle function to get the value to 
        breakup.

        ex: 
        int valToBreak = getServoCycle(45);
        >>>sets valToBreak to 355
        
        note: the motor's speed controller is either 
        LED0 or LED1 depending on where its plugged into 
        the board. If its LED1, simply add 4 to the LED0
        address

        ex: steering(0); -> driving angle forward
    */
    
    
    //Motor config/stop. This will cause a second beep upon completion
    /*
        -Task 3: using bufWrite, bufRead, breakup(), and
        and metal_i2c_transfer(), implement the funcion made
        above. This function Configure the motor by 
        writing a value of 280 to the motor.

        -include a 2 second delay after calling this function
        in order to calibrate

        -Note: the motor's speed controller is either 
        LED0 or LED1 depending on where its plugged into 
        the board. If its LED1, simply add 4 to the LED0
        address

        ex: stopMotor();
    */


    /*
    ############################################################
        ATTENTION: The following section will cause the        
        wheels to move. Confirm that the robot is              
        Propped up to avoid it driving away, as well as         
        that nothing is touching the wheels and can get 
        caught in them

        If anything goes wrong, unplug the hifive board from
        the computer to stop the motors from moving 
        
        Avoid sticking your hand inside the 
        car while its wheels are spinning
    #############################################################
    */
    

    //Motor Forward
    /*
        -Task 4: using bufWrite, bufRead, breakup(), and
        and metal_i2c_transfer(), implement the function
        made above to Drive the motor forward. The given
        speedFlag will alter the motor speed as follows:
        
        speedFlag = 1 -> value to breakup = 313 
        speedFlag = 2 -> value to breakup = 315(Optional)
        speedFlag = 3 -> value to breakup = 317(Optional)

        -note 1: the motor's speed controller is either 
        LED0 or LED1 depending on where its plugged into 
        the board. If its LED1, simply add 4 to the LED0
        address or type and replace LED1 with LED0

        ex: driveForward(1);
    */
    
    //Motor Reverse
    /*
        -Task 5: using bufWrite, bufRead, breakup(), and
        and metal_i2c_transfer(), implement the function
        made above to Drive the motor backward. The given
        speedFlag will alter the motor speed as follows:
        
        speedFlag = 1 -> value to breakup = 267 
        speedFlag = 2 -> value to breakup = 265(Optional)
        speedFlag = 3 -> value to breakup = 263(Optional)

        -note 1: the motor's speed controller is either 
        LED0 or LED1 depending on where its plugged into 
        the board. If its LED1, simply add 4 to the LED0
        address or type and replace LED1 with LED0

        ex: driveReverse(1);
    */
    
    
    //Fully Controlling the PCA9685
    /*
        -Task 6: using previously defined functions, 
        perform the following sequence of actions
        
        -Configure the motors (wait for 2 seconds)
        -Set the steering heading to 0 degrees 
        -Drive forward (wait for 2 seconds)
        -Change the steering heading to 20 degrees (wait for 2 seconds)
        -Stop the motor (wait for 2 seconds)
        -Drive forward (wait for 2 seconds)
        -Set steering heading to 0 degrees (wait for 2 seconds)
        -Stop the motor
    */

}
