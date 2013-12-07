Team Members: Sean Flinn, Kiertan Walker-Phelan, and Adam Croissant

What we've done:

Made a class hierarchy of nodes to represent an abstract syntax tree
Implement int, string, and pointer
Implemented functions and sfunctions
function calls type check to int or string depending on whether it is a function or a sfunction
maintain symbol table tracking symbols of global and local scope separately
String addition works, and addition properly type checks
type checking in operations and function calls.
nstrlen() implemented in our naught library
created a function to add two naught strings
address of and dereferencing works as expected
print prints out the expression and returns the expressions value, so you can use operators on a print statement
Checks if functions/sfunctions have previously been defined and crashes if a function/sfunction has been defined previously
Checks that a function definition or declaration meets any previous declaration's types
Throws an error if the user writes nested functions
Warns the user if they call an undefined function
Prevents a user from declaring a variable twice in the same scope
Ensure you can't get the address of a non-integer or dereference a non-pointer
Doesn't allow operations on undeclared variables


What we haven't done:

Our compiler only prints out the first error and then exits. It doesn't print out all of the errors in the file
Our syntax tree often uses AST_node (our base class) pointers instead of the actual type of nodes due to how we initially implemented it
Our compiler doesn't confirm that the return type from a function or sfunction is correct (could be implemented, but with a few modifications)
Our compiler doesn't tell you where your error arises like gcc does
Didn't put the function to add two naught strings in the naught library 
Made a makefile - to compile naught files using our project, follow this example:
     $ cpp *.n > *cpp.n (run all files through cpp)
     $ ./comp <your .n files>
     $ gcc -Wall -g -c <your .c files> string_add.c nstr_to_len.c
     $ gcc <your .o files> string_add.o nstr_to_len.o -o <program_name> -L . -lnaught
