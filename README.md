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

There is no limit it to the number of commands you can chain. You can also use ( ) to group commands together. For
example:  
> $ echo a && echo b || echo c && echo d  
will print  
> $ a  
> $ b  
> $ d  
but  
> $ (echo a && echo b) || (echo c && echo d)  
will print   
> $ a  
> $ b  

To compile use these commands:

> $ git clone https://github.com/bgutz001/rshell.git   

> $ cd rshell  

> $ git checkout hw1    

> $ make    

> $ ./bin/rshell

To test if a file exists use the form:  
> cmd = test [ arg ] [ path to file ]   
The availiabe arguments are -e to test if the file exists, -d to test if its a directory, and -f to see if its a normal
file. Also, you can use the form:    
> cmd = [ [ arg ] [ path to file ] ]     
Note that you must actually type the outer most [ ]. For example:    
> [ -e /bin ]    


**Known Bugs**

1. If you want to print out special characters such as && || ; [ ] or ( ) make sure you use " " around the whole echo
statment or else things will break


**Design**

tokenClass.cpp handles parsing the string the user inputs into commands. main.cpp handles connectors and executes
commands. If you want to make changes to the program then add or change functions in those files accordingly.
