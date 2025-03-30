#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>	// usleep
#include <time.h>
#include <sys/wait.h>
#include <signal.h>		// contains singals functions and structures.


/*
	- how to prevent the process to be sent to the background
*/
void handle_sigtstp()
{
	printf("Stop not allowed\n");
}

void handle_sigcont()
{
	printf(("input a number:  "));
	fflush(stdout);
}

int main(int argc, char **argv)
{
	system("clear");

	// struct sigaction sa;		// My System error :  incomplete type "struct sigaction" is not allowed ;;; C/C++(70)
	
	/*
		This will override the SIGTSTP and rather than Stopping/Pausing our process & sending background;
		it will perform handle_sigtstp() function and execute it rather than SIGTSTP.
	*/
	// signal(SIGTSTP, &handle_sigtstp);	// overriding SIGTSTP
	



	// Handle SIGCONT when program is displayed to printf the text again because it is gone
	// Comment SIGTSTP to make SIGCONT work !
	// signal(SIGCONT, &handle_sigcont);	
	
	(void) argc;
	(void) argv;
	/*
		Good Info:
			- fork() will produce a child that its (pid == 0) 
			- but also in the parent process (which pid != 0) it will have child id in pid
				- If we do in Child Process (getpid) (get process id) then it will get the ID of child
				- Also this value of getpid of the child will have 100% the same value of pid of (pid = fork())
			- so the fork() will make clone of the parent ; but also return the (child getpid) 
			- the child inside the program will have (pid of fork) of value (0) 
				- but this 0 isn't its pid or id nbr; it is C language function does.
	*/

	
	
	//	-  Handling the SIGTSTP of CTRL + Z 
	
	// struct sigaction sa;
	// sa.sa_handler = &handle_sigtstp;
	// sa.sa_flags = SA_RESTART;
	// sigaction(SIGTSTP, &sa, NULL);



	// Handling the SIGCONT of command: fg
	struct sigaction sa;
	sa.sa_handler = &handle_sigcont;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGCONT, &sa, NULL);

	int x ;
	printf(("input a number:  "));
	scanf("%d", &x);
	printf("Result (%d * 5) = (%d)\n", x, (x * 5));

	return (0);
}

