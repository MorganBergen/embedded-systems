# programs in embedded c
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
12. [input and output](#input-and-output)
13. [exercises at the end](#exercises-at-the-end)
14. [notes](#notes)

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

## operators

operators are used to perform operations on variables and values.  the most common operators are listed below:

| operators |       name        |   example   |     description                 |
|---------:|:-----------------|-----------:|:-------------------------------|
| `+`      | addition          | `x + y`     | adds two values together        |
| `-`      | subtraction       | `x  - y`    | subtracts two values            |
| `*`      | multiplication    | `x  * y`    | multiplies two values           |
| `/`      | division          | `x  / y`    | divides two values              |
| `%`      | modulus           | `x  % y`    | returns the division remainder  |
| `++`     | increment         | `++ x`      | increases the value by 1        |
| `--`     | decrement         | `-- x`      | decreases the value by 1        |
| `=`      | assignment        | `x = 5`     | assigns a value to a variable   |
| `==`     | comparison        | `x == y`    | checks if the values are equal  |
| `!=`     | not equal         | `x != y`    | checks if the values are not equal |
| `>`      | greater than      | `x > y`     | checks if the value of x is greater than the value of y |
| `<`      | less than         | `x < y`     | checks if the value of x is less than the value of y |
| `>=`     | greater than or equal to | `x >= y` | checks if the value of x is greater than or equal to the value of y |
| `<=`     | less than or equal to | `x <= y` | checks if the value of x is less than or equal to the value of y |
|`&&`      | logical and       | `x < 5 && x < 10` | returns true if both statements are true |
|`\|\|`    | logical or        | `x < 5 \|\| x < 4` | returns true if one of the statements is true |
|`!`       | logical not       | `!(x < 5 && x < 10)` | returns the result, returns false if the result is true |
|`&`       | bitwise and       | `(a & b) = 100`, a: 110, b:101 | copies a bit to the result if it exists in both operands |
|`\|`      | bitwise or        | `(a \| b) = 111`, a: 110, b:101 | copies a bit if it exists in either operand |
|`~`       | bitwise not       | `(~a) = 001`, a: 110 | binary not operator that complement each bit of the operand |
|`<<`      | bitwise left shift| `a << 2 = 100`, a: 110 | the left operands value is moved left by the number of buts specified by the right of the operand
|`>>`      | bitwise right shift | `a >> 2 = 001`, a: 110 | the left operands value is moved right by the number of bits specified by the right operand
|`&`       | address operator  | `&a` (if a is a variable)| returns the address of a variable |
|`sizeof()`| size operator     | `sizeof(a)` | returns the size of a variable |
|`*`       | pointer operator  | `*a` (if a is a pointer)| returns the value of the variable where the pointer points |

## conditionals

the control-flow statements of a language specify the order in which computations are performed.

- an expression such as `x = 0` or `i++` or `printf(...)` becomes a statement when it is followed by a semicolon
- in c the semicolon is a statement terminator, rather than a separator as it is in languages like pascal
- braces `{` and `}` are used to group declarations and statements together into a __compound statement__ or commonly refered to as a __block__
 so that they're syntactically equivalent to a single statement.
- the braces that surround the statements of a function or one example; and braces around multiple statements after an `if`, `else`, `while`, or `for` are another example
- braces essentially define scopes

### `if-else`

the `if-else` statemnet is ued to express decisions.  the syntax is as follows:

```c
if (expression) {
    // statements
} else {
    // statements
}
```
- else is always optional
- the _expression_ is evaluated if it is true meaning it's not zero then the statements inside the if block are executed
- `if` simply tests the numeric value of an expression, certain shortcuts are possible

```c
if (expression) {
    // statements
}
// instead of 
if (expression != 0) {
    // statements
}
```
- ambiguity us pernicious in situations like this
- the indentation shows unequivocally what you want, but the compiler doesn't get the message, and associates the e l s e with the inner i f . This kind of bug can be hard to find; it's a good idea to use braces when there are nested ifs.

```c
if (n >= 0) 
    for (i = 0; i < n; i++)
        if (s[i] > 0)
            printf("%d\n", s[i]);
            return(i);
        }
else
    printf("error -- n is negative\n");
```

## loops

## arrays

## strings

## memory locations

## pointers

## functions

## input and output

0.  `scanf()`

`scanf()` is equivalent to `std::cin` whereby the only way to initialize a pre-existing variable is via a pass by reference into the function

**input and output facilities are not part of the c language itself, but they are provided in the standard library**

- programs that interact with their enviroment in much more complicated ways than the simple calculations in the examples above
- the standard library is a set of functions that provide input and output, string handling, storage management, mathematical routine, and a variety of other services for c programs
- the ANSI (American National Standards Institute) standard library is defined in the header file `stdio.h` and defines these library functions precisely so that they can exist in compatible form on any system where c exists
- programs that confine their system interactions ot facilities provided by the standard library can be moved from one to another without change

1.  `int getchar(void)`

- the library implements a simple model of text input and output
- a text stream consists of a sequence of lines; each line ends with a newline character `\n` 
- if a system doesn't operate that way the library might convert things like carriage return and linefeed to newline on input and back again on output
- the simplest input mechanism is to read one character at a time from the _standard input_, normally the keyboard with `getchar:` `int getchar(void)`
- `getchar` returns the next input character each time it's called or EOF when it encounters the end of a file
- the symbolic constant `EOF` is defined in `stdio.h`
- the value is -1, which is the same as the value of the expression `EOF == -1`
- however tests should be written in terms of EOF so as to be independent of the specific value 

2.  `prog < infile`

- in many enviroments a file may be substituted for the keyboard by using the `<` convention for input redirection: if a program `prog` uses `getchar`, then the command line: `prog < infile` causes prog to read characters from `infile` instead.  the switching of the input is done in such a way that `prog` itself is obligious to the change; in particular, the string `<infile` is not included in the command line arguments in `argv`

```c
int main(int argc, char *argv[]); // argv does not contain < infile within it
```

3.  `otherprog | prog`

- the `|` convention for output redirection causes the output of one program to be used as the input of another
- input switching is invisible if the input comes from another program via the piping mechanism
- in this cause the command line runs the two programs `otherprog` and `prog` and pipes the standard output of `otherprog` into the standard input for `prog`.

4.  `int putchar(int)`

- is used for output: `putchar(c)` puts the character `c` on the _standard output_ normally the screen.
- `putchar` returns the character it prints or EOF if it encounters an error
- output can usually be directed to a file with the `>` convention for output redirection: if `prog` uses `putchar` `prog > outfile` will write the standard output to `outfile` instead. and if pipping is supported `prog | anotherprog` puts the standard output of `prog` into the standard input of `anotherprog`.

5.  `int printf(const char *format, ...)`

- output produced by `prinf()` also finds its way to the standard output. 
- calls to `putchar` and `printf` may be interleaved - output appears in the order in which the calls were made


## exercises at the end

1.  write a program that will work as a basic calculator that can perform, addition, subtraction, multiplication, and division on a user input data for two operands.  something like `5 -> + -> 6` user input will print result `sum of 5 and 6 is 11`

2.  write a c program to accept the height of a person in centimeters and categorize the person according to their height whether the person is tall/medium/short

3.  write a c program to print all the prime numbers within a limit set by a user input

4.  write a c program to create a converter from Binary to Hexadecimal and vice-versa

5.  write a program in c to count a total number of duplicate elements in an array

6.  write a program in c to calculate the length of the string using a pointer

7.  extend the assignmemt 1 by including `math.h` header file in your program and add the following functionalities to your calculator by utilizing the built-in functions of `math.h`:  square root, ceiling, floor and power.  also, create your own function for custom math operation that returns $(a + b)^2$ if `(a + b)^2` given as user input.

## notes

1.  compilation

`gcc -o a main.c`
