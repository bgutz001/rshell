# Rshell - A basic implementation of a shell 

Brandon Gutzmann  

Nicholas Rogers   

This projected was created for CS100 class at UCR

**Functionality**

Commands will have the form:
> cmd = executable [ argumentList ] [ connector cmd ]
connector = || or && or ;

Where executable is an executable program in the PATH and argumentList is a list of zero
or more arguments separated by spaces. The connector is an optional way you can run multiple
commands at once. If a command is followed by ;, then the next command is always executed;
if a command is followed by &&, then the next command is executed only if the first one
succeeds; if a command is followed by ||, then the next command is executed only if the first
one fails. For example:

> $ ls -a  

> $ echo hello   

> $ mkdir test

is equivalent to:

> $ ls -a; echo hello; mkdir test

There is no limit it to the number of commands you can chain.

To compile use these commands:

> $ git clone https://github.com/bgutz001/rshell.git   

> $ cd rshell  

> $ git checkout hw    

> $ make    

> $ bin/rshell

**Known Bugs**

1. Echo with "" doesn't work. Can't echo opertators like || && ; 
