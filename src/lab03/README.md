# universal asynchronous receiver/transmission (uart)

**contents**

1.  [brief](#brief)
2.  [directory structure](#directory-structure)
3.  [setup project](#setup-project)
4.  [hardware platform](#hardware-platform)
5.  [uart read/write functions](#uart-readwrite-functions)
6.  [eecs388_lib.h](#eecs388_libh)
7.  [eecs388_uart.c](#eecs388_uartc)
-   [memory map](#memory-map)
8.  [eecs388_lib.c](#eecs388_libc)
9.  [`void ser_setup()`](#void-ser_setup)
10. [`void ser_write()`](#void-ser_write)
11. [`ser_printline()`](#ser_printline)
12. [implement `ser_read()`](#implement-ser_read)
13. [appendix](#appendix)
14. [notes](#notes)

## brief

the following readme will explicate a deeper understanding of the hardware platform HiFive1, including its CPU, architecture, memory map, external gpio pin map, and other relevant information.  the following src will have an added implementation of the `ser_read()` function, which reads data form the terminal via the UART connection.  note that we will only be using the `UART 0` universal asynchronous synchronous transmitters 

## directory structure

```
❯ tree
.
├── README.md
├── info.pdf
└── lab03
    ├── docs
    │   ├── FE310-G002.pdf
    │   └── hifive1b-getting-started-guide_v1.1.pdf
    ├── include
    │   └── README
    ├── lib
    │   └── README
    ├── platformio.ini
    ├── src
    │   ├── eecs388_lib.c
    │   ├── eecs388_lib.h
    │   └── eecs388_uart.c
    └── test
        └── README

7 directories, 11 files
```

## setup project

<img width="1040" alt="output" src="https://user-images.githubusercontent.com/65584733/218893074-31ece0a0-5fd2-415f-a533-c58641096080.png">

## hardware platform 

containing board specification, in section 3.3 "usb to jtag and serial ports" find the J-link OB connectivity figure.  the platform uses a specialized chip (Segger J-Link OB) to provide two serial connections via USB.  For this project we will use `UART0`, which is connect to the main CPU (SiFive FE310-G002 CPU) of the platform.  in order to use the `UART0` you need to program the CPU.  for that you need to view the datasheet of the CPU.

0.  hifive rev b components (01-figure.pdf)

1.  usb to JTAG and Serial Ports

the hifive1 reb b is populated with a segger j-link ob module which bridges USB to JTAG and two serial ports used for the `FE310-G002` console, `FE310-G002` JTAG, and `ESP32-SOLO-1` configuration.

-  **JTAG** used for the `FE310-G002` debug
-  **Serial 0** used for the `FE310-F002` console
-  **Serial 1** used for the Expressif Systems `ESP32-SOLO-1`

2.  J-Link OB connectivity (02-figure.pdf)

figure 02 shows the connectivity between the SiFive FE310-G002 SoC, J-Link OB, and Wireless Connectivity on HiFive1 Rev B

3.  `FE310-G002` overview (03-figure.pdf)

this figure shows the overall top-level block diagram of the `FE310-G002`.  the block diagram shows what hardware blocks are integrated in the CPU along with other useful information such as data ram size (16KB DTIM), which is the maximum amount of memory you can use within your program.  this sounds very small, but it's actually big enough to complete this program.  note that there are **2 `UART` blocks**, (`UART0` and `UART1`) of which we will use the `UART0` for this lab.

4.  `FE310-G002 Memory Map (04-figure.pdf)`

in order to program the `UART0` block, you first need to know where the hardware block is mapped in the cpu address space.  the table shows memory mapping information of the hardware blocks of the cpu.  the `UART0` block is mapped between `010013000` - `0x10013FF` (4KB space).  next we need to know how to actually program the `UART` hardware block, which is described in chapter 18 of the manual.  the following table shows the control registers that you need to know to interact with the `UART` hardware block.  

5.  **Register offsets within `UART` memory map**

| Offset | Name | Description |
|:-------|:-----|:------------|
|`0x00`  | `txdata` | Transmit data register |
|`0x04`  | `rxdata` | Receive data register |
|`0x08`  | `txctrl` | Transmit control register |
|`0x0C`  | `rxctrl` | Receive control register |
|`0x10`  | `ie` | UART interrupt enable |
|`0x14`  | `ip` | UART interrupt pending |
|`0x18`  | `div` | Baud rate divisor register |

![03-figure](https://user-images.githubusercontent.com/65584733/218916924-2757d34f-21ab-413f-8198-330ec7c9c8d0.png)


## uart read/write functions

```zsh
❯ tree
.
├── eecs388_lib.c
├── eecs388_lib.h
└── eecs388_uart.c

1 directory, 3 files
```


## `eecs388_lib.h`

```c
#ifndef EECS388_LIB_H
#define EECS388_LIB_H

/* generic definitions */

#define ON          1
#define OFF         0
#define INPUT       0   
#define OUTPUT      1

/* hifive1 platform related definitions */

#define RED_LED     22
#define BLUE_LED    21
#define GREEN_LED   19

/* memory map */

#define GPIO_CTRL_ADDR      0x10012000  // gpio controller base address
#define GPIO_INPUT_VAL      0x00        // input value
#define GPIO_INPUT_EN       0x04        // input enable
#define GPIO_OUTPUT_EN      0x08        // output enable
#define GPIO_OUTPUT_VAL     0x0C        // output_val
#define GPIO_OUPUT_XOR      0x40        // output XOR (invert)

#define CLINT_CTRL_ADDR     0x02000000  // clint controller base address
#define CLINT_MTIME         0xbff8      // timer register

#define UART0_CTRL_ADDR     0x10013000  // uart0 controller base address
#define UART_TXDATA         0x00        // txfifo register
#define UART_RXDATA         0x04        // rxfifo register
#define UART_TXCTRL         0x08        // tx control register
#define UART_RXCTRL         0x0C        // rx control register
#define UART_IE             0x10        // interrupt enable register
#define UART_IP             0x14        // interrupt pending register
#define UART_DIV            0x18        // uart baud rate divisor

/* eecs388 library api */
void gpio_mode(int gpio, int mode);
void gpio_write(int gpio, int state);

void delay(int msec);

void ser_setup();
void ser_write(char c);
void ser_printline(char *str);
char ser_read()

#endif // __EECS388_LIB_H__
```

### memory map

the memory map is a list of the memory addresses that are used to control the gpio pins.

1.  **gpio controller base address  `#define GPIO_CTRL_ADDR     0x10012000`**

- `GPIO_CTRL_ADDR`  is a variable name that represents the base address of the gpio (general purpose input/output controller in the memory mapped i/o mmio address space.  gpio is a memory adddress that _refers_ to the location of the gpio control register on the device.  an address space is a range of memory addresses that can be accessed by the processor, while a register is a small amount of very fast memory that is located in the chip itself.  a register is often used to hold a small piece of data or a memory address that is being actively used by the processor.

- `#define GPIO_CTRL_ADDR     0x10012000`  is a preprocessor macro that defines the base address of the registers that control the gpio pins on the platform that the code is written for in this case it's for the FE310-G002 chip.  

- a preprocessor macro is a fragment of code that is given a name and cal be called multiple times throughout the code.  when the preprocessor encounters the macro name in the code, it replaces the name with the corresponding fragment of code, which is called the macro expansion. we use `#define` for this exact purpose.   

2.  **input value  `#define GPIO_INPUT_VAL     0x00`**

3.  **input enable  `define GPIO_INPUT_EN      0x04`**

4.  **output enable `#define GPIO_OUTPUT_EN     0x08`**

`GPIO_OUTPUT_EN` is a macro that represents the offset in bytes of the register controlling the output enable for the gpio pins.  a register is a small amount of fast memory available on a microcontroller that can be used to hold data or configuration settings, in this case it's used to access the register that controls the output enable for the gpio pins.  so by setting the appropriate bits in this register, the code can configure the gpio pins to be the output pins.

in otherwords `GPIO_OUTPUT_EN` is a constant variable that represents the memory offset of a reister in the gpio controller's memory mapped i/o (MMIO) region.  a register is a special type of memory location within a computer's processor or peripheral devices, which is designed to hold data that can be read or written by a computer program.   in this case the gpio controller has several registers that can be used to configure its behavior and access the values of its input and output pins.  so by writing to or reading from hese registers, the program can interact with the gpio controller to control the state of the pins connected to it, which can be used to control external devices or to read input signals from sensors or switches.

## `eecs388_uart.c`

the `UART`initialization and transmit related code as part of the `eecs388` library has been provided, so let's look at the provided code to better understand how to program the `UART` block, by first looking at the `eecs388_uart.c` module.

the source code contains three main modules, that is `eecs388_art.c`, `eecs388_lib.h`, and `eecs_lib.c` and the program is supposed to read a character from the `UART0` serial port and turn on/off the appropriate LED based on the read character, where r -> red led, g -> green led, b -> blue led.  the first task outlined in the `eecs388_uart.c` file states to read the memory map ch 4 and UART in ch 18.  then there after review the provided the `eecs_lib.c` module.

```c
#include <stdint.h>
#include "eecs_388_lib.h"

int main() {

    char c;
    int led_gpio = GREEN_LED;
    
    // general purpose input output is used to set the direction of the pin to either input or output
    gpio_mode(RED_LED, OUTPUT);
    gpio_mode(GREEN_LED, OUTPUT);
    gpio_mode(BLUE_LED, OUTPUT);

    ser_setup();
    
    while(1) {
        ser_printline("\ntype 'r' or 'g' or 'b': "); 
        c = ser_read();        
        gpio_write(led_gpio, OFF);

        // Echo/write back the character to UART
        ser_write(c);  
        
        switch (c) {
            case 'r':
                led_gpio = RED_LED;
                break;
            case 'g':
                led_gpio = GREEN_LED; 
                break;
            case 'b':
                led_gpio = BLUE_LED; 
                break;
            default:
                ser_printline("ERROR");
                break;
        }
        gpio_write(led_gpio, ON);
    }
}
```

### 1.  `void gpio_mode(RED_LED, OUTPUT)`

the general purpose input output (gpio) mode is a method used to set the direction of the pin to either input or output mode.  if the parameter for mode is `int OUTPUT = 1` then the pin will be set in the direction to output, where it is prepared to send signals to the microcontroller, if the `int gpio = RED_LED = 22` is set in the parameter of the function then the pin that we are choosing to direct will be defined, so in this case it will be set to direction for output to allow signals to be sent on pin number 22.

when this method is invoked the compiler is redirected to the `eecs388_lib.c` module. the `gpio_mode` is defined as follows,

```c
// ...
void gpio_mode(int gpio, int mode) {
    
    unint32_t val;

    if (mode == OUTPUT) {

        val = *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_OUTPUT_EN);

        val |= (1 << gpio);

        *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_OUTPUT_EN) = val;

        if (gpio == RED_LED || gpio == GREEN_LED || gpio == BLUE_LED) {
            
            val = *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_OUTPUT_XOR);

            val |= (1 << gpio);

            *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_OUTPUT_XOR) = val;

    } else if (mode == INPUT) {

        val = *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_INPUT_EN);

        val |= (1 << gpio);

        *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_INPUT_EN) = val;

    } return;
}
// ...
```

1.  `uint32_t val;`  

- is a 32-bit unsigned integer, meaning it can store a binary number with 32 digits, where each digit can either be a a `0` or a `1` the unsigned part means that it only represents non-negative numbers, and the 32-bit part means that it in total it will use 32 bits of memory to store the value.

- therefore the range of values that `val` can store is between 

- in hexadecimal `0x00000000` - `0xFFFFFFFF`

- in binary `00000000 00000000 00000000 00000000` - `11111111 11111111 11111111 11111111`

- in denary `0` - `4,294,967,295`

- the purpose of `val` is to store and manipulate the value of the 32-bit register that controls the behavior of the gpio pin.  `val` will be used to modify the value of the `GPIO_OUTPUT_EN` register this is the output register.  `GPIO_OUTPUT_EN` is a macro that represents the offset in bytes of the register controlling the output enable for the gpio pins.  a register is a small amount of fast memory available on a microcontroller that can be used to hold data or configuration settings, in this case it's used to access the register that controls the output enable for the gpio pins.  so by setting the appropriate bits in this register, the code can configure the gpio pins to be the output pins.

2.  `if (mode == OUTPUT) {`

- this `if` statement is used to check whether the mode parameter is set to `OUTPUT` meaning that the specified pin from the previous parameter get's set to a direction where it is prepared to send signals to the microcontroller.  


## `eecs388_lib.c`

```c
#include <stdint.h>
#include "eecs388_lib.h"

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

void gpio_write(int gpio, int state) {
  uint32_t val = *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_OUTPUT_VAL);
  if (state == ON) 
    val |= (1<<gpio);
  else
    val &= (~(1<<gpio));    
  *(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_OUTPUT_VAL) = val;
  return;
}

inline uint64_t get_cycles(void) {
  return *(volatile uint64_t *)(CLINT_CTRL_ADDR + CLINT_MTIME);
}

void delay(int msec) {
  uint64_t tend; 
  tend = get_cycles() + msec * 32768 / 1000;
  while (get_cycles() < tend) {}; 
}

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

void ser_setup() {
  /* initialize UART0 TX/RX */
  *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_TXCTRL) |= 0x1;
  *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_RXCTRL) |= 0x1;
}

void ser_write(char c) {
  uint32_t regval;
  do {
    regval = *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_TXDATA);
  } while (regval & 0x80000000);
  *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_TXDATA) = c;
}

char ser_read() {

    uint32_t regval;
    do {
        regval = *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_RXDATA);
    } while (regval & 0x80000000);
    return (char)regval;

}
```

## `void ser_setup()` explanation

```c
void ser_setup() {
    *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_TXCTRL) |= 0x1;
    *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_RXCTRL) |= 0x1;
}
```

1.  **components of the code explained**

- `UART0_CTRL_ADDR` is the base address of the UART0 controller
- `UART_TXCTRL` is the offset of the TX control register
- `UART_RXCTRL` is the offset of the RX control register
- `volatile` is a keyword that tells the compiler not to optimize the code (i.e. not to cache the value of the variable in a register)
- `uint32_t` is a 32-bit unsigned integer
- `*` is the dereference operator that returns the value of the variable at the address
- `|=` is the bitwise OR assignment operator that performs a bitwise OR operation and assigns the result to the left operand.
- `0x1` is a hexadecimal number that represents the value 1

2.  **line by line of what the code does**

- `*(volatile uint32_t *)(UART0_CTRL_ADDR + UART_TXCTRL) |= 0x1;` sets the TX enable bit in the TX control register, and assigns the TXFIFO register to 1
- `*(volatile uint32_t *)(UART0_CTRL_ADDR + UART_RXCTRL) |= 0x1;` sets the RX enable bit in the RX control register, and assigns the RXFIFO register to 1

## `void ser_write()`

```c
void ser_write(char c) {
    
    uint32_t regval;

    do {
    
        regval = *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_TXCTRL) |= 0x1;
    
    } while (regval & 0x80000000);

    *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_TXDATA) = c;
}
```

1.  **components of the code explained**

-  `uint32_t` is a 32-bit unsigned integer
-  `regval` is a variable that stores the value of the TX control register which starts at 0 and is updated in the while loop
-  `*(volatile uint32_t *)(UART0_CTRL_ADDR + UART_TXDATA)` is the address of the TX data register which is used to write data to the TX FIFO
-  `(regval & 0x80000000)` is a bitwise AND operation that checks if the TXFIFO is full or not
- `*(volatle uint32_t *)(UART0_CTRL_ADDR + UART_TXDATA) = c;` is the address of the TX data register which is used to write data to the TX FIFO


## `ser_printline()`

```c
void ser_printline(char * str) {

    int i;

    for (i = 0; ; i++) {

        if (str[i] == '\0') {

            ser_write('\n');
            
            break;
        } 

        ser_write(str[i]);
    }
}
```

## implement `ser_read()`

```c
char ser_read() {

    unit32_t regval;

    do {
        
        regval = *(volatile uint32_t *)(UART0_CTRL_ADDR + UART_RXDATA);

    } while (regval & 0x80000000);

    return (regval & 0xFF);
}
```

## notes
```c
// UART)_CTRL_ADDR
// base address where the uart is mapped
// UART_TXDATA
// offset for the specific transmission register
// when you add them together you get the actual address of the register
// gives us the actual address of the transmission register

// volatile tells the compile that whatever is at that address it can change
// everything is a pointer to our transmission register
// * dereferences the pointer and takes the entire pointer and dereferences it
// take the pointer goes to the address and then sets regval to that address, which is the value of the register
// we essentially make a copy of the transmission register
// while( regval & 0x80000000)
// this is a check with a bitwise and operation with the

/*
    1 0 1 0 0 1 ... = regval
  & 1 0 0 0 0 0
  --------------
    1 0 0 0 0 0

hexadecimal number for the register number
the right most bit is the most significant bit at index 31 from the right
bit wise and operation between the two
you take each number and you and it with the other number

if bit number 31 is set on the high five register then the operation is still going on
it means that the FIFO (Queue data structure) is not empty and is still not finished being sent
when the operations for the previous operation is finished the bit will be 0 and the while loop will break
when the high five board does the last operation then the most significant bit will be 0 which makes it 0 which represents false and then the condition
regval & 0x80000000 fails and the while loop breaks


once you exit the loop you it's going to write the value to the address
c will be the parameter of the function 
you need to do something identical, 
bit number 31 is set to 1 as long as the register still does not have a valid character
the bit number 31 as long as the 
read operations goes to the memory address 
*/
```
