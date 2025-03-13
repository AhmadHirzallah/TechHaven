#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdbool.h>
# include <sys/types.h>
# include <fcntl.h>

/* ---------------------------- IMPROVEMENTS ----------------------------- */
/* 1. Added header guards with proper indentation                          */
/* 2. Added necessary headers                                              */
/* 3. Using precise types (pid_t instead of int)                           */
/* 4. Better organization with comments                                    */
/* 5. Added documentation comments                                         */
/* 6. More semantic naming                                                 */
/* 7. Added safety features (array sizes)                                  */
/* ------------------------------------------------------------------------ */

typedef enum e_returns_exits
{
	OK = 0,
	ERR_WRNG_ARGS_NBR,
	ERR_NO_PATH_VAR_FOUND,
	ERR_FAIL_CREATING_PIPE,
	ERR_FAIL_CALLOC_CMDS,
	ERR_FAIL_IN_FORKING_HEREDOC,
	ERR_IN_GNL
}           t_returns_exits;

typedef enum e_error_print {
	PERROR,
	FD2,
	BOTH_FD2_PERROR
}   t_error_print;

/**
 * @enum e_pipe_mode
 * @brief Represents different pipe operation modes
 * 
 * - PIPEX_MODE_HEREDOC will make the (infile_fd = 0) & take input from user.
 */
typedef enum e_pipe_mode {
	PIPEX_MODE_STDIN,
	PIPEX_MODE_HEREDOC
}   t_pipe_mode;

/**
 * @struct s_io_files
 * @brief Contains input/output file management
 */
typedef struct s_io_files {
	int         infile_fd;
	int         outfile_fd;
}   t_io_files;

/**
 * @struct s_command
 * @brief Represents a single command with its full context
 */
typedef struct s_command {
	char        **cmd_args;          // Command arguments (NULL-terminated) like (ls -l -a)
	char        *full_path;      // Resolved absolute path  like (/bin/ls)		// *** STILL NOT WORKED ON
	bool        is_valid;        // Successfully validated command
}   t_command;

/**
 * @struct s_pipe_context
 * @brief Manages pipe operations and process tracking
 */
typedef struct s_pipe_context
{
	int         **pipes_fds;         // Array of pipe file descriptors
	pid_t       *childs_prcs_ids;     // Array of child process IDs *************** still not worked on
	size_t      num_pipes;       // Number of active pipes

	// size_t      num_children;    // Number of spawned children  // I am not sure if this can be used
}   t_pipe_context;

/**
 * @struct s_environment
 * @brief Contains execution environment details
 */
typedef struct s_environment {
	char        **raw_env;       // Original environment variables
	char        **system_paths;  // Parsed PATH directories
	const char  *shell_path_var;     // Absolute path to current shell
}   t_environment;

/**
 * @struct s_pipex
 * @brief Main context container for pipex operations
 *      
 * - num_commands will be argc-3 (skip 1(./pipex) 2(infile) 3(outfile))

 * - env contains raw envp and PATH varaiable splitted inside it !

 */
typedef struct s_pipex {
	// Input parameters
	int             argc;
	char            **argv;
	
	// System environment
	t_environment   env;

	t_pipe_mode		mode;            // Operation mode
	const char		*heredoc_delim;  // Needed for heredoc parsing
	
	
	// File management
	t_io_files      files;
	
	// Pipe management
	t_pipe_context  pipes;
	
	// Command execution
	t_command      *commands;
	size_t         num_commands;
	
	// Program state
	int             exit_code;
	bool            has_error;

}   t_pipex;


int			init_pipex_managing(t_pipex *pipex_info ,int argc, char **argv, char **envp);
int			terminate_pipex_with_msg(t_pipex *pipex_info, char *msg, t_returns_exits exit_code, t_error_print type);
int			terminate_pipex(t_pipex *pipex_info, t_returns_exits exit_code);
void		display_error_msg(char *msg, t_error_print type);
int			get_path_var(t_pipex *pipex_info);
int			get_cmdline_args(t_pipex *pipex_info);
int			pipe_on_pipes_fds(t_pipex *pipex_info);
int			get_io_files_ready(t_pipex *pipex_info);
int			perform_all_cmds(t_pipex *pipex_info);
void		ft_close_fds(int *pipes, int num_pipes, int file_fd);
int			handle_here_doc(t_pipex *pipex_info, int i);


#endif