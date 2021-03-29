A shell has been built to execute the user commands e.g. ls, cat, echo and sleep.
The working consists of several functions to accomodate the user inputs.
the C program has been written such that whenever the user inputs a command, the command is parsed with tokenization function, the tokens are then sent to the execution function and forking is done.
All system commands can be run in our new shell.
You just need to compile the C program with gcc my_shell.c -o my_shell and then load it using ./my_shell
It will show the directory you are present in e.g. cwd
It also implements multiple functions written in singe line using '&'
and returns its pid using getpid().
The History function has been added in my_shell, what it does is provides the last command using "!!"
The I/O redirect function has been added recently. 

