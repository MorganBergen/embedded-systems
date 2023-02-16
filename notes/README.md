# homework 1

1.  what is the value stored in register `x2` after all lines are executed, all numbers are decimal (assume `x1 = 200`, `x2 = 300`)

```
Add x3, x1, x2    // x1 = 200, x2 = 300, x1 + x2 = 500, x3 = 500
Sub x2, x3, x2    // x3 = 500, x2 = 300, x3 - x2 = 200, x2 = 200
```

**answer: 200**

2.  in the first lab you performed a "native compilation" of the c program

**answer: false**

3.  a given isa could be implemented with different microarchitectures

yes, a gievn instruction set architectcure (isa) can be implemented using different microarchitectures.  the isa defines the machine language instructions that a processor can execute, while the microarchitecture describes the internal design of the processor and how it executed the instructions defined by the isa.  different microarchitectures can be optimized for different design goals, such as performance, power efficiency, or area efficiency, while still supporting the same isa.  as a result, two processors that implement the same isa can have diffent performance characteristics and feature sets.

**answer: true**

4.  what is the content in memory address 104 after execting the following code?  all numbers are decimal, x0 contains 0.

```assembly
addi x1, x0, 100    // add will add to x1, where 0x = 0, 100 = 100, x0 + 100 = 0 + 100 = 100, x1 = 100
ori  x2, x0, 50     // ori will use bitwise or to set x2
                    // x0 = 0, 50 = 50, 0 OR 50 = 50, x2 = 50
sw   x2, 4(x1)      // sw will store the value in x2 which is 50 into memory address 4(x1)
                    // x1 = 100, 4 = 4, 100 + 4 = 104, store 50 into memory address 104
                    // memory_address[104] = 50
```

**answer: 50**

5.  what information should be included in instruction set architecture (isa)?

a.  opcodes and operands of the cpu
b.  all information required to write assembly programs for the cpu
c.  register names of the cpu
d.  microarchitecture of the cpu
e.  interconnections of functional units inside cpu

instruction set architecture (isa) defines the interface between software and hardware, including the instructions and the format of the instructions that are available for a processor.  the isa should include the opcodes and operands that the cpu can execute, and all the information required to write assembly programs for the cpu, such as the instruction format, addressing modes, and data types.

the register names of the cpu are also part of the isa, as they are used in assembly language programming to hold intermediate results and data.

the microarchitecture of the cpi and the interconnections of functional units inside the cpu are not typically part of the isa.

**answer: a, b, c**

6.  which functionality cannot be provided by the Apple A9 system-on-chip (SoC) inside iPhone?

a.  data storage
b.  sensing
c.  graphics processing
d.  general computation

**answer: b**

7.  match the various integrated circuits with appropriate types

power management circuits - digial or analog - analog

operational amplifiers - digital or analog - analog

microprocessors - digital or analog - digital

fpga - digital or analog - digital

sram - digital or analog - digital

8.  which of the following occurs during preprocessing step on a compiler toolchain?

a.  linking of the machine code

b.  expansion of the included files

c.  removal of comments

d.  generation of the assembly code

**answer:  b, c**

9.  which of the following are examples of attacks on confidentiality (in computing systems)?

a.  a hidden malicious circuit inside the chip passing secret information to an outsider 

b.  mod chip attack on gaming console to bypass restrictions

c.  causing a voltage glitch to corrupt the output of the chip

d.  observing the power consumption of the chip to guess the password

**answer: a, d**

observing the power consumption of the chip to guess the password is an example of an attack on confidentiality in computing systems. This type of attack is known as a power analysis attack, and it involves analyzing the power consumption of a device to extract secret information. In this case, the attacker may be able to guess the password by analyzing the power consumption of the device while the password is being entered.

a hidden malicious circuit inside the chip passing secret information to an outsider is an example of an attack on confidentiality. This is commonly known as a hardware trojan, and it is a type of malicious modification to the chip's design or manufacturing process that can cause it to leak sensitive information to an attacker.

11.  which of the following can be used to measure instruction execution rate?

a.  mW

b.  ms

c.  MIPS

d.  DMIPS

**answer: c, d**

DMIPS stands for Dhrystone MIPS (Million Instructions Per Second). It is a measure of a computer's performance and is commonly used to compare the performance of different processors. Unlike MIPS, which measures the raw instruction throughput of a processor, DMIPS is based on the Dhrystone benchmark, which measures the performance of a processor by executing a set of common tasks. The DMIPS rating of a processor is determined by the number of Dhrystone instructions it can execute in one second.


11.  match the various electronic system with appropriate features

| electronic system         | features                                    |
|:--------------------------|:--------------------------------------------|
| embedded systems          |  often requires real-time operations        |
| general computing systems |  end-user programmable                      |
| general computing systems |  lots of power, memory, & compute resources |
| embedded systems          |  limited application                        |

12.  arrange the following functionalities in a vehicle based on their computing resource requirement (starting with lower requirement at the top)

unordered list:
lowest requirement
-  anti-lock braking system
-  in-vehicle entertainment system
-  blind spot monitoring
-  lane keeping assistance
-  self-driving
highest requirement

in order:
lowest requirement
-  anti-lock braking system
-  in-vehicle audio/video entertainment system
-  blind spot monitoring
-  lane keeping assistance
-  self-driving
highest requirement










