# SimASM
simulator that follows the ISA defined next. It is written in C++ and may use the Qt framework for the GUI.
### ISA
#### Registers
The ISA has 4 general purpose registers, R0, R1, R2, and R3.
The ISA also has a program counter register.
#### Stack
The ISA has a stack that is 4096 bytes in size. The stack pointer register points to the top of the stack.
#### Memory
The ISA has a shared memory to store code and data, with a variable size. direct access to memory is permitted.
#### ALU
The ALU is a 32-bit ALU that supports the following operations:
##### Comments
line comments are started with a `!` and end at the end of the line.
##### LDA - Load Address
Load register reg1 with the contents of either the contents of reg2, or the memory var or a constant
const. Memory regions loads (load into a variable, for instance) are NOT ALLOWED.
There can be indirect loads, for instance `LDA R1, R2` will load the contents of the memory address
##### STR - Store Register
Store the contents of reg or const into the memory var. 
Register regions stores (store into a Register,for instance t0) are NOT ALLOWED.
There can be indirect stores, for instance `STR R1, R2` will store the contents of R1 into the memory address
##### PUSH - Push to the top of the stack
Push the contents of reg/var or const into the top of the stack.
##### POP - Pop from the top of the stack
Pop the contents of the top of the stack into reg/var. Storing into Memory regions is NOT ALLOWED.
#### Logical Operations
The logical operations are the following:
there cannot be result stored in a memory region.
##### AND - Logical AND
Perform a Logical AND between reg1 and reg2 or const and store the result in reg1.
##### OR - Logical OR
Perform a Logical OR between reg1 and reg2 or const and store the result in reg1.
##### NOT - Logical NOT
Perform a Logical NOT on reg1 and store the result in reg1.
#### arithmetical operations
The arithmetical operations are the following:
there cannot be result stored in a memory region.
##### ADD - Addition
Perform an addition between reg1 and reg2/var or const and store the result in reg1.
##### SUB - Subtraction
Perform a subtraction between reg1 and reg2/var or const and store the result in reg1.
##### MUL - Multiplication
Perform a multiplication between reg1 and reg2/var or const and store the result in reg1.
##### DIV - Division
Perform a division between reg1 and reg2/var or const and store the result in reg1.
##### MOD - Modulo
Perform a modulo between reg1 and reg2/var or const and store the result in reg1.
The operation is defined as first argument is the modulo of the second argument.
##### INC - Increment
Increment the contents of reg1 by 1.
##### DEC - Decrement
Decrement the contents of reg1 by 1.
#### comparison operations and jumps
##### BEQ - Branch if Equal
Branch to the label if reg1 is equal to reg2 or const.
##### BNE - Branch if Not Equal
Branch to the label if reg1 is not equal to reg2 or const.
##### BBG - Branch if Bigger
Branch to the label if reg1 is bigger than reg2 or const.
##### BSM - Branch if Smaller
Branch to the label if reg1 is smaller than reg2 or const.
##### JMP - Jump
Jump to the label.
#### Misc
##### HLT - Halt
Halt the execution of the program.
##### SRL - Shift Right Logical
Shift the contents of reg1 to the right by the amount of bits specified in reg2 or const.
##### SLL - Shift Left Logical
Shift the contents of reg1 to the left by the amount of bits specified in reg2 or const.



