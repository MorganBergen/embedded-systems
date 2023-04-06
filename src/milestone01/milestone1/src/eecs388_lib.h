#ifndef __EECS388_LIB_H__
#define __EECS388_LIB_H__

/******************************************************************************
 *   generic definitions
 *******************************************************************************/
#define ON                  1
#define OFF                 0
#define OUTPUT              1
#define INPUT               0

/******************************************************************************
 *   hifive1 platform related definitions
 *******************************************************************************/
#define RED_LED             22 // gpio 22
#define BLUE_LED            21 // gpio 21
#define GREEN_LED           19 // gpio 19

#define PIN_19              13 // gpio 13
/******************************************************************************
 *   memory map
 *******************************************************************************/
#define GPIO_CTRL_ADDR      0x10012000  // GPIO controller base address
#define GPIO_INPUT_VAL      0x00        // input val
#define GPIO_INPUT_EN       0x04        // input enable
#define GPIO_OUTPUT_EN      0x08        // output enable
#define GPIO_OUTPUT_VAL     0x0C        // output_val 
#define GPIO_IO_FUNC_EN     0x38        // gpio iof enable.
#define GPIO_OUTPUT_XOR     0x40        // output XOR (invert)

#define CLINT_CTRL_ADDR     0x02000000  // CLINT block base address
#define CLINT_MTIME         0xbff8      // timer register

#define UART0_CTRL_ADDR     0x10013000  // UART0 controller base address 
#define UART1_CTRL_ADDR     0x10023000  // UART1 controller base address
#define UART_TXDATA         0x00        // TXFIFO register
#define UART_RXDATA         0x04        // RXFIFO register
#define UART_TXCTRL         0x08        // TX control register
#define UART_RXCTRL         0x0C        // RX control register
#define UART_IE             0x10        // interrupt enable register
#define UART_IP             0x14        // interrupt pending register
#define UART_DIV            0x18        // uart baud rate divisor



#define UART_ADDR(devid) (UART0_CTRL_ADDR + devid * 0x10000)
/***********************************************************
 *  Modifications for physical final project
 * ***********************************************************/
//High 5 board info
#define I2C_CTRL_ADDR       0x10016000 //Address of I2C control instance


//Setup for PCA9685
#define PCA9685_I2C_ADDRESS 0x40
#define PCA9685_MODE1 0x00      /**< Mode Register 1 */
#define PCA9685_LED0_ON_L 0x06  /**< LED0 on tick, low byte*/
#define PCA9685_PRESCALE 0xFE     /**< Prescaler for PWM output frequency */

// MODE1 bits
#define MODE1_SLEEP 0x10   /**< Low power mode. Oscillator off */
#define MODE1_AI 0x20      /**< Auto-Increment enabled */
#define MODE1_RESTART 0x80 /**< Restart enabled */
#define FREQUENCY_OSCILLATOR 25000000 /**< Int. osc. frequency in datasheet */

//Servo
#define SERVOMIN  155 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  355 // This is the 'maximum' pulse length count (out of 4096)

#define MIN_PULSE_WIDTH       800
#define MAX_PULSE_WIDTH       2200
#define DEFAULT_PULSE_WIDTH   1500
#define FREQUENCY             50



#define I2C_BAUDRATE        100000





void set_up_I2C();


/******************************************************************************
 *   eecs388 library api (similar to Arduino)
 *******************************************************************************/
void gpio_mode(int gpio, int mode);
void gpio_write(int gpio, int state);
void delay(int msec);
void delay_usec(int usec);
void ser_init();
void ser_setup(int devid);
int  ser_isready(int devid);
void ser_write(int devid, char c);
void ser_printline(int devid, char *str);
char ser_read(int devid);
int ser_readline(int devid, int n, char *str);
void pwm_init();
void pwm_write(int gpio, int value);
int map(int angle,int lowIn, int highIn, int lowOut, int highOut);
int getServoCycle(int angle);
#endif // __EECS388_LIB_H__
