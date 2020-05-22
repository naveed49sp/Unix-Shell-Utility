all versions are implemented in different files.
functions_v1.c contains the functions which are used to implement version01, functions_v2.c contains those functions which are used to implement version 2 and so on.
version 01 is almost same as discussed in video lecture
version 02 can perform i/o redirection. 
	> for i/o redirection "infile.txt" and "outfile.txt" should present in cwd
	> This version also handles the use of pipes
	> "cat /etc/passwd > outfile.txt" will print the output in given file
	> "cat /etc/passwd | wc" will print the count on stdout
version 03 supports executing multiple commmands on a single line if they are separated by a semicolon (;)
makefile is written for compiling and installing the project
Use following commands to test the working.
> "make" it will run the commands in sequence and generate "myexe"
> "make clean" it will remove intermediate object files
> "make install" it will install myexe in /usr/bin
> "make uninstall" it will remove myexe from /usr/bin
> Don't forget to use sudo before installing or uninstalling the project
> "./myexe" it will run the project and show the prompt on stdout
> "cat /etc/passwd > outfile.txt" it will print the output in given file
> "cat /etc/passwd | wc" will print the count on stdout
> " ls ; ls -l" it will execute multiple commands on single line separated by semicolon
> "ctrl + D" it will terminate the program
version 04 stores history of commands