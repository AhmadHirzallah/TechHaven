#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//We need unistd to use fork function
// Unistd is a linux specific library ; it is only found on linux -- some people do same for windows
#include <unistd.h>
#include <sys/wait.h>  // Added header for wait()


int main (int argc, char **argv)
{
	(void) argc;
	(void) argv;
/*
	// Section One
*/
	// int p_id = fork();
	// int n;
	
	// /*
	// 	- if we are at main process we go from (101) to (200)
	// 	- if we are at child process we start from (1) to (100)  
	// */
	// if (p_id != 0)
	// 	n = 101;
	// else if (p_id == 0)	// child first printing; (1 to 100) -- then parent printing (101 to 200)
	// 	n = 1;
	// int i = n;
	// /*	
	// 	- Now to get a proper result that	we want;
	// 	  We have to flush the standard ouput everytime we print something on the screen 
	// 	  Basically the standard output when you use printf or something to it;
	// 	  It has an internal Buffer;
	// 	  if you print a lot of things very quickly; it won't print them automatically
	// 	  It will wait to get all the input; then print whole output text !				
	// 	 - If we want to print them all excactly when we call printf
	// 	 - To solve this we use `fflush()` of stdout as `fflush(stdout)
	// 	 	So Every time we print a number or a digit it's going to be actually shown on the terminal.
	// */
	// while (i < n + 100)
	// {	
	// 	printf("(%i)  ", i++);
	// 	fflush(stdout);
	// }
	// printf("\n\n\n\n\n");
	/*
		The problem is that the numbers arn't in the order that we expected From 1 to 200 !!! 
		They are printed randomly !!! Because 2 proceses splitted in (fork) and both execute every single statement 
		and can thus can be at same time. 
	*/



	// solving using wait : 
	int p_id = fork();
	int n;

	if (p_id == 0)
		n = 1;
	else if (p_id != 0)
		n = 101;
	/*
		If we are in the main process;
		we should wait for the child process to finish printing its numbers then main/parent will be launched.
	*/
	/*
		The POSIX function wait is declared to take a pointer argument (int *);
		where it stores the exit status of the terminated child.
		 Since you don't need the status, pass NULL as the argument.
	*/
	if (p_id != 0)	
		wait(NULL);
	int i = n;
	while (i < n + 100)
	{
		printf("(%i)\t", i++);
		fflush(stdout);
	}
	if (p_id != 0)
		printf("\n\n\n\n\n");
	

	/*
		We need to wait the child process to print its numbers!
		Then print main/parent process numbers 
	*/

	return (0);
}