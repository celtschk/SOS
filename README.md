# SOS
A purely stack based esoteric programming language

## Table of contents

  * [Introduction](#introduction)
  * [Repository overview](#repository-overview)
  * [The language](#the-language)
    * [Basic concepts](#basic-concepts)
    * [Commands](#commands)
      * [Stack navigation](#stack-navigation)
      * [Stack manipulation](#stack-manipulation)
      * [Flow control](#flow-control)
      * [Input/Output](#inputoutput)
    * [Example programs](#example-programs)
      * [Hello world](#hello-world)
      * [copy input to output (cat)](#copy-input-to-output-cat)
      * [Binary complement](#binary-complement)
  * [The interpreter](#the-interpreter)
  * [The example programs](#the-example-programs)

## Introduction

SOS is a purely stack-based esoteric programming language. The name SOS is short for Stack Of Stacks, or it is your reaction if you need to read or write code in this language.

Being purely stack based here means that the only data structure the language has is the stack. The items on the stack are then, of course, also stacks, hence the name.

As the language allows to implement the logical operations `and` and `not` as well the control structures if/else and while, it is Turing complete.

## Repository overview

This repository contains the following items:

  * The language specification (part of README.md, this file).
  * An interpreter for the language, in the directory `interpreter`.
  * Example programs in the language, in the directory `examples`.

## The language

### Basic concepts

An SOS program consists of a string of characters, where each character describes a single command. Except for loops, which are enclodes in parentheses (see below for details), the commands are executed from left to right. Whitespace characters, letters, digits, the comma and the period/full stop are ignored. An implementation may or may not ignore other non-command characters.

Each command has a precondition and an action. If the precondition is not met, the current loop is exited, that is, execution continues after the corresponding closing parenthesis. Note that failing to meet a precondition is the only way to exit a loop. If not currently in a loop, the program is terminated instead. The program also terminates on reaching the end of the code.

The only data structure of the program is the stack of stacks. There are two stacks that are special:

  * The root stack. This is the only stack that is not on another stack. Every other stack is directly on that stack, or on some stack that is itself directly or indirectly on the root stack.
  * The current stack. This is the stack on which commands act. The current stack may be changed by entering or leaving a stack.

At the beginning of the program, the current stack is the root stack, which is empty.

### Commands

#### Stack navigation

  * `>`: Enter

    **Precondition:** The current stack is not empty.

    **Effect:** Makes the stack on the top of the current stack the new current stack.
    
  * `<`: Leave

    **Precondition:** The current stack is not the root stack.

    **Effect:** Makes the parent stack of the current stack the new current stack.
    
#### Stack manipulation

  * `+`: Create

    **Precondition:** None.

    **Effect:** Pushes a new empty stack on top of the current stack.

  * `-`: Destroy

    **Precondition:** The current stack is not empty.

    **Effect:** Removes the stack on the top of the current stack. Any content of that stack is lost.

  * `^`: Push

    **Precondition:** The current stack contains at least two stacks.

    **Effect:** The top of the current stack is pushed onto the stack below, and removed from the current stack.
    
  * `_`: Pop

    **Precondition:** The current stack is not empty, nor is the stack at the top of the current stack.

    **Effect:** The top of the top is popped from the top of the current stack, and pushed onto the current stack.
 
  * `=`: Duplicate

    **Precondition:** The stack is not empty.
    
    **Effect:** Duplicates the top element of the current stack,
 
  * `%`: Exchange

    **Precondition:** The current stack contains at least two stacks.

    **Effect:** Exchanges the top two stacks on the current stack

  * `{`: Rotate left

    **Precondition:** None.

    **Effect:** Rotates the current stack one position to the left, that is, it moves the bommon element to the top. If the current stack has less than two elements, this has no effect.

  * `}`: Rotate right

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

  * `!`: Write a single bit to standard output

    **Precondition:** None.

    **Effect:** If the current stack is empty, write a zero bit, otherwise write a one bit.

    Bytes are written from the most significant bit to the least significant bit. If at the end of the program an incomplete byte has been output, it is padded with zeros from the *left.* Thus a program that only produces the bits `1010` outputs a single byte of value 10, or a line feed character if interpreted as ASCII.

### Example programs

#### Hello world

This program just prints "Hello world" on a line by itself, with LF as line terminator (i.e. Unix style)
```
!+!-!!+!-!!!!+!!-!!+!-!+!-!+!!-!+!!-!!!+!!-!+!!-!!!+!!-!+!!!!-!!+!-!!!!!!+!!!-!+!!!-!+!!-!+!!!!-!+!!!-!!+!-!!+!!-!+!!-!!!+!!-!!+!-!!+!-!+!-!
```
Or in *slightly* more readable form (all the text is ignored by the interpreter):
```
!+!-!!+!-!!!    write H
!+!!-!!+!-!+!   write e
-!+!!-!+!!-!!   write l
!+!!-!+!!-!!    write l
!+!!-!+!!!!     write o
-!!+!-!!!!!     write space
!+!!!-!+!!!     write w
-!+!!-!+!!!!    write o
-!+!!!-!!+!-!   write r
!+!!-!+!!-!!    write l
!+!!-!!+!-!!    write d
+!-!+!-!        write linefeed
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

#### Binary complement

The following outputs the binary complement of the standard input.
```
+>?<(_--)!(-))
```
Again, the whole program is a loop (with implied opening parenthesis at the beginning of the program).

At the beginning of the loop, the current stack is empty. The program pushes an empty stack, enters it, reads a bit, and leaves the stack again. This if the read bit was a zero, the stack now contains an empty stack, if the bit was 1, it contains a stack containingan empty stack. If we reached the end of file, the loop is terminated (the final stack isn't empty in that case, but that doesn't matter).

Next execution reaches `(_--)`. If the top of stack is just an empty stack, trying to pop an element (`_`) violates the precondition, and therefore immediately terminates the loop, leaving the stack unchanged. Otherwise, the top element is popped (so that now the current stack consists of two empty stack), and then the top two elements are removed (so that now the stck is empty). In the next iteration of this loop, the attempt to pop in an empty stack again violates the preconditions of pop, thus the loop now terminates with the stack empty.

The end result of this is that now the stack is empty if a one was read, and not empty if a zero was read, the opposite of what a single `?` would have resulted in. Thus the following `!` outputs the complement of the bit just read.

As in the previous program, the stack is now cleared for the next iteration of the loop.

## The interpreter

This repository includes an interpreter for the SOS programming language written in C++.

To build the interpreter, just compile all C++ souce files (`*.cc`) into a program. A CMakeLists.txt for cmake is also provided.

In the following, I'm assuming the executable can be executed with `interpreter/sos`. Otherwise, replace `interpreter/sos` with whatever path and name the executable has in your system.

The interpreter can read the program either from a file, or directly from the command line. To run a command from a file, just type
```
interpreter/sos filename
```
For example, to run the hello world example in the directory examples, use
```
interpreter/sos examples/helloworld.sos
```
To run a program directly from the command line, you can use the command line parameter `-c` followed by the program as next parameter. Make sure to properly quote that parameter so it doesn't get interpreted by the shell. For example, to run the cat example above directly from the command line, you can use
```
interpreter/sos -c "?!(-))"
```
Here the `"` are quotes for the shell, which aren't seen by the interpreter (but if they were, it wouldn't hurt anyway, as the interpreter ignores everything it doesn't know).

## The example programs

The directory `examples` contains a few example programs written in the SOS programming language. The files all have the ending `.sos`.
