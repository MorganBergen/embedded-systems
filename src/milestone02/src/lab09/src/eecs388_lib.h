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
#endif // __EECS388_LIB_H__
