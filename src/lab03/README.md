# universal asynchronous receiver/transmission (uart)

**contents**

1.  [brief](#brief)
2.  [directory structure](#directory-structure)
3.  [setup project](#setup-project)
4.  [hardware platform](#hardware-platform)
5.  [uart read/write functions](#uart-readwrite-functions)
6.  [`eecs388_lib.h`](#eecs388_libh)
7.  [`eecs388_uart.c`](#eecs388_uartc)
-   [memory map preprocessor directives](#memory-map-preprocessor-directives)
8.  [`eecs388_lib.c`](#eecs388_libc)
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

### memory mapping preprocessor directives

the memory map is a list of the memory addresses that are used to control the gpio pins.

1.  `#define GPIO_CTRL_ADDR     0x10012000` gpio controller base address  

- `GPIO_CTRL_ADDR`  is a variable name that represents the base address of the gpio (general purpose input/output controller in the memory mapped i/o mmio address space.  gpio is a memory adddress that _refers_ to the location of the gpio control register on the device.  an address space is a range of memory addresses that can be accessed by the processor, while a register is a small amount of very fast memory that is located in the chip itself.  a register is often used to hold a small piece of data or a memory address that is being actively used by the processor.

- `#define GPIO_CTRL_ADDR     0x10012000`  is a preprocessor macro that defines the base address of the registers that control the gpio pins on the platform that the code is written for in this case it's for the FE310-G002 chip.  

- a preprocessor macro is a fragment of code that is given a name and cal be called multiple times throughout the code.  when the preprocessor encounters the macro name in the code, it replaces the name with the corresponding fragment of code, which is called the macro expansion. we use `#define` for this exact purpose.   

-  in general `#define GPIO_CTRL_ADDR       0x10012000` is a preprocessor directive that defines the `GPIO_CTRL_ADDR` macro to the memory address of the control register in the memory-mapped i/o address space of the FE310-G002 CPU.  so when the program reads from or writes to this memory address, it is accessing the GPIO control register and modifying its contents.  the gpio control register itself contains many individual fields, each of which controls different aspects of the gpio's, such as whether they are configured as inputs or outputs which you will see are defined below, to see whether the state of the upp-up and pull-down resister etc.  

2.  `#define GPIO_INPUT_VAL     0x00` input value  

-  this preprocessor macro defies the offset value for the register that reads the input value of the gpio pins.

-  in the case of computer architecture an offset value is a value added to a base address to compute the address of a memory location.  when a program wants to access a specific piece of data in memory, it needs to calculate the actual memory address where the data is located.  to do this, the program uses the base address of the memory region where the data is stored, and then adds an offset to that base address to get the final memory address.  the offset is usually expressed as a number of bytes, and is used to specify the distance between the starting memory address and the desired memory location.

-  so in this case the gpio pins' input value can be read from register located at the offset value from the base address of the gpio controller, which is defined as `GPIO_CTR_ADDR`.  the base address serves as a reference point for the offset values used to access other registers in the gpio controller.  the input value register has an offset value of `0x00`, which is added to the base address to obtain the memory address of the register.

3.  `#define GPIO_INPUT_EN      0x04` input enable  

-  `GPIO_INPUT_EN` is a preprocessor macro that defines the offset value of the `GPIO` input enable register within the `GPIO` controller's address space.  when you add this value to the base address of the `GPIO` controller variable name `GPIO_CTRL_ADDR` which is `0x10012000`, you get the memory address of the `GPIO` input enable register. 

- this register is used to **enable** `GPIO` pins as inputs, meaning that the `GPIO` pins as inputs, meaning that the `GPIO` controller will monitor the voltage level of those pins and allow the device to read those values.  in other wordsm the `GPIO` input enable register controls which pins are configued as inputs.

4.  `#define GPIO_OUTPUT_EN     0x08` output enable 

- `GPIO_OUTPUT_EN` is a macro that represents the offset in bytes of the register controlling the output enable for the gpio pins.  as previously stated a register is a small amount of fast memory available on a microcontroller that can be used to hold data or configuration settings, in this case it's used to access the register that controls the output enable for the gpio pins.  so by setting the appropriate bits in this register, the code can configure the gpio pins to be the output pins.

-  the output enable register is located at the address that is equal to the base address of the gpio controller @ address `0x10012000` plus the offset value of `0x08`

-  so in the code shown in the `eecs388_lib.c` implementation file within the `gpio_mode` function definition `*(volatile uint32_t *) (GPIO_CTRL_ADDR + GPIO_OUTPUT)` is a pointer to the output enable register and by setting the bit corresponding to the gpio pin we want to use as an output, we enable it.

5.  `#define GPIO_OUTPUT_VAL     0x0C` output value 

-  `GPIO_OUTPUT_VAL` is a macro that defines an offset value for the output value register within the gpio controller.  it specifies the location of the register that holds the current output state of each pin on the gpio controller.

-  the output value register can be used to set the state of a specific pin by writing to it directly.  as you will see later on in the implementation file `eecs388_uart.c` this will specifically be utilized, in the `gpio_write` function.  where the output value register is accessed by adding the `GPIO_CTRL_ADDR` base address to the `GPIO_OUTPUT_VAL` offset to get the address of the register.  the desired output value is then written to this register by setting or clearing the appropriate bit.  for example to set a pin to high, a `1` is written to the corresponding bit in the output value register.

6. `#define GPIO_OUTPUT_XOR     0x40` output xor (invert) 

-  `GPIO_OUTPUT_XOR` is a macro that defines the values `0x40` to the identifier `GPIO_OUTPUT_XOR`.  this identifier is typically used to set or toggle a specific output bit on the gpio port, where the bit is XORed with its current value.

-  for example, if a particular bit of the output port is currently set to `0` and `GPIO_OUTPUT_XOR` is applied to that bit, the bit will be toggled to 1.  if the bit was already 1, applying `GPIO_OUTPUT_XOR` would toggle it back to `0`.

-  `XOR` refresher the short for exclusive or is a logical operation that outputs true only when inputs differ.  it is a binary operator, meaning that it operatoes on two binary digits or bits.  specifically, the xor operator returns a `1` or `true` if and only if one of the two bits being compared is `1`.  if both bits are the same (`1 xor 1` or `0 xor 0`) the `xor` operator returns a `0` or `false`.

7.  `#define CLINT_CTRL_ADDR    0x02000000` core local interruptor controller address 

-  `CLINT_CTRL_ADDR` has a constant base address value of `0x02000000`, it's a preprocessing directive.  this address in the memory map on the cpu specifically refers to the address of the core local interruptor controller. also known as CLINT controller.

- the clint is a hardware block that provides timer and interrupt services to the FE310-G002 processor on the board.  the clint has a number of register that can be accessed at specific memory locations, and the address `0x02000000` is the base address for those registers.

8.  `#define CLINT_MTIME        0xbff8` clint m time register

-  the `CLINT_MTIME` is a maco that defines the memory-mapped address of the machine time register in the CLINT (core local interrupter) block of the hardware platform.

- the machine timer register is a 64-bit register that stores the current time of the hardware platform, and is incremented by a timer at a fixed frequency.  it is typically used in embedded systems to perform tasks that require timing or time-stamping, such as scheduling tasks, measuring the duration of an event, or generating precise delays.

9.  `#define UART0_CTRL_ADDR        0x10013000` uart0 controller base address

-  `UART0_CTRL_ADDR` defines a symbolic name `UART0_CTRL_ADDR` that represents the memory address of the `UART0` controller on the board.  the `UART0` controller is responsible for managing the serial communication between the microcontroller and a device connected to its serial port.

-  the `UART0` controller is a used to access the `UART0` control register to set the baud rate, enable the transmitter and receiver, and send and receive data over the serial port.

- the serial port is the communication interface between two devices, where data is transmitted one bit at a time in sequential order over a serial communication channel.  the serial port is a feature of the sifive FE310-G002 and it provides a way to communicate with the board from another device, such as this personal computer via a usb micro-b cable.

-  a baud rate is the number signal or symbol changes (events) per second in a communication channel.  it represents the rate at which data is transmitted over a communication channel and is typically measured in bits per second.  (bps)

10.  `#define UART_TXDATA         0x00`  txfifo register

-  `UART_TXDATA` represent the offset of the transmit FIFO (first in first out) queue data register within the `UART0` control address space.  when a byte is sent via the `UART0` interface, the byte is written into this register and added to the transmit FIFO.  

-  the transmit FIFO is a buffer within the `UART0` interface that holds bytes waiting to be sent over the serial connection.

-  a buffer is a region of memory used to temporarily hold data while it is being move from one place to another.  it is an intermediate place for data to be stored and retrieved, buffers are commonly used to speed up input/output operations and to balance the different rates at which data is received and processed by a computer.

-  so when the program needs to send data through the `UART0` interface, it writes the data to the `UART_TXDATA` register offset by adding it to `UART0_CTRL_ADDR`

11.  `#define UART_RXDATA         0x04` rxfifo register

-  `UART_RXDATA` is a macro that defines the offset of the receive FIFO data register within the `UART0` control address space.  when a byte is received via the `UART0` interface, the byte is read from this register and removed from the receive FIFO.

`#define UART_TXDATA         0x00        // TXFIFO register`
`#define UART_RXDATA         0x04        // RXFIFO register`
`#define UART_TXCTRL         0x08        // TX control register`
`#define UART_RXCTRL         0x0C        // RX control register`

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
