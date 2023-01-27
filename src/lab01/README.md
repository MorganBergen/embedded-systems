# lab1
## embedded systems

**morgan bergen**
**jan 26 2023**
**exercises at the end**

**contents**

1.  [objective](#objective)
2.  [basic c program structure](#basic-c-program-structure)
3.  [variables, data types, and constants](#variables-data-types-and-constants)
4.  [operators](#operators)
5.  [conditionals](#conditionals)
6.  [loops](#loops)
7.  [arrays](#arrays)
8.  [strings](#strings)
9.  [memory locations](#memory-locations)
10. [pointers](#pointers)
11. [functions](#functions)
12. [exercises at the end](#exercises-at-the-end)
13. [notes](#notes)

## objective

in this lab we will go over some essential topics of c programming which are required to know during our embedded systems lab on the following weeks.  we will use an online compiler for practicing and writing all the programs we learn today.  [here](https://www.onlinegdb.com/online_c_compiler) to access the online c compiler.  first, we will understand the listed c programming topics below and practice the.  after that try to solve the assignment problems.  once you're finished, demonstrate the programs to your ta and turn in the programs in canvas.

## basic c program structure

```c
#include <stdio.h>
    int main() {
        printf("hello world");
        return 0;
}
```

## variables, data types, and constants

variables are containers for storing data values, like numbers and characters.  the data type specifies the size and type of information the variable will store.  basic data types include: char, int, long, float, double, void, and unsigned version of each of them.  

syntax:  `type variablename = value;`

examples:

1.  declare a variable without assigning the value and assign the value letter

```c
// declare a variable
int mynum;
// assign a value to the variable
mynum = 5;
```

2.  printing any string/character/variable

```c
int mynum = 15;
char myletter = 'd';
printf("my number is %d and my letter is %c", mynum, myletter);
```

- 

## operators

## conditionals

## loops

## arrays

## strings

## memory locations

## pointers

## functions

## exercises at the end

1.  write a program that will work as a basic calculator that can perform, addition, subtraction, multiplication, and division on a user input data for two operands.  something like `5 -> + -> 6` user input will print result `sum of 5 and 6 is 11`

2.  write a c program to accept the height of a person in celtimeter and categorize the person according to their height whether the person is tall/medium/short

3.  write a c program to print all the prime numbers within a limit set by a user input

4.  write a c program to create a converter from Binary to Hexadecimal and vice-versa

5.  write a program in c to count a total number of duplicate elements in an array

6.  write a program in c to calculate the length of the string using a pointer

7.  extend the assignmemt 1 by including `math.h` header file in your program and add the following functionalities to your calculator by utilizing the built-in functions of `math.h`:  square root, ceiling, floor and power.  also, create your own function for custom math operation that returns $(a + b)^2$ if `(a + b)^2` given as user input.

## notes

1.  compilation

`gcc -o a main.c`
