#include "pipex.h"
#include "libft.h"

int	peform_double_dup2(t_pipex *pipex_info)
{

}

void ft_close_fds(int *pipes, int num_pipes, int file_fd)
{
    int i;

    i = 0;
    while (pipes[i] && (i < num_pipes * 2))
    {
        if (pipes[i] > 2)
            close(pipes[i]);
        i++;
    }
    if (file_fd > 2)
        close(file_fd);
}