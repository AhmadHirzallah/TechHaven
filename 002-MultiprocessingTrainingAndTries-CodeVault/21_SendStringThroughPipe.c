#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// for using strlen and string functions
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>  // Added header for getpid/getppid/wait()

int	main (int argc, char **argv)
{
	(void) argc;
	(void) argv;

	int p_fd[2];
	if (pipe(p_fd) < 0)
		return (1);
	int pid = fork();
	if (pid < 0)
		return 2;
	// read a line from the user and send it through a pipe to the parent process.
	if (pid == 0) // child process
	{
		close(p_fd[0]);
		printf("\n\nChild process.\n\n");
		char input[200];
		printf("input string:   ");

		/*
			- (str to read into), (maximum length), (stream of reading)
			- at the end of the string a \n is left and we kind of have to remove it.
		*/ 
		fgets(input, 200, stdin);
		input[strlen(input) - 1] = '\0';	// this is the last character which is '\n' but we set it into '\0' or 0
		
		int str_size = strlen(input) + 1; // include the '\0' & send all of chars of string
		if (write(p_fd[1], &str_size, sizeof(int)) < 0)
			return (3);
		printf("Sent the size of the string: %d\n", str_size);
		if (write(p_fd[1], input, (str_size * sizeof(char))) < 0)
			return (4);
		printf("Sent the string: (%s) to the Parent Process\n", input);
		close(p_fd[1]);
	}
	else if (pid != 0)	// Parent Process
	{
		close(p_fd[1]);
		char received_input[200];
		int str_size;
		if (read(p_fd[0], &str_size, sizeof(int)) < 0)
			return (5);
		printf("\n\nParent process.\n\n");
		printf("Received the size of the string: %d\n", str_size);
		if (read(p_fd[0], received_input, (sizeof(char) * str_size)) < 0)
			return (6);
		printf("Received the string: (%s) from the Child Process\n", received_input);
		printf("String is:  [%s]\n", received_input);
		close(p_fd[0]);
		wait(NULL);
	}
	
}