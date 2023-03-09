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
#define GPIO_OUTPUT_XOR     0x40        // output XOR (invert)

#define CLINT_CTRL_ADDR     0x02000000  // CLINT block base address
#define CLINT_MTIME         0xbff8      // timer register

#define UART0_CTRL_ADDR     0x10013000  // UART0 controller base address 
#define UART_TXDATA         0x00        // TXFIFO register
#define UART_RXDATA         0x04        // RXFIFO register
#define UART_TXCTRL         0x08        // TX control register
#define UART_RXCTRL         0x0C        // RX control register
#define UART_IE             0x10        // interrupt enable register
#define UART_IP             0x14        // interrupt pending register
#define UART_DIV            0x18        // uart baud rate divisor

/******************************************************************************
 *   eecs388 library api (similar to Arduino)
 *******************************************************************************/
void gpio_mode(int gpio, int mode);
void gpio_write(int gpio, int state);

void delay(int msec);
void delay_usec(int usec);

void ser_init();
void ser_write(char c);
void ser_printline(char *str);
char ser_read();
int  ser_readline(int n, char *str);

void pwm_init();
void pwm_write(int gpio, int value);
#endif // __EECS388_LIB_H__
