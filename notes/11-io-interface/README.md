# i/o interace

**contents**

1.  [FE310-G002 datapath](#fe310-g002-datapath)
2.  [how does cpu talk to devices](#how-does-cpu-talk-to-devices)
3.  [memory mapped i/o](#memory-mapped-io)
4.  [memory map of sifivefe310](#memory-map-of-sifive310)
5.  [general purpose i/o gpio](#general-purpose-io-gpio)
6.  [example turn on an led](#example-turn-on-an-led)

[volatile in c](#volatile-in-c)
[transfer types](#transfer-types)
[synchronous vs. asynchronous](#synchronous-vs-asynchronous)


## volatile in c

-  when we use `volatile`, the compiler generates code to re-load the variable item each time it is referenced in your program
-  without `volatile` the compiler may generate code that merely reuses  the value it already loaded into the register

```c
void ser_write(char c) {
    
    uint32_t regval;

    do {
        
        regval = *(volatile uint32_t *)(UART_CTRL_ADDR + UART_TXDATA);
    
    } while (regval & 0x80000000);

    *(volatile uint32_t *)(UART_CTRL_ADDR + UART_TXDATA) = c;
}
```

**`unit32_t`**

```assembly
ser_write:
        li      a5, 268513280
        lw      a5, 0(a5)
.L17:
        bltz    a5, .L17
        li      a5, 268513280
        sw      a0, 0(a5)
```

**`volatile uint32_t`**

```assembly
ser_write:
        li      a4, 268513280   # a4 = 0x10013000
.L17:
        lw      a5, 0(a4)       # a5 = *a4
        bltz    a5,.L17         # branch to .L17 if a5 < zero
        sw      a0, 0(a4)
        ret     
```

when used `volatile` the `lw` happens inside the loop everytime
