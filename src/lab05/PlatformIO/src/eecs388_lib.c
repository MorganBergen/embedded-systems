#include <stdint.h>
#include "eecs388_lib.h"

void gpio_mode(int gpio, int mode)
{
  uint32_t val;
  
  if (mode == OUTPUT) {
    val = *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_OUTPUT_EN);
    val |= (1<<gpio);
    *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_OUTPUT_EN) = val;

#if 0
    // active high
    val = *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_OUTPUT_XOR);
    val |= (1<<gpio);
    *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_OUTPUT_XOR) = val;
#endif

  } else if (mode == INPUT) {
    val = *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_INPUT_EN);
    val |= (1<<gpio);
    *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_INPUT_EN) = val;
  }
  return;
}

void gpio_write(int gpio, int state)
{
  uint32_t val = *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_OUTPUT_VAL);
  if (state == ON) 
    val |= (1<<gpio);
  else
    val &= (~(1<<gpio));    
  *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_OUTPUT_VAL) = val;
  return;
}

inline uint64_t get_cycles(void)
{
  return *(volatile uint64_t *)(CLINT_CTRL_ADDR + CLINT_MTIME);
}

void delay(int msec)
{
  uint64_t tend; 
  tend = get_cycles() + msec * 32768 / 1000;
  while (get_cycles() < tend) {}; 
}

void delay_usec(int usec)
{
  uint64_t tend; 
  tend = get_cycles() + (uint64_t)usec * 32768 / 1000000;
  while (get_cycles() < tend) {}; 
}

void ser_init()
{
  /* initialize UART0 TX/RX */
  *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_TXCTRL) |= 0x1;
  *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_RXCTRL) |= 0x1;
}

void ser_write(char c)
{
  uint32_t regval;
  /* busy-wait if tx FIFO is full  */
  do {
    regval = *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_TXDATA);
  } while (regval & 0x80000000);

  /* write the character */
  *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_TXDATA) = c;
}

void ser_printline(char *str)
{
  int i;
  for (i = 0;; i++) {
    if (str[i] == '\0') {
      ser_write('\n');
      break;
    }
    ser_write(str[i]);
  }
}

char ser_read()
{
  uint32_t regval;
  /* busy-wait if receive FIFO is empty  */
  do {
    regval = *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_RXDATA);
  } while (regval & 0x80000000);
  /* return a byte */
  return (uint8_t)(regval & 0xFF);
}

int ser_readline(int n, char *str)
{
  int i = 0; 
  for (i = 0; i < n; i++) {
    str[i] = ser_read();
    if (str[i] == '\r') {
      ser_read(); /* read '\n' */
      str[i] = 0; 
      return i;
    }
  }
  str[i-1] = 0;
  return i; 
}