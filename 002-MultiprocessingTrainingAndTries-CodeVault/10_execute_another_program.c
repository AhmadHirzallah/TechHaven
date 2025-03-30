#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>

/*
	- We want to execute a program using (c in coding) rather than in terminal
	- Like (ping google.com) which is done in terminal.
	- We want to perform it using a .c program !

	- This is achieved using the (exec) family of functions
		- For (Windows) it is <process.h>
		- For (Linux) it is <unistd.h>
*/
int main (int argc, char **argv)
{
	(void) argc;
	(void) argv;
	/*
		(1st: The Path To The Program)
		(2nd: The Path that we have Executed)
		(3rd: The 1'st argument to our program like "google.com")
		(4th: If we don't have any more arguments that we want to send to the program; then we have to pass NULL;;;
			Otherwise the program Won't Work!!!).

		- (execl) don't go to the program (ping for example) and execute it then return to the main program
			- (execl) will override the main/parent process and put it in top of it ! it will override the calling process !!
				- Overridding the Memory & Execution order !!
		- (execl) (ex*l) the l at end of exec stands for list of arguments; so we executed the ping program with a list of arguments !!
		- instead of (execl) we can use (execv) (l into b) which stands for a vector !
			- instead of listing the arguments using (execl); with (execv) we can use an array of argument and send it into the execv !!!!
	*/

/*
	execl("/usr/bin/ping",
			"/usr/bin/ping",
			"facebook.com",
			NULL);
*/

	/*
		- We can use (execlp()) which we can write the name of the executable without the path like execl() !
		- execlp : the (p) tells the exec() function to use the path variable; which is loaded automatically in the command prompt
	*/

	// execlp("ping" , "ping" , "gmail.com", NULL);

	// char *args_arr[] = {"ping" , "yahoo.com", NULL};
	// execvp("ping", args_arr);


	/*
		execvpe() ; in this; we can pass an environemt variable path like main() parameter (char *envp[])
	*/
	char *args_arr[] = {"ping" , "online.visual-paradigm.com", NULL};
	char *envp[] = {
		"TEST=environment variable",
		NULL
	};
	int err = errno;		// you can debug and search for this errno for example if it is err = 0x000002 so the error number 2 find it and search ; find it; for example it will say no file/program found with this name (no ping2 program for example only there is ping)
	execve("ping", args_arr, envp);		// Won't work because we dont have envp variable that have an ping program ! :)






	printf("Program (ping) finished executing.\n");
	return (0);
}
