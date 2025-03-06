#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>	// usleep
#include <time.h>
#include <sys/wait.h>
#include <signal.h>	

/*
	- We want a program that use signals
		- It should prompt user to enter the number of seconds
		- The child process will start executing for the entered nbr of seconds.
		- After this nbr of seconds have elapsed(منقضي)
			- The execution stops (Not terminating or killing Process)!
			- Prompt the user again to enter nbr of seconds and execute them
		- if user entered a (0 or minus) number; then the program terminate 
*/
int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;
	int pid = fork();
	if (pid == -1)
	{
		printf("Error in forking\n\n");
		return (-1);
	}
	if (pid == 0)
	{	//Child
		int i = 0;
		while (1)
		{
			printf("%d- Some Text --\n\n", ++i);
			usleep(50000);
		}
	}
	else
	{
		kill(pid, SIGSTOP);
		int entered_time;
		do
		{
			printf("Enter the Time in seconds for the execution:  ");
			scanf("%d", &entered_time);
			if (entered_time > 0)
			{
				kill(pid, SIGCONT);
				sleep(entered_time);
				kill(pid, SIGSTOP);
			}
		} while(entered_time > 0);
		printf("Program is Terminated..\n\n");
		kill(pid, SIGKILL);
		wait(NULL);
	}

	return (0);
}