#include <stdlib.h>
#include <string.h>		// for using strlen and string functions
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>  // Added header for getpid/getppid/wait()
#include <stdio.h>	// this and the below errno.h needed for (perror)
#include <errno.h>


int	main (int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;

	FILE *file_ptr;
	(void)file_ptr;

	file_ptr = fopen("fileIsNotExist.txt", "r"); // Read mode; files isn't exist in debug folder.
	// Bec. of this the program will throw an error message
	// we will try to find the corresponding error code for that

	// 1'st way:
	printf("(errno value)\tError Number:\t%d\n", errno);	// it return error number (2) (u can search it; but it is for not exist files)


	//	We are going to point to the exact error type using strerror(errno) function
	printf("(strerror):\tString error:\t%s\n\n", strerror(errno));

	// We are going to Display the latest error occured using perror()
	perror("\n(perror)\tLatest error occured");	// Perror don't need any variable or helper things

	// EXITFAILUR & EXITSUCCESS	:: To use them; include stdlib.h
	// instead of using non zero error code in exit() function we can use these 2
	exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS); // this won't be reached :)
	/*
		- you can (and often should) return distinct non-zero error codes
			 to indicate different types of errors. The standard macros EXIT_SUCCESS
			  (typically defined as 0) and EXIT_FAILURE (typically defined as 1)
			   are provided for general usage, but they don't give you granular error information.
		- In a more complex program, you can define your own error codes—either via 
			#define macros or an enumeration—to represent various failure scenarios. This way,
			 when your program terminates due to an error, the exit code will indicate what went
			  wrong, making debugging and logging easier.

		typedef enum {
	    EXIT_OK = 0,
	    ERR_FILE_NOT_FOUND = 2,
	    ERR_INVALID_ARGUMENT = 3,
	    ERR_NETWORK_FAILURE = 4
	} ErrorCode;
	*/
	return (0);	// This won't be reached by exit(....) above
}