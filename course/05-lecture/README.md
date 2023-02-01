# isa & microarchitecture

**instruction set architecture**

morgan bergen
jan 31 2023


## abstractions from software to silicon

## the software stack

**high-level language program in c**

**assembly language program for mips**
```c
$ indicate different registers
lw means load word
```

## motivation to learn isa

- insturctions are worcs used to command computer hardware
- the collection of these words, or the vocabulary is called "instruction set"
- why we need to understand this vocabulary?

- without instruction set, the design and functionality of architecture cannot be understoon
- provides ability to examine code at lower level of abstrcations an solve bugs/ecurity issues

## topics

## mips isa

## classes of instructions in mips

## opcode and operands

- opcode:  operation that is executed by the cpu
- operand:  data or memory location used to execute that operation

| category | instruction | example | meaning | comments
| --- | --- | --- | --- | --- |
| arithmetic | add | add $t0, $t1, $t2 | $t0 = $t1 + $t2 | always three operands|
| arithmetic | subtract | sub a, b, c | a = b - c | always three operands|

- the destination operand always goes first

## simpliefied model of computer architecture

[the von neumann computer model](https://en.wikipedia.org/wiki/Von_Neumann_architecture)

## registers

- limited number of memory location connected to ALU
- MIPS32 has 32 registers (therre is a MIPS64 also)
    - each of the 32 registers has capacity to hold 32 bits (also known as a word)
    - when we say MIPS in this class we assume the MIPS32

## register naming

## register naming in MIPS

- $zero:  always holds the value 0
- saved information
- global pointer
- stack pointer
- all are physical registers in our mips32

## memory

- your program can have large number of variable and complex data types
    - ex:  arrays with 100 elements
- 32 or 64 registers are not sufficient
- we need to use a large memory space to store this data
- but we cannot perform arithmetic operations directly from memory
- loading brinsg data to the register from the memory
- storing brings data from the register to the memory

the difference is that there is one source operand and one destination operand

## complexities with memory

- your program can have a large number of variables and complex data types
    - ex:  arrays with 100 elements


## memory organization

## instructions:  load and store

```c
g = h + A[7];
```

```MIPS
lw  $t0, 28($s1) // the address you want to bring from A[7] to register s1
add $t0, $s2, $t0 // add the value of h to the value of A[7]
sw  $t0, 48($s1) // store the value of g in the memory
```

## practice

example 

```c
A[10] = y + A[11];
```
```MIPS
lw  $t0 44($s1)
add $t0, $t0, $s2
sw $t0, 40($s1)
```

register `$s1` has the base address of array `A`

```MIPS
// load word from register t0 to 44 s1
lw  $t0 44($s1)
// add the value of y to the value of A[11]
add $t0, $t0, $s2
// sw $source_register $destination_memory_address
// t0 is what we want to send
// since its A[10] 40 is the location
// s1 is the destination address
sw  $t0, 40($s1)
```
