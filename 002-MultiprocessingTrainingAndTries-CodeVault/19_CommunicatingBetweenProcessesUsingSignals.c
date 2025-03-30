#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>	// usleep
#include <time.h>
#include <sys/wait.h>
#include <signal.h>		// contains singals functions and structures.

int x = 0;

void handle_sigusr1()
{
	if (x == 0)
	{
		printf("\nThe multiplication is a repititive addition...!!\n");
		fflush(stdout);
	}
}

/*
	- A simple question is asked by the program and the user have to answer it
	- if it takes more than 5 seconds for the user to answer; 
		- then the user will receive a hint.
	- this should be done using 2 processes.
*/
int main(int argc, char **argv)
{
	system("clear");

	
	(void) argc;
	(void) argv;

	int pid = fork();
	if (pid < 0)
		return (1);

	if (pid == 0) // Child
	{
		sleep(5); // Sleeps exactly 5 seconds
		
		/*
			- SIGUSR1 is userdefined process; if we dont handle it;
				  - then the default behaviour is to terminete the process !!
						- Handling is in Parent Process Because it will receive the SIGUSR1 and 
							it will terminate the process if we don't handle it for parent!
						- handling it in child won't affect the parent process 
							which should receive this signal and handle it by printing hint !
		*/
		kill(getppid(), SIGUSR1);	
		exit(EXIT_SUCCESS);
	}
	else // Parent : wait 5 secs then provide hinting to the user
	{
		// signal(SIGUSR1, &handle_sigusr1);	// This don't work and rissed an error

		// Everything work fine; run program on System/Terminal
		struct sigaction sa;
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = handle_sigusr1;
		sigaction(SIGUSR1, &sa, NULL);

		printf("What is the result of:  3 * 5 =  ");
		scanf("%d", &x);
		if (x == 15)
			printf("Right Answer :)\n");
		else
			printf("Wrong Answer :(\n");
		wait(NULL);
	}




}