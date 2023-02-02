#ifndef __EECS388_LIB_H__
#define __EECS388_LIB_H__

/******************************************************************************
 *   generic definitions
 *******************************************************************************/
#define ON      1
#define OFF     0
#define OUTPUT  1
#define INPUT   0

/******************************************************************************
 *   hifive1 platform related definitions
 *******************************************************************************/
#define RED_LED             22 // gpio 22
#define BLUE_LED            21 // gpio 21
#define GREEN_LED           19 // gpio 19

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

/******************************************************************************
 *   eecs388 library api (similar to Arduino)
 *******************************************************************************/
void gpio_mode(int gpio, int mode);
void gpio_write(int gpio, int state);

void delay(int msec);

#endif // __EECS388_LIB_H__
