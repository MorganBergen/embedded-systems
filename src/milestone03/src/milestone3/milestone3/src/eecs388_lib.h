#ifndef __EECS388_LIB_H__
#define __EECS388_LIB_H__

#include <stdio.h>

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

#define MAX_INTERRUPTS      16
#define MAX_EXT_INTERRUPTS  52

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

#define CLINT_CTRL_ADDR     0x02000000  // CLINT controller base address
#define CLINT_MTIME         0xbff8      // timer register
#define CLINT_MTIMECMP      0x4000      // timer compare register

#define UART0_CTRL_ADDR     0x10013000  // UART0 controller base address 
#define UART1_CTRL_ADDR     0x10023000  // UART1 controller base address
#define UART_TXDATA         0x00        // TXFIFO register
#define UART_RXDATA         0x04        // RXFIFO register
#define UART_TXCTRL         0x08        // TX control register
#define UART_RXCTRL         0x0C        // RX control register
#define UART_IE             0x10        // interrupt enable register
#define UART_IP             0x14        // interrupt pending register
#define UART_DIV            0x18        // uart baud rate divisor

#define MCAUSE_INT          0x80000000UL
#define MCAUSE_CAUSE        0x000003FFUL
#define MSTATUS_MIE_BIT     (3)  // global interrupt enable bit mask. 
#define MIE_MTIE_BIT        (7)  // machine mode timer interrupt enable bit mask. 
#define MIE_MEIE_BIT        (11) // machine mode external interrupt enable bit mask. 

#define PLIC_CLAIM_ADDR     0x0C200004  // PLIC claim/complete register



/***********************************************************
 *  Modifications for physical final project
 **********************************************************/

//Buffer Size that accomodates "read" and the float32 
#define BUFFER_SIZE         25

//High 5 board info
#define I2C_CTRL_ADDR       0x10016000 //Address of I2C control instance

//Setup for PCA9685
#define PCA9685_I2C_ADDRESS 0x40
#define PCA9685_MODE1 0x00      /**< Mode Register 1 */
#define PCA9685_LED0_ON_L 0x06  /**< LED0 on tick, low byte*/
#define PCA9685_LED1_ON_L 0x0A 
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
/******************************************************************************
 *   macros
 *******************************************************************************/
#define read_csr(reg) ({ unsigned long __tmp; \
  asm volatile ("csrr %0, " #reg : "=r"(__tmp)); \
  __tmp; })

#define write_csr(reg, val) ({ \
  asm volatile ("csrw " #reg ", %0" :: "rK"(val)); })

#define UART_ADDR(devid) (UART0_CTRL_ADDR + devid * 0x10000)

#define printf(x...) {sprintf(__buf, x); ser_printline(0, __buf);}
 
/******************************************************************************
 *   eecs388 library api (similar to Arduino)
 *******************************************************************************/
extern char __buf[80];

void gpio_mode(int gpio, int mode);
void gpio_write(int gpio, int state);

void set_cycles(uint64_t cycle);
uint64_t get_cycles(void);

void delay(int msec);
void delay_usec(int usec);

void enable_timer_interrupt();
void enable_external_interrupt();
void enable_interrupt();
void disable_interrupt();
void register_trap_handler(void *func);

void ser_setup(int devid);
int  ser_isready(int devid);
void ser_write(int devid, char c);
void ser_printline(int devid, char *str);
char ser_read(int devid);
int ser_readline(int devid, int n, char *str);

void set_up_I2C();
int map(int angle,int lowIn, int highIn, int lowOut, int highOut);
int getServoCycle(int angle);
#endif // __EECS388_LIB_H__
