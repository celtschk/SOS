# SOS
A purely stack based esoteric programming language

## Introduction

SOS is a purely stack-based esoteric programming language. The name SOS is short for Stack Of Stacks, or it is your reaction if you need to read or write code in this language.

Being purely stack based here means that the only data structure the language has is the stack. The items on the stack are then, of course, also stacks, hence the name.

## The language

### Basic concepts

An SOS program consists of a string of characters, where each character describes a single command. Except for loops, which are enclodes in parentheses (see below for details), the commands are executed from left to right. Whitespace characters are ignored. An implementation may or may not ignore non-whitespace non-command characters.

Each command has a precondition and an action. If the precondition is not met, the current loop is exited, that is, execution continues after the corresponding closing parenthesis. Note that failing to meet a precondition is the only way to exit a loop. If not currently in a loop, the program is terminated instead. The program also terminates on reaching the end of the code.

The only data structure of the program is the stack of stacks. There are two stacks that are special:

  * The root stack. This is the only stack that is not on another stack. Every other stack is directly on that stack, or on some stack that is itself directly or indirectly on the root stack.
  * The current stack. This is the stack on which commands act. The current stack may be changed by entering or leaving a stack.

At the beginning of the program, the current stack is the root stack, which is empty.

### Commands

#### Stack navigation

  * `>`: Enter stack.

    **Precondition:** The current stack is not empty.

    **Effect:** Makes the stack on the top of the current stack the new current stack.
    
  * `<`: Leave stack.

    **Precondition:** The current stack is not the root stack.

    **Effect:** Makes the parent stack of the current stack the new current stack.
    
#### Stack manipulation

  * `+`: Create stack.

    **Precondition:** None.

    **Effect:** Pushes a new empty stack on top of the current stack.

  * `-`: Destroy stack.

    **Precondition:** The current stack is not empty.

    **Effect:** Removes the stack on the top of the current stack. Any content of that stack is lost.

  * `^`: Push stack.

    **Precondition:** The current stack contains at least two stacks.

    **Effect:** The top of the current stack is pushed onto the stack below, and removed from the current stack.
    
  * `_`: Pop stack.

    **Precondition:** The current stack is not empty, nor is the stack at the top of the current stack.

    **Effect:** The top of the top is popped from the top of the current stack, and pushed onto the current stack.
 
  * `%`: Exchange

    **Precondition:** The current stack contains at least two stacks.

    **Effect:** Exchanges the top two stacks on the current stack

  * `{`: Rotate left

    **Precondition:** None.

    **Effect:** Rotates the current stack one position to the left, that is, it moves the bommon element to the top. If the current stack has less than two elements, this has no effect.

  * `}`: Rotate left

    **Precondition:** None.

    **Effect:** Rotates the current stack one position to the right, that is, it moves the top element to the bottom. If the current stack has less than two elements, this has no effect.

#### Flow control

  * `(`: Begin loop

    **Precondition:** None.

    **Effect:** It has no effect when executed.

  * `)`: End loop

    **Precondition:** None.

    **Effect:** Execution continues at the command after the corresponding opening parenthesis. If there is no corresponding opening parenthesis, execution continues at the beginning of the program.

#### Input/Output

  * `?`: Read a single bit from standard input.

    **Precondition:** Standard input is not at end of file.

    **Effect:** If the read bit is a zero, does not have an effect. If the read bit is a one, an empty stack is pushed on top of the current one, as if `+` had been executed.

    Bytes are read starting from the most significant bit to the least significant bit.

  * `!`: Wite a bit to standard output

    **Precondition:** None.

    **Effect:** If the current stack is empty, write a zero bit, otherwise write a one bit.

    Bytes are written from the most significant bit to the least significant bit. If at the end of the program an incomplete byte has been output, it is padded with zeros from the *left.* Thus the program consisting only of `1010` outputs a single byte of value 10, or a line feed character if interpreted as ASCII.

### Example programs

#### Hello world

This program just prints "Hello world" on a line by itself, with LF as line terminator (i.e. Unix style)
```
!+!-!!+!-!!!!+!!-!!+!-!+!-!+!!-!+!!-!!!+!!-!+!-!!!!+!!-!+!!!!-!!+!-!!!!!!+!!!-!+!!!-!+!!-!+!!!!-!+!!-!+!!-!+!-!+!!-!+!!-!!!+!!-!!+!-!!+!-!+!-!
```
This just puts out the bits of "Hello world" in ASCII. At the beginning, the stack is empty, thus for each `!` a 0 is output. To switch to 1, something (namely an empty stack) is put on the current (root) stack using `+`. Since now the stack is no longer empty, `!` now outputs 1 bits. To output 0 bits again, that stack content is removed with `-`.

In total, the binary output of this code therefore reads (with spaces added for better comprehension):
```
01001000 01100101 01101100 01101000 01101111 00100000 01110111 01101111 01101101 01101100 01100100 1010
```
Note that the final four output bits get left-padded to 8 bits with zeros, so the actual output is:
```
01001000 01100101 01101100 01101000 01101111 00100000 01110111 01101111 01101101 01101100 01100100 00001010
```
This is the ASCII representation of the string "Hello world" with a final line feed character.

#### copy input to output (cat)

The following program just copies all input unchanged to output, that is, it does the same as `cat` when used as a “filter”:
```
?!(-))
```
The whole program is a loop (as the final closing parenthesis has no matching opening parenthesis, execution goes back to the beginning, just as if there were an opening parenthesis in front of the program).

At the beginning of the loop, a bit is read. If standard input is at EOF, the precondition of `?` is not met, and therefore the loop (and thus the program) ends. Otherwise, if a zero bit is read, the stack is left empty, while if a one bit is read, an empty stack is pushed on the current stack (which therefore is no longer empty).

The following `!` outputs a zero if the current stack is empty (that is, a zero was read), and a one otherwise (i.e. a one was read).

Finally, the `(-)` is a loop that emtpties the stack for the next iteration, by removing anything on the stack (`-`) until the stack is empty (the precondion of `-` is not met, thus the loop terminates).
