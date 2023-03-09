# quiz 3

1.  for the following assembly program, how many times the addi instruction inside the loop will execute?  all instructions are based on 32 bits MIPS ISA.

```assembly
addi r1, r0, 4
Loop:
addi r1, r1, -1
bne r1, r0, Loop
sub r1, r0, r0
```

- 4

2.  for the following assembly program, what is the content in memory address 100 after executing the following code?  all umbers are decimal.  please note that register `r0` contains zero.  all instructions are based on mips isa.

```assembly
addi r1, r0, 54
addi r2, r0, 58
addi r3, r0, 100
sw r1, 0(r3)
sw r2, 4(r3)
```
