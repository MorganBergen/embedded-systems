# operations of the computer hardware

...
design principle 1:  simplicity favors regularity


# operands of the computer hardware

unlike programs in high-level languages the operands of arithmetic instructions are restricted; they must be from a limited number of special locations built directly in hardware called registers.  registers are the bricks of computer construction:  registers are primitives used in hardware design that are also visible to the programmer when the computer is completed.  the size of a register in the mips architecture ios 32 bits; groups of 32 bits occur so frequently that are given the name word in the mips architecture.  

one major difference between the variables of a programming language and registers is that the limited number of registers, typically 32 on current computers.  mips has 32 registers, thus continuing in our top-down stepwise evolution of the symbolic representation of the mips languaghe, in this section we have added the restriction that the three operands of mips arithmetic instructions must each be chosen from one of the 32 32-bit registers.

the reason for the limit of 32 registers may be found in the second of our four underlying design principles of hardware technology:  

design principle 2:  smaller the faster

a vary large number of registers may increase the clock cycle time simply because it takes electronic signals longer when they must travel farther.  so the effective use of registers is key to program performace.  although we could simply write instructions using numbers for registers, from 0 to 31, the mips convention is to use two-character names following a dollar sign to represent a register.  

-  `$s0, $s1` for registers that correspond to variables in c
-  `$t0, $1` for temporary registers needed to compile the program into mips instructions

### compiling a c assignment using registers

it's the compilers job to associate program variables with registers, take for instance the assignment statement:

```cpp
f = (g + h) - (i +j);
```

```mips
add $t0, $s1, $s2   # register $t0 contains g + h, equivalent to t0 = g + h
add $t1, $s3, $s4   # register $t1 contains i + j, 
sub $s0, $t0, $t1
```


# supporting procedures in computer hardware

a procedure or a function is one tool C or java programmers use to structure programs, both to make them easier to understand and to allow code to be reused.  procedures allow the programmer to concentrate on just one portion of the task at a time, with parameters acting as a barrier between the procedure and the rest of the program and data, allowing it to be passed values and return results.  

you can think of a procedure like a spy who leaves with a secret plan, acquires resources, performs the task, covers her tracks, and then returns to the point of origin with the desired result.  nothing else should be perturbed once the mission is complete.  a spy operates on only a need to know basis so the spy cant make assumptions about his employer.  similarly, in the execution of a procedure the program must follow these six steps:

1.  place parameters in a place where the procedure can access them.
2.  transfer control to the procedure
3.  acquire the storage resources needed for the procedure
4.  perform the desired task
5.  place the result value in a place where the calling program can access it
6.  return control to the point of origin, since a procedure can be called from several points in the program

registers are the fastest place to hold data in a computer, so we want to use them as much as possible.  


## definitions

1.  word:  the natural unit of access in a computer, usually a group of 32 bits; corresponds to the size of a register in the mips architecture.
2.  register:  a primitive in hardware design that is also visible to the programmer when the computer is completed; the size of a register in the mips architecture is 32 bits.
3.  procedure:  a tool C or java programmers use to structure programs, both to make them easier to understand and to allow code to be reused; procedures allow the programmer to concentrate on just one portion of the task at a time, with parameters acting as a barrier between the procedure and the rest of the program and data, allowing it to be passed values and return results.
4.  parameter:  a variable that is passed to a procedure; the procedure can access the parameter but cannot change it.
5.  local variable:  a variable that is declared inside a procedure; the procedure can access the local variable but cannot change it.
6.  return value:  the value returned by a procedure; the calling program can access the return value.
7.  stack:  a data structure that stores the return addresses of procedures; the stack is a last-in, first-out (LIFO) data structure.
8.  stack pointer:  a register that points to the top of the stack; the stack pointer is used to access the stack.
9.  frame pointer:  a register that points to the bottom of the stack frame; the frame pointer is used to access the local variables of a procedure.
10.  stack frame:  a region of the stack that stores the local variables of a procedure; the stack frame is created when a procedure is called and destroyed when the procedure returns.
11.  stack overflow:  an error that occurs when the stack frame of a procedure is larger than the stack; the stack overflow error occurs when the stack pointer and the frame pointer point to the same location.
12.  stack underflow:  an error that occurs when the stack frame of a procedure is smaller than the stack; the stack underflow error occurs when the stack pointer and the frame pointer point to different locations.
13.  stack frame diagram:  a diagram that shows the layout of a stack frame; the stack frame diagram shows the stack pointer, the frame pointer, the return address, the local variables, and the parameters.
14.  procedure call:  a statement that transfers control to a procedure; the procedure call is followed by a list of arguments that are passed to the procedure.
15.  procedure return:  a statement that
