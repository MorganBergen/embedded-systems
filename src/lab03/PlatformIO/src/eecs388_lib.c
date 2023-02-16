/*
 * @file        eecs388_lib.c
 * @date        Wed Feb 15 18:39:51 CST 2023
 * @author      morgan bergen
 * @brief       EECS 388 Lab 03 Thursday 9 AM
 */

#include <stdint.h>
#include "eecs388_lib.h"


/*
 * @pre     None
 * @param   gpio_port: GPIO port to be initialized
 *          mode: GPIO mode to be set
 * @post    GPIO port is initialized
 * @return  None
 * @brief   sets GPIO_OUTPUT_EN or GPIO_INPUT_EN register
 */
void gpio_mode(int gpio, int mode) {
  uint32_t val;
  
  if (mode == OUTPUT) {
    val = *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_OUTPUT_EN);
    val |= (1<<gpio);
    *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_OUTPUT_EN) = val;

    if (gpio == RED_LED || gpio == GREEN_LED || gpio == BLUE_LED) {
      // active high
      val = *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_OUTPUT_XOR);
      val |= (1<<gpio);
      *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_OUTPUT_XOR) = val;
    }
  } else if (mode == INPUT) {
    val = *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_INPUT_EN);
    val |= (1<<gpio);
    *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_INPUT_EN) = val;
  }
  return;
}

/* 
 * @pre     None
 * @param   gpio_port: GPIO port to be initialized
 *          value: value to be set
 * @post    GPIO port is initialized
 * @return  None
 * @brief   sets GPIO_OUTPUT_VAL register
 */
void gpio_write(int gpio, int state) {
  uint32_t val = *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_OUTPUT_VAL);
  if (state == ON) 
    val |= (1<<gpio);
  else
    val &= (~(1<<gpio));    
  *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_OUTPUT_VAL) = val;
  return;
}

/*
 * @pre     None
 * @param   void
 * @post    None
 */
inline uint64_t get_cycles(void) {
  return *(volatile uint64_t *)(CLINT_CTRL_ADDR + CLINT_MTIME);
}

void delay(int msec) {
  uint64_t tend; 
  tend = get_cycles() + msec * 32768 / 1000;
  while (get_cycles() < tend) {}; 
}

/**
 * @pre     None
 * @param   str pointer
 * @return  None
 */
void ser_printline(char *str) {
  int i;
  for (i = 0;; i++) {
    if (str[i] == '\0') {
      ser_write('\n');
      break;
    }
    ser_write(str[i]);
  }
}

/*
 * @pre     None
 * @param   None
 * @return  None
 * @brief   initializes UART TX/RX
 */
void ser_setup() {
  *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_TXCTRL) |= 0x1;
  *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_RXCTRL) |= 0x1;
}

/*
 * @pre     None
 * @param   character to send via the UART
 * @return  None
 * @brief   writes a character to the UART 0 FIFO, while busy-waiting if TX FIFO is full
 */
void ser_write(char c) {
  uint32_t regval;
  do {
    regval = *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_TXDATA);
  } while (regval & 0x80000000);

  *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_TXDATA) = c;
}

/**
 * read a chacter from the uart 0
 * 
 * Input: None
 * Return: read byt
 */
char ser_read() {
 // regval is a place holder for the actual return value of the function
  uint32_t regval;

  // busy-wait if rx FIFO is empty
  do {
    // the regval is the value of the RXDATA register
    // by using the * operator, we are dereferencing the address of the RXDATA register
    // by using the volatile keyword, we are telling the compiler that the value of the register may change at any time
    // by using the uint32_t keyword, we are telling the compiler that the value of the register is a 32 bit unsigned integer
    // the next * operator is dereferencing the address of the register
    // so (uint32_t *) is casting the value of the register to a 32 bit unsigned integer
    // we know that the he UART0 controller is a used to access the UART0 control register to set the baud rate, enable the transmitter and receiver, and send and receive data over the serial port.

    // and the serial port is the communication interface between two devices, where data is transmitted one bit at a time in sequential order over a serial communication channel.the serial port is a feature of the sifive FE310 - G002 and it provides a way to communicate with the board from another device, such as this personal computer via a usb micro - b cable.
   // so we add UART0_CTRL_ADDR to the address of the RXDATA register to get the address of the RXDATA register in the UART0 controller 
    regval = *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_RXDATA);
  } while (regval & 0x80000000);

  // then we return the value of the RXDATA register  
  return (regval & 0xFF);

}

