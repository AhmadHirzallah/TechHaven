/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:33:55 by ahirzall          #+#    #+#             */
/*   Updated: 2025/03/16 01:03:31 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define  PIPEX_BONUS_H

# include "get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_returns_exits
{
	OK = 0,
	ERR_OUTFILE,
	ERR_WRNG_ARGS_NBR,
	HERE_DOC_STOP,
	ERR_FAIL_CREATING_PIPE,
	ERR_FAIL_STRJOIN_CMDS,
	ERR_FAIL_IN_FORKING_HEREDOC,
	ERR_FAIL_IN_FORKING_INFILE,
	ERR_INPUT_FILE_HANDLER,
	ERR_INSTREAM_DUP2,
	ERR_OUTSTREAM_DUP2,
	ERR_DUP2_FAILS,
	ERR_CMD_NOT_XR = 126,
	ERR_CMD_NOT_EXIST = 127,
	ERR_NO_PATH_VAR_FOUND = 127,
	ERR_INPUT_FILE_READ = 0,
	ERR_FAIL_CALLOC_SYS_PATHS = -2,
	ERR_FAIL_CALLOC_CMDS = -2,
	ERR_FAIL_CALLOC_PIPES = -2,
	ERR_FAIL_CALLOC_CHILD_PIDS = -2,
	ERR_FAIL_STRJOIN_MALLOC = -2,
	ERR_IN_GNL_MALLOC = -2
}					t_returns_exits;

typedef enum e_error_print
{
	PERROR,
	FD2,
	BOTH_FD2_PERROR,
	FD1
}					t_error_print;

/**
 * @enum e_pipe_mode
 * @brief Represents different pipe operation modes
 *
 * - PIPEX_MODE_HEREDOC will make the (infile_fd = 0) & take input from user.
 */
typedef enum e_pipe_mode
{
	PIPEX_MODE_INFILE,
	PIPEX_MODE_HEREDOC
}					t_pipe_mode;

// /**
//  * @struct s_io_files
//  * @brief Contains input/output file management
//  */
typedef struct s_io_files
{
	int				infile_fd;
	int				outfile_fd;
}					t_io_files;

typedef enum e_commands_permissions
{
	PERMISSIONS_OK = -1,
	PER_NOT_EXIST_F_NOK = 1,
	PER_NOT_X_R_NOK = 2,
	PER_CHECK_LATER = 4
}					t_commands_permissions;

/**
 * @struct s_command
 * @brief Represents a single command with its full context
 */
typedef struct s_command
{
	char			**cmd_args;
	char			**env_bins_paths;
}					t_command;

/**
 * @struct s_environment
 * @brief Contains execution environment details
 */
typedef struct s_main_env_pars
{
	int				argc;
	char			**argv;
	char			**raw_envp;
}					t_main_env_pars;

/**
 * @struct s_pipexredirection, the exit status is greater than zero
 * @brief Main context container for pipex operations
 *
 * - num_commands will be argc-3 (skip 1(./pipex) 2(infile) 3(outfile))

 * - env contains raw envp and PATH varaiable splitted inside it !

 */
typedef struct s_pipex
{
	t_main_env_pars	main_pars;
	t_pipe_mode		pipex_mode;
	const char		*heredoc_delim;
	char			**system_paths;
	char			***cmds_args;
	int				num_cmds_args;
	t_io_files		files;
	int				**pipes_fds;
	int				*childs_pids;
	int				errno_rtrn;
}					t_pipex;

void				process_characteristics(t_pipex *pipex);
char				**extract_all_paths(t_pipex *pipex);
char				***get_cmds_args(t_pipex *pipex, int i);
void				error_msg(char *msg, t_error_print type);
int					get_io_files_ready(t_pipex *pipex);
int					open_pipes(t_pipex *pipex, int i);
int					handle_input_cmd(t_pipex *pipex, int i);
void				input_here_doc(t_pipex *pipex);
int					perform_both_io_dup2(t_pipex *pipex, int in_stream,
						int out_stream);
int					processing_cmd_args(t_pipex *pipex, char *cmd_args,
						char **complete_cmd, int i);
int					is_valid_cmd_checker(t_pipex *pipex, char *cmd);
int					get_outfile_ready(t_pipex *pipex);
int					perform_last_cmd(t_pipex *pipex, int i);
int					perform_middle_pipes_cmds(t_pipex *pipex, int i);
int					handle_input_cmd(t_pipex *pipex, int i);
int					handle_here_doc(t_pipex *pipex, int i);
void				cleanup_pipex(t_pipex *pipex);
void				free_childs_pids(t_pipex *pipex);
void				free_pipes_fds(t_pipex *pipex);
void				free_cmds_args(t_pipex *pipex);
void				free_system_paths(t_pipex *pipex);
void				close_all_files(t_pipex *pipex);
void				close_all_pipes(t_pipex *pipex);
void				error_msg_termination(t_pipex *pipex, char *msg,
						t_error_print type, int exit_code);
char				*join_cmds_handler(t_pipex *pipex, char *s1, char *s2,
						bool free_s2);
int					process_here_doc_line(t_pipex *pipex);
void				close_io_pipes(t_pipex *pipex, int *pipes_fds);

#endif

/*
typedef enum e_close_specifying
{
	CLOSE_IN_FILE,
	CLOSE_OUT_FILE,
	CLOSE_IO_FILES,
	CLOSE_IN_PIPE_FD,
	CLOSE_OUT_PIPE_FD,
	CLOSE_IO_PIPE
}					t_error_print;


// int			initialize_pipex(t_pipex *pipex_info ,int argc, char **argv,
				// char **envp);
// int			get_path_var_and_paths(t_pipex *pipex_info);
// int			get_cmdline_args(t_pipex *pipex_info);
// int			pipe_on_pipes_fds(t_pipex *pipex_info);
// int			get_io_files_ready(t_pipex *pipex_info);
// int			perform_all_cmds(t_pipex *pipex_info);
// int			handle_here_doc(t_pipex *pipex_info, int i);
// int			handle_input_file(t_pipex *pipex_info, int i, int j);
// void		close_io_pipes(int *pipes_fds);
// void		close_all_pipes(t_pipe_context *pipex_info, int i);
// void		close_io_files(t_io_files *files);
// int			peform_io_dble_dup2(int in_stream, int out_stream);
// int			is_valid_cmd_check(t_pipex *pipex_info, char *full_path_cmd,
				t_command **commands);
// int			process_any_cmd(t_pipex *pipex_info, int i);
// int			get_io_files_ready(t_pipex *pipex_info);
// void		close_all_pipes_till_index(t_pipe_context *pipex_info, int i,
			int end);
// void		termination_with_all_closing(t_pipex *pipex_info,
			t_returns_exits exit_code, int i);
// void		display_error_msg(char *msg, t_error_print type);
// int			terminate_pipex(t_pipex *pipex_info, t_returns_exits exit_code);
// void		terminate_pipex_with_msg(t_pipex *pipex_info, char *msg,
			t_returns_exits exit_code, t_error_print type);
// void		term_pipex_pipes_handling(t_pipex *pipex_info, char *msg,
			t_returns_exits exit_code, t_error_print type);
// void		execute_cmd(t_pipex *pipex_info, int i);
// char		*get_executable_cmd(t_pipex *pipex_info, char *system_path,
			char *cmd);
// void		input_here_doc(t_pipex *pipex_info, int i);
*/
