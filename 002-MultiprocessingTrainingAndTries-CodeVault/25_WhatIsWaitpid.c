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
		- waitpid :
			- If we want to wait for a specific process
			- If we have many Childs; and one take longer time
				- And we want to make it 1'st Finished Process  
				- So we need to make All Other Main(Parent)/Childs Processes wait for the specific Child 
				- We want to specify the first ending child (all processes are waiting it to finish first)
				- After Specifying this process and make all Process Wait it (line of code using waitpid)
					 then they can execute and terminate; but before all waited for the specified Child Process
	*/

	int p_id1 = fork();
	if (p_id1 < 0)
		return (1);
	if (p_id1 == 0)		// if is child
	{
		sleep(4);
		printf("\nFinished Execution of (%d)\n", getpid());
		return (0);
	}
	int p_id2 = fork();
	if (p_id2 < 0)
		return (2);
	if (p_id2 == 0)
	{
		sleep(1);
		printf("\nFinished Execution of (%d)\n", getpid());
		return (0);
	}

	/*
		- But the problem that we want the p_id1 to be first finished process.
			- This means all processes should wait for 1'st child finish first (4 seconds)
			- then the fast processes (Parent/Main & 2'nd Child p_id2) can finish (Child2 before Main of course).
		- So we want to wait first for the Longest Running Process p_id1 (4 seconds)
	*/
	// int wait_pid = wait(NULL);
	// printf("Waited for %d\n\n", wait_pid);
	// int wait_pid2 = wait(NULL);
	// printf("Waited for %d\n\n", wait_pid2);



	/*
		- We want to wait first for the Longest Running Process p_id1 (4 seconds).
		- All processes will exeucte this line & wait for the 1'st Child that takes (4 secs to execute)
		- 1st Argument is the process id of the child (which is returned in fork())
		- 2nd Argument is as wait(NULL) or wait(*ptr) ;; pid_t wait(int *wstatus);
			- When you call wait(NULL), you are telling the system that you don't care about the exit
				 status of the terminated child process.
			- When you call wait(&status) (or equivalently, wait(ptr) if ptr is a pointer to an integer),
				 the function will store the termination status of the child process in the variable pointed
				 to by ptr. You can then examine this status using macros such as
				 WIFEXITED(status), WEXITSTATUS(status), WIFSIGNALED(status), etc.
			- pid_t waitpid(pid_t pid, int *wstatus, int options);
				- This is a pointer to an integer variable where the termination status of the child process is stored.
				- Similar to wait(), you can use macros such as WIFEXITED, WEXITSTATUS, WIFSIGNALED, etc.,
					 to interpret the status stored in the variable.
				- If you don’t care about the termination status, you can pass NULL.
		
		- 3rd Argument is telling/specifying How to wait; (0 default)
			- pid_t waitpid(pid_t pid, int *wstatus, int options);
			- This is an integer value that specifies options for the behavior of waitpid.
			- When set to 0, waitpid blocks until the specified child process terminates.
			- You can also combine options using bitwise OR. Common options include:
				- WNOHANG: Return immediately if no child has exited yet.
				- WUNTRACED: Also return if a child has stopped (but not terminated) due to a signal.
				- WCONTINUED: Report if a stopped child has been resumed by delivery of SIGCONT.
	*/
	int wait_pid = waitpid(p_id1, NULL, 0);	
	printf("\nWaited for %d\n\n", wait_pid);
	int wait_pid2 = waitpid(p_id2, NULL, 0);
	printf("\nWaited for %d\n\n", wait_pid2);

	return (0);
}
