#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// for using strlen and string functions
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>  // Added header for getpid/getppid/wait()


int	main (int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	(void) envp;
	
	/*
		- name of fork (p_id) ; it is actually not the current process ID;
		- So you may think all child processes will have (Process ID = 0)
			- But this is 100% WRONG
		- fork() DOES'NT return the Process ID	;;; 
		- fork() returns 2 values because it split (clone) the process so 2 values are returned
		- fork() : 
			- Inside the Parent Process ---->>>> We are returning Child Process ID
				- The child process which is created(cloned) after fork is called is returned
					inside the p_id variable (INSIDE THE PARENT PROCESS; THE ID VAR HAVE CHILD ID)
		- Parent Process p_id != getpid so the actual process id of the process isn't inside p_id
		- Inside Child Process there is an arbitrary number which is always (0). 
			- Child Process (p_id : 0) != (getpid : actual process id of Child) of the child !  
		- This is provided to make us know how we can distinguish between the parent process
			 and the child process.
			- So it is only to let us know if we are in Child Process AT THE TIME OF
				 EXECUTION/RUNNING of Program
	*/
	int p_id = fork();
	if (p_id < 0)
		return (1);
	if (p_id == 0)		// if is child
		sleep(1);
	printf("Returned by fork(): [%d],\t\tCurrent ID (using getpid()): [%d],\t\tParent ID (using getppid()): [%d]\n\n", 
			p_id ,getpid(), getppid());
	int result = wait(NULL);
	if (result == -1)
		printf("No Children to wait for; PROGRAM FINISHED\n\n");
	else
		printf("[%d] Finished Execution.\n\n", result);

	return (0);
}
