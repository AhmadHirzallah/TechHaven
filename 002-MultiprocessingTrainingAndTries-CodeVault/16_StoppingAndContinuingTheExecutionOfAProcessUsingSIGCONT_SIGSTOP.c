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
	/*
		Good Info:
			- fork() will produce a child that its (pid == 0) 
			- but also in the parent process (which pid != 0) it will have child id in pid variable
				- If we do in Child Process (getpid) (get process id) then it will get the ID of child
				- Also this value of getpid of the child will have 100% the same value of pid of (pid = fork())
			- so the fork() will make clone of the parent ; but also return the (child getpid) 
			- the child inside the program will have (pid of fork) of value (0) 
				- but this 0 isn't its pid or id nbr; it is C language function does.
	*/

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
		// Parent
		// pid is equal getpid of child (getpid of child = pid (pid of fork))
		kill(pid, SIGSTOP);	// So this is sending to the Child Process a Signal to stop.
		int entered_time;
		do
		{
			printf("Enter the Time in seconds for the execution:  ");
			scanf("%d", &entered_time);
			if (entered_time > 0)
			{
				kill(pid, SIGCONT);		// Continue Execution of Child Process while loop
				sleep(entered_time);	// waiting child process executin by entered time in seconds ! 
				kill(pid, SIGSTOP);		// after sleep/waiting time is finished stop the child process
			}
		} while(entered_time > 0)
		;
		printf("Program is Terminated..\n\n");
		kill(pid, SIGKILL);	// Terminate the program
		wait(NULL);
	}

	return (0);
}