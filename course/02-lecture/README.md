# embedded software development
https://fr.wikipedia.org/wiki/GNU_Make
**contents**

### context

- we can look at embedded systems from different abstraction layers
- software abstraction
    - application programs, operating system, compiler

- hardware
    - primary component:  microprocessor or microcontroller
    - abstractions:  microarchitecture and instruction set architecture, digital logic, transistor

### example

- application software:  word procesor, internet browser
- system software:  operating system, compiler
    - os:  a supervising software that manages hardware resources to run the application software
    - compiler:  translates program to machine executable binary
- hardware:  processor, memory, io

### isa instruction set architecture

- isa is the grammar that translates high level language to machine code
- ISA acts as an interface between the hardware and the software
- provides a model/abstratcion of the hardware taht can be controlled by writing programs in assembly langugage
- isa can be considered as a manial for the assembly programmer
- the isa specifies the:
    - memory organization
    - register set
    - instruction set (opcodes, data types, and addressing modes)
- ARM, x86, MIPS, RISC-V, SPARC, PowerPC

### analogy

- isa of a cpu lets the programmer know the required informtion to control the hardware by writing a program
- isa of a car 

### microarchitecture

- diagrams that describes the interconnections of the microarchitectureal elements
- implementation of the isa
- x86-64 ISA implemented by Intel and AMD have different microarchitecture

<p><a href="https://commons.wikimedia.org/wiki/File:Intel_Core2_arch.svg#/media/File:Intel_Core2_arch.svg"><img src="https://upload.wikimedia.org/wikipedia/commons/6/60/Intel_Core2_arch.svg" alt="Intel Core2 arch.svg" height="818" width="652"></a><br>By I, <a href="//commons.wikimedia.org/wiki/User:Appaloosa" title="User:Appaloosa">Appaloosa</a>, <a href="http://creativecommons.org/licenses/by-sa/3.0/" title="Creative Commons Attribution-Share Alike 3.0">CC BY-SA 3.0</a>, <a href="https://commons.wikimedia.org/w/index.php?curid=2541872">Link</a></p>

### embedded system development platform

- when you want to program an embedded system, you first write the application program (in C) on a host machine.

- the host machine has a compiler that generates the machine code

- this machine code will only run on this specific device or other devices twith the same arch

```txt

host machine (x86)  ->  compiler  ->  machine code  ->  microcontroller (ARM)  ->  run

host machine

application
sw tools

```
- due to the limited resource of the target, host machine usually contains our build enviroment

```txt
    
host machine

code    ->  compiler toolchain           ->  executable
 c          gcc (gnu compiler collection)    binary file

```

### compiler toolchain

- compiler toolchain is a set of tools that are used to compile the source code into machine code

```

[*.c/*.h] -> preprocessor -> [*.i] -> compiler -> [*.s] -> assembler -> [*.o] -> linker -> [executable]

```

### preprocessing

- preprocessors enables the inclusion of header files, macro expansions etc.
- sometimes it is a separate program invoked by the compiler as the first part of translation
- what happens in preprocessing:
    - removal of comments
    - expansion of macros
    - expanion of the included header files

### example of preprocessing step

### compilation

- takes the preprocessed file as input, compiles it and produces an intermediate compiled output

- the output file for this stage produces machine dependent assembly code

- invoked by -S flag

```bash
gcc -S helloworld.i -o helloworld.s
```

### assembly

- converts assembly code into object code (binary file unreadable by textexitor
- object code is a portion of machine code that hasn't yet been linked into a complete program
- assemler leaves the addresses of the external functions (if any) undefined, to be filled in later by the linker
- after the linking is done, we get an executable file that can be executed on the CPU

c-code --- gcc -S ---> assembly code --- gcc -c ---> binary

**c-code**
```c
int main() {
    int x, y, z;
    y = 5;
    y = 2;
    z = x + y;
    return(0);
}
```

**assembly code**
```asm
0:  addi    sp,sp,-32
4:  sd      s0, 24(sp)
8:  addi    s0,sp,32
c:  li      a5, 5
```
