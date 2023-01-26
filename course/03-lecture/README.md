# lecture 3

**contents**

1.  [example inclass quiz](#example-inclass-quiz)
2.  [embedded systems primarily uses c programming](#embedded-systems-primarily-uses-c-programming)
3.  [bits vs bytes](#bits-vs-bytes)
4.  [declaring variables](#declaring-variables)
5.  [primitive data types](#primitive-data-types)
6.  [type modifiers](#type-modifiers)
7.  [type qualifiers](#type-qualifiers)
8.  [data storage in memory](#data-storage-in-memory)
9.  [intro to number systems](#intro-to-number-systems)
10. [positional system](#positional-system)
11. [converting to decimal](#converting-to-decimal)
12. [number systems](#number-systems)
13. [categories of numbers](#categories-of-numbers)
14. [unsigned numbers](#unsigned-numbers)
15. [2s complement numbers](#2s-complement-numbers)
16. [converting from 2s complement to signed decimal](#converting-from-2s-complement-to-signed-decimal)
17. [fractional numbers: float and double](#fractional-numbers-float-and-double)


### example inclass quiz

1.  assembly language programs generated from the same C program is the same for different instruction set architecture (ISA)

- false

2.  the same isa can be implemented with two different microarchitectures

- true

3.  the preprocessing step of the compiler tool-chain expands the assembly code to generate a machine-readable binary

- false

4.  embedded systems are generally not programmable by end-user/consumers

- true

### embedded software market share 

- C:    70%
- C++:  25%
- assembly, java, etc.:  5%

see [C: The Immortal Programming Language](https://embeddedgurus.com/barr-code/2018/02/c-the-immortal-programming-language/)

### embedded systems primarily uses c programming

- **high-level**
    - feasibility of learning, portability across OS, hardware independent compared to assembly

- **low level**
    - lower code overhead for execution
    - ex:  java we need a JVM (java virtual machine) in addition to the jar files (executable)
    - bitwise operation (programming registers)
        - changing register values
    - memory management (access & allocation)
        - pointers, dynamic memory allocation
    - I/O operation
        - using pointers we can configure I/O devices

### bits vs bytes

- **bit**
    - smallest unit of information
    - 0 or 1

- 8 bits == 1 byte
- 1 word == 16 bits

$ b_{7} b_{6} b_{5} b_{4} b_{3} b_{2} b_{1} b_{0} $

- most significant bit (MSB)
    - left most bit, has the most significant impact

- least significant bit (LSB)
    - right most bit, has the least significant impact

- to understand a value of a variable and use it properly, a compiler needs to understand both the raw values and the type of variable

### declaring variables

- variable is nothing but the name of a memory location
- declaration is needed before using variable in prohram
- declaration needs (at least) two things:
    - data tuype
    - variable name

```c
<data-type> <var-name>; // declaration
int var;
```

- variable can be initialized during declaration

```c
<data-type> <var-name> = <value>; // declaration
int var = 7;
```

- when we declare once, we don't need to declare the type again (within the same function/scope)
    - `int var;`
    - `var = 13;`

- we can assign variable to a variable
    - `int var = 13;`
    - `int new_var = var;`

### primitive data types

data type       size        range                       description
char            1 byte      -128 to 127 or 0 to 255     character
int             2 bytes     -32,768 to 32,767           integer
float           4 bytes     1.2E-38 to 3.4E+38          floating point
void            1 byte      -128 to 127 or 0 to 255     void

- void
    - function return type:  when function doesnt return anything
    - `void func() { printf("hi"); }`
    - universal pointer type:  when pointer can point to any data type
    - `void* ptr;`

#### data types in general

- data type is a way for the programmer to tell the compiler or interpreter how the data will be used/processed
- allows programmer to define precision, range, and sign of the data

**tree of data types**

```

                data type
              /      |     \
     primitive   derived    user-defined
        |          |          |
      char       array      structure
      int        pointer    union
      float      function   enum
      double
      void
```

### type modifiers

`<type modifier (s)><data-type> <var name> = <value>;`

increase the size of data types of change their properties
- short
- long
- unsigned
- signed

`unsigned long int var = 20;`

### type qualifiers

`<type qualifier (s)><data-type> <var name> = <value>;`

- the keywords which are used to modify the properties of a variable are called type qualifiers
    - **const**:  variable can't be changed once it is defined
    - **volatile**:  tells the compiler that the value of the variable may chnage at any time - without any action being taken by the nearby code (could chnage by the hardware instead)

```
void main() {
    int i = 9;
    const int x = 10;
    clrscr();

    i = 15;
    x = 100; // creates an error
```

- example of variable with such change:
    - registers of memory-mapped peripheral
    - global variables modified by an interrupt service routine
    - global variables accessed by multiple tasks within a multi-threaded application
    - [How to Use C's volatile Keyword](https://barrgroup.com/embedded-systems/how-to/c-volatile-keyword)

### data storage in memory

$ 1000_{2} = 8_{10} $

$ 0002_{2} = 0_{10} $ // change MSB:  high impact

$ 1001_{2} = 9_{10} $ // change LSB:  low impact

the reason as to why we have octal and hexidecimal, is because people needed to write code to represent binary numbers

### intro to number systems

```txt
positional system       base        allowed digits
binary                  base 2      0, 1
octal                   base 8      0, 1, 2, 3, 4, 5, 6, 7
decimal                 base 10     0, 1, 2, 3, 4, 5, 6, 7, 8, 9
hexadecimal             base 16     0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F
```

### positional system

- value of a number is defined by
    - digit
    - index
    - base

- converting to decimal
    - digit x base ^ index
    - value = sum of products

### converting to decimal (cont.)

- binary (base 2)
    - symbols: 0, 1

### number systems

- conversion to deciaml:  hand calculation is hard for large numbers
- need sum(digit * base^index) equation

```
decimal         hexadeciaml             binary
------------------------------------------------------------
0               0x0                     0b0
2               0x2                     0b10
9               0x9                     0b1001
10              0xA                     0b1001
15              0xF                     0b11111
31              0x1F                    0b11111
128             0x80                    0b10000000
131             0x83                    0b10000011
32768           0x8000                  0b1000000000000000
```

1F in hex is 31 in decimal

15 * 16^0 + 1 * 16^1 = 31

### categories of numbers

- unsigned
- signed
- factional

### unsigned numbers

- no sign, only magnitude/value
- n-bit binary number
- decimal value
- example

### 2s complement numbers

- most common method of representing signed integers in computers
- getting two's complement of an integer
    - write the number 28 in binary e.g. 00011100
    - invert the digits                  11100011
    - add 1 to the result                11100100
    - that is how one would write -28 in 8 bit binary 
    - a leading 1 means a negative number, a leading 0 means positive in 2s complement

















