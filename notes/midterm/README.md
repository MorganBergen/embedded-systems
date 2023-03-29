# midterm exam solution

1.  using 8-bit two's complement numbers add -5 with -2

```
 (-2)  1111 1110
+(-5)  1111 1011
-----------------
(-7)   11111 1001 : discard carry-out
```

2.  indicate if the statements are true or false

a.  the range of negative numbers (i.e. all possible negative numbers is larger when using sign magnitude method for representing signed 32-bit numbers.

false

b.  the range of negative numbers (i.e. all possible negative numbers) is larger when using sign magnitude method for representing signed 32-bit numbers

true

c.  in both 2s complement methods all negative numbers start with 1

true

3.  mark the multiplications that can be performed using logical left shift?  assume `Z = 00001111` in binary

6.  write down the content of memory and registers in decimal after all lines of the following assembly code executes.  all numbers in code are decimal

```assembly
addi $r1, $r0, 120  # r1 = 120
srl  $r2, $r1, 1    # r2 = 120
srl  $r3, $r2, 1    # r3 = 30

sw   $r1, 0($r3)    # m(30) = 120
lw   $r4, 0($r3)    # r4 = m(30) = 120
```

answer `r1 = 120`, `r2 = 60`, `r3 = 500`, `mem(30) = 120`

7.  which of the following memory technologies are non-volatile?

-  solid state drive
-  flash memory
-  eeprom

8.  select the correct c code option that wil translate to assembly code below.  the operations (add vs subtract) with associated branch (if vs else) should be consistent between c and assembly code.

10.  what is the total storage capacity in term sof bits of a memory with 8-bit addresses and addressability of 1 byte?

2048 bits = 2^8 * 8 bits

11.  which of the following are not true for volatile type qualifier?

-  compiler can optimize and remove volatile objects if there is no use in the code
-  indicates that an object's value is constant

12.  in the memory map of sifive fe310 hardware, which memory technoligy is used for storing stack, heap, bss, data segments during program execution?

-  on chip volatile memory

13.  which of the following memories can be designed with transistors only

-  sram and registers

14.  for the following assembly program how manytimes the addi instruction inside the loop will execute?  all instructions are based on 32-bit mips isa

```assembly
addi $r1, $r0, 4
Loop:
    addi $r1, $r1, -2
    bne  $r1, $r0, Loop
    sub $r1, $r0, r0
```

2 times

15.  let us assume that the following code is in the memory and ready for execution.  the lines with `func()` inside main indicate function calls.  at a given 

18.  which are the possible reasons for choosing c language over java for programming embedded hardware?

-  low memory requirement and faster code execution

19.  what operation is always needed before storing (push operation) something to the stack?

-  decreasing the stack pointer value

20.  what information is not required in instruction set architecture (isa)?

-  circuit diagram of the alu, implementation and interconnections of functional units inside cpu
