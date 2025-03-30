#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// for using strlen and string functions
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>  // Added header for getpid/getppid/wait()


/*
Project Idea:
	- the program : 	ping -c 5 google.com | grep rtt
	- What happens is: 	
		- The stdout of ping ... *.com is routed into the (pipe |)
		- The seconds program/executable (grep) take in input (from pipe[0]) rather than (stdin) !
		- then it perform grep rtt on the (pipe[0]) and get the final result ! 
	- This depends on the command; since (grep) knows how to handle the standard input 
*/

/*
 Code Planning:
	- We will have Parent/Main process which only will create pipes and processes
	- fork a 1'st child process  that will execute the 1'st command (ping)
	- fork another child process to execute the grep command !
	- we will use a pipe which is created by the main process to
		redirect the input & output properly from (ping process) (1'st Child)
		to the (grep process) (2'nd Child). 
*/
int	main (int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;

	int p_fd[2];
	if (pipe(p_fd) < 0)
		return (1);
	int p_id1 = fork();
	if (p_id1 < 0)
		return 2;
	if (p_id1 == 0) // 1'st Child executing the (ping) command
	{
		printf("\nPing Command is proceccing ...\n\n");
		close(p_fd[0]);
		// Overwritting the output stream (fd = 1 overwritted/remove) and set it to the pipe[1] writting end
		dup2(p_fd[1], STDOUT_FILENO);
		char *command[] = {"ping", "-c", "5", "Google.com", NULL};
		close(p_fd[1]);
		execve("/bin/ping", command, envp);
	}
	int p_id2 = fork();
	if (p_id2 < 0)
		return 3;
	if (p_id2 == 0) // 2'nd Child executing the (grep) command on input of child 1 (ping)
	{
		close(p_fd[1]);
		dup2(p_fd[0], STDIN_FILENO);
		char *command[] = {"grep", "rtt", NULL};
		close(p_fd[0]);
		// printf("\ngrep Command is proceccing ...\n\n");	// Bad printing
		execve("/usr/bin/grep", command, envp);
	}
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(p_id1, NULL, 0);
	waitpid(p_id2, NULL, 0);
	return (0);
}