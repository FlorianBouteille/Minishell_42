# Minishell_42
The first really consequent project in the 42 Common core. 

The point is to implement a robust command line interpreter, just like bash. The first part of the project was an exhaustive parsing challenge, as the project, in essence, is to read and interpret any user input. 

This was split into two major parts, the "lexing", aka splitting the input into comprehensive tokens, and the actual parsing of these tokens, in order to differenciate between commands, arguments, options and pipes. 
The second part was about execution, each command needs to be run in its own subprogram and send its result into the next command through a pipe. Behavior has to be consistent, especially in case of error, each subprogram has to handle and free its data properly and close file descriptors. 
Finally, it needed some signal handling, as the program had to interpret signals in order to exit properly according to where it receives the signal (main program, subprogram, heredoc, etc...). 

This was a great team effort and though its not very visual, we're pretty proud of the result !
