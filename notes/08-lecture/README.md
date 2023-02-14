# MIPS assembly

MIPS stands for Microprocessor without Interlocked Pipeline Stages. It is a reduced instruction set computer (RISC) instruction set architecture (ISA) developed by MIPS Technologies for its MIPS processor series. the MIPS architecture is widely used in computer systems, including workstations, servers, embedded systems, and video game consoles.

0.  what is the MIPS assembly code for the C assignment statement below?

`f = (g + h) - (i + j)`

```MIPS
add $t0, $s1, $s2   # register $t0 contains g + h
add $t1, $s3, $s4   # register $t1 contains i + j
sub $s0, $t0, $t1   # f gets $t0 - $t1, which is (g + h) - (i + j)
```

1.  what is the MIPS assembly code for the C assignment statement below?

`A[12] = h + A[8];`

- assume variable `h` is in register `$s2`
- all elements of `A` is in memory and the base address of the array `A` is in `$s3`

```
lw   $t0, 32($s3)       # temporary register 
                        # storing the value of A[8] in register $t0
add  $t0, $s2, $t0      # temporary reg $t0 gets h + A[8]
                        # adding value in register $s2 with $t0 and sending it to $t0
sw   $t0, 48($s3)       # storing the value of $t0 in A[12]
```

- although there is a single operation in the C statemnet, now two of the operands are in memory
- so we need even more MIPS instructions
- the first two instructions are the same as the prior example, except this time we use the proper offset for byte addressing in the load word instruction to select A[8]
- and the add instruction places the sum in `$t0`

3.  `add $t0, $s1, $s2`

```
|____0  hex____| |____11 hex____| |____12 hex____| |____00000____||____20 hex___|
     6  bits          5  bits          5  bits          5  bits        6  bits
     opt code         rs               rt               rd             funct
|_31________26_|
```

- opcode = `add`
- `rs = s1 = 17_{10} = 11_{16}`
- `rt = s2 = 18_{10} = 12_{16}`
- `rd = t0 = 8_{10} = 8_{16}`

```
add $t0, $s1, $s2
name    mnemonic    format      operation
add     add         R           R[rd] = R[rs] + R[rt]
```

4.  converting the following instruction to hex using MIPS reference sheet

`lw $t0, 1200($t1)`

- opcode = `lw`
- `rs = t1 = 9_{10} = 9_{16}`
- `rt = t0 = 8_{10} = 8_{16}`
- `lw = 23_10 = 17_{16}`


```
I  |31-opcode-26||25-rs-21||20-rt-16||15-immediate-0|
   | 17 hex     || 9 hex  || 8 hex  || 4B0 hex      |
```






