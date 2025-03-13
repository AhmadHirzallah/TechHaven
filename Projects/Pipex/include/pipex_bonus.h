#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdbool.h>
# include <sys/types.h>

/* ---------------------------- IMPROVEMENTS ----------------------------- */
/* 1. Added header guards with proper indentation                          */
/* 2. Added necessary headers                                              */
/* 3. Using precise types (pid_t instead of int)                           */
/* 4. Better organization with comments                                    */
/* 5. Added documentation comments                                         */
/* 6. More semantic naming                                                 */
/* 7. Added safety features (array sizes)                                  */
/* ------------------------------------------------------------------------ */

/**
 * @enum e_pipe_mode
 * @brief Represents different pipe operation modes
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
    const char  *heredoc_delim;  // Needed for heredoc parsing
}   t_io_files;

/**
 * @struct s_command
 * @brief Represents a single command with its full context
 */
typedef struct s_command {
    char        **cmd_args;          // Command arguments (NULL-terminated) like (ls -l -a)
    char        *full_path;      // Resolved absolute path  like (/bin/ls)
    bool        is_valid;        // Successfully validated command
}   t_command;

/**
 * @struct s_pipe_context
 * @brief Manages pipe operations and process tracking
 */
typedef struct s_pipe_context {
    t_pipe_mode mode;            // Operation mode
    int         **pipes_fds;         // Array of pipe file descriptors
    size_t      num_pipes;       // Number of active pipes
    pid_t       *child_pids;     // Array of child process IDs
    // size_t      num_children;    // Number of spawned children  // I am not sure if this can be used
}   t_pipe_context;

/**
 * @struct s_environment
 * @brief Contains execution environment details
 */
typedef struct s_environment {
    char        **raw_env;       // Original environment variables
    char        **system_paths;  // Parsed PATH directories
    // const char  *shell_path;     // Absolute path to current shell
}   t_environment;

/**
 * @struct s_pipex
 * @brief Main context container for pipex operations
 */
typedef struct s_pipex {
    // Input parameters
    int             argc;
    char            **argv;
    
    // System environment
    t_environment   env;
    
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

#endif