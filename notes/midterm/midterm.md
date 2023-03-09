# midterm exam

1.  how much should you increment the pc after fetch stage in a processor that is a word addressable (1 word = 32 bits) and the width of each instruction is 4 bytes?

1

10.  mark the multiplications that can be perfromed using logical left shift?  assume `z = 00000111` in binary 

a.  $x \times 9$
b.  $z \times 16$
c.  $z \times 32$
d.  $z \times 64$

11.  which of the following statements (if any) are true for the code used in the lab below

```c
#include <stdint.h>
#include "eecs388_lib.h"

int main() {

    int gpio = GREEN_LED;
    gpio_mode(gpio, OUTPUT);

    while(1) {
        gpio_write(gpio, ON)
        delay(1000);
        gpio_write(gpio, OFF);
        delay(300);
    }
}
```

a.  the while(1){...} loop iterates just once
b.  the `gpio_write()` in line 11 is a function declaration
- c.  we may not need such while loop if the operating system is present
d.  the `eecs388_lib.h` contains the definition of function `gpio_write()`


16.  for the following assembly program, what is the content in memory address 100 after executing the following code?  all numbers are decimal.  please note that register r0 contains zero.  all instructions are based on mips isa.

```assembly
addi    r1, r0, 54      # r1 = 0 + 54 
addi    r2, r0, 58      # r2 = 0 + 58
addi    r3, r0, 100     # r3 = 0 + 100
sw      r1, 0(r3)       # r1 = 0 + 100 
sw      r2, 4(r3)       # r2 = 4 + 104
```
```
rs [54]  ---> 
rs [58]  ---> 
r3 [100] --->
```

a.  54
b.  112
c.  54, 112
d.  100, 104

