# embedded-systems
------------------------------------------------------------

**contents**

1.  [Introduction to Embedded Systems](./course/01-introduction-to-embedded-systems.md)
2.  [lab01]

### embedded systems c / c++

to develop embedded systems, you must first understand c/c++ programming language particularly embedded c.  embedded c is a collection of language extensions for c programming developed by the c standard group to solve concerns of commonality between c extensions for different embedded systems.  The one more important distinction between c and embedded c is about _usage_.  Therefore it is strongly advised to grasp certain fundamental concepts of c programming language in order to fully comprehend both the theory and labs of this course.

**topcs**
1.  variables
2.  data types
3.  operators
4.  conditions
5.  loops
6.  string
7.  user input
8.  arrays
9.  pointers
10. functions


### embedded systems c / c programming resources

[embedded c w3 schools](https://www.w3schools.com/c/index.php)

[introduction to the c programming language for embedded applications](https://www.allaboutcircuits.com/technical-articles/introduction-to-the-c-programming-language-for-embedded-applications/)

[online gdb](https://www.onlinegdb.com/online_c_compiler)

[c programming tutorial](https://www.youtube.com/watch?v=KJgsSFOSQv0)

**about**

The purpose of this repository is to illustrate material pertaining to the course embedded systems.  An embedded system is an intelligent system with special-purpose computation capabilities, (e.g. smart appliance, cars, medical devices, etc.)  The material will cover the hardware and software architecture of embedded systems, as how to program a microprocessor to interact with the physical world through sensors and actuators.

The conceptual material consists of

- introduction to embedded systems, defining embedded systems, differentiating embedded systems from general-purpose computers.

- embedded software echopsystem, introduction to tools and enviroments for developing embedded software (build toolchain, gnu make, ide, git)

- c programming refresher

- RV32 ISA, a brief introduction to RISC-V assembly language

- microprocessor's memory address space

- i/o how to interact with the physical world using sensors and actuators

- interrupt, difference between interrupt and polling, how to use them, and the implications of using them

- concurrency and threads, how to utilize the available parallelism in the hardware and develop concurrent embedded software

- scheduling and real-time scheduling concepts in linux

- cpu and memory architecture, how instructions get executed in the hardware and the micro-architecture of a basic RISC-V, single-cycle processor.
