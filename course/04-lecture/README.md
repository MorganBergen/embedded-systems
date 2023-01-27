# lecture 04

**content**

1.  [context](#context)
2.  [representing signed numbers](#representing-signed-numbers)
3.  [questions](#questions)
4.  [fractional numbers: float and double](#fractional-numbers-float-and-double)
5.  [operators](#operators)
6.  [arithmetic operators](#arithmetic-operators)
7.  [increment and decrement ++, --](#increment-and-decrement---)
8.  [example](#example)
9.  [relational operators](#relational-operators)
10. [example](#example-1)
11. [logical operators](#logical-operators)
12. [example](#example-2)
13. [bitwise operators](#bitwise-operators)
14. [difference between logical vs bitwise operations](#difference-between-logical-vs-bitwise-operations)
15. [bitwise vs logical AND/OR](#bitwise-vs-logical-andor)
16. [assignment operators](#assignment-operators)
17. [bitwise operators](#bitwise-operators-1)
18. [left shift](#left-shift)
19. [right shift](#right-shift)
20. [flow control statements: branching](#flow-control-statements-branching)
21. [branching using switch statement](#branching-using-switch-statement)
22. [flow control statements: looping](#flow-control-statements-looping)
23. [while and do while loops](#while-and-do-while-loops)
24. [use of while/do-while in embedded programming](#use-of-whiledo-while-in-embedded-programming)
25. [break and continue](#break-and-continue)
26. [functions in c](#functions-in-c)
27. [defining a function](#defining-a-function)
28. [function declaration](#function-declaration)
29. [calling a function](#calling-a-function)
30. [using header files for function](#using-header-files-for-function)
32. [example](#example-3)

## context

## representing signed numbers

## questions

- subtract 8 from 9 in 2s complement negation method (without doing subtraction)
- assume we have 8-bit digits (not 32 bits), ignore carry beyond 8 bits

```
- 9_(10) = 00001001_(2)
- 8_(10) = 00001000_(2)

step 1:  -8_(10) = 11111000_(2)
step 2:  9 + (-8) = 00000001_(2) = 1_(10)

  00001001_(2)
+ 11111000_(2) 
---------------
 00000001_(2) = 1_(10)
```

## fractional numbers: float and double

## operators

## arithmetic operators

## increment and decrement ++, --

- var++ prefix increment
- ++var postfix increment

```
a = 1; b = 2; c = 3;
x = a-- + b++ - ++c; // x = 1 + 2 - 4
x -> -1
```

## example

```c
int main() {
    int var1 = 100;
    printf("%d\n", var1++); // 100
    printf("%d\n", ++var1); // 102
    printf("%d\n", var1--); // 102
    printf("%d\n", --var1); // 101
    return(0);
}
```

## relational operators

- checks the relationship between two operands
- c uses its int type to represent true and false
- if the relation is true, a relational operation returns 1;
- if the relation is false, a relational operation returns 0;

```
<   less than
<=  less than or equal to
>   greater than
>=  greater than or equal to
==  equal to
!=  not equal to
```
```cpp
if (a > b) {
    printf("a is greater than b\n");
} else {
    printf("a is not greater than b\n");
}
```
## example

```c
int a = 21;
int b = 10;

if (a == b) {
    printf("Line 1 - a is equal to b\n");
} else {
    printf("Line 1 - a is not equal to b\n");
}

printf(" %d", a > b);
printf(" %d", a < b);
```

## logical operators

- commonly used in conditional expression in c programming 
    - `if (condition1 && condition2) { ... }`
    - `if (condition1 || condition2) { ... }`
    - `if (!condition1) { ... }`

- logical operation returns either 0 or 1 (true or false)

```
&&  logical AND
||  logical OR
!   logical NOT
```

## example

- if the result of the logical operator is true then 1 is returned otherwise 0 is returned

```c
int a = 5, b = 5, c = 10;

if ((a == b) && (c > b)) {
    printf("Line 1 - Condition is true\n");
} else if ((a == b) && (c < b)) {
    printf("Line 1 - Condition is false\n");
} else if ((a == b) || !(c < b)) {
    printf("Line 2 - Condition is true\n");
} else {
    printf("Line 2 - Condition is false\n");
}
```

## bitwise operators

- used for manipulating bits and performing bit-by-bit operations
- operates on `int` type data (including short, long, unsigned) and return int data types as well

```
|   bitwise OR              10011011 | 01101100 = 11111111
&   bitwise AND             10011011 & 01101100 = 00001000
^   bitwise XOR             10011011 ^ 01101100 = 11110111
~   bitwise ones complement ~10011011 = 01100100
<<  left shift              10011011 << 2 = 00101100
>>  right shift             10011011 >> 2 = 00101100
```

## difference between logical vs bitwise operations

- logical use case:  constructing complex conditional expressions
- example:  `if (cond0 || cond1){ ... }`
- return type: `0` or `1`
- sign:  ||, &&, !

- bitwise use case:  manipulating bits bit by bit
- example: ` 1011 | 1100 = 0111`
- return type:  `int` type data (including `short`, `long`, `unsigned`)
- sign:  `|`, `&`, `^`, `~`, `<<`, `>>`

## bitwise vs logical AND/OR

operand1 = 0b1000
operand2 = 0b1100

(operand1 && operand2) = 0b1000
(operand1 & operand2) = 0b1000

## assignment operators

- arithmetic and bitwise operators can be combined with an assignment for simplicity

`var0 += var1` is equivalent to `var0 = var0 + var1`

`var0 >>= 5` is equivalent to `var0 = var0 >> 5`

## bitwise operators

- << left shift
    - `c = a << 2` shift left by 2 bits
- >> right shift
    - `c = a >> 2` shift right by 2 bits
- application of bitwise shoft:  cryptographic algorithms, multiplication and division, encoding and decoding etc.

## left shift

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/5/5c/Rotate_left_logically.svg/1200px-Rotate_left_logically.svg.png" style="width:200px" >

## right shift

- the result of right shift operation is a **division** by 2^n, where n is the number of shifted bit position
    - applies for unsigned number
    - ignores the remainder

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/5/5c/Rotate_left_logically.svg/1200px-Rotate_left_logically.svg.png" style="width:200px">

| x | syntax | binary | decimal | hint |
|---|--------|--------|---------|------|
| example 0 | x = 7 | 0111 | 7 | |
| example 1 | y = x >> 1 | 0011 | 3 | 7/2 = 3.5, ignore the remainder |
| example 2 | z = x << 2 | 0001 | 1 | 7/4 = 1.75, ignore the remainder |
| example 3 | i = x << 4 | 0000 | 0 | 7/16 = 0.45, ignore the remainder |

## flow control statement:  branching

- two main component
    - an expression in parenthesis 
    - a statement or block of statement

- if the expression is true
    - then the statement or block of statements gets executed
    - otherwize, these statements are skipped

```c
if (condition) {
    // statement
} else if (condition) {
    // statement
} else {
    // statement
}
```

## switch statement

```c

int main() {
    // local variable definition
    char grade = 'B';

    switch(grade) {
        case 'A' :
            printf("Excellent!\n" );
            break;
        case 'B' :
        case 'C' :
            printf("Well done\n" );
            break;
        case 'D' :
            printf("You passed\n" );
            break;
        case 'F' :
            printf("Better try again\n" );
            break;
        default :
            printf("Invalid grade\n" );
    }
```
> above average

## while loop

- loops provide a way to repeatedly execute a statement or a block of statements
    - provides control on how many times to loop

- c provides a number of ways
    - `while`
    - `do while`
    - `for`

```c

int main() {
    // local variable definition
    int a = 10;

    // while loop execution
    while( a < 20 ) {
        printf("value of a: %d\n", a);
        a++;
    }
```

## do while loop

a do while loop is similar to a while loop except that it tests the condition at the end of the loop body

```c
int main() {
    // local variable definition
    int a = 10;

    // do loop execution
    do {
        printf("value of a: %d\n", a);
        a = a + 1;
    } while( a < 20 );
```

## use of while/do-while in embedded programming

- general purpose computers have operating systems
- the os waits for your instructions to run the desired programs
- many embedded systems do not have os
- programs written for such systems need infinite lopp that constantly waits for user input
    - otherwise, the program will just run once and exit
- such infinite loop can be designed using `while (always true) { ... }` or `do { ... } while (always true);`


```c
while(1) {
    gp
