# universal asynchronous receiver/transmission (uart)

**contents**

1.  [brief](#brief)
2.  [directory structure](#directory-structure)
3.  [setup project](#setup-project)
4.  [hardware platform](#hardware-platform)
5.  [uart read/write functions](#uart-readwrite-functions)
6.  [eecs388_lib.c](#eecs388_libc)
7.  [eecs388_lib.h](#eecs388_libh)
8.  [eecs388_uart.c](#eecs388_uartc)
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

add screenshot of vs code

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

4.  `FE310-G002 Memory Map (04-figure.pdf)


## notes

```
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
