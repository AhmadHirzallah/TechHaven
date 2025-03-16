/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_args_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 00:30:11 by ahirzall          #+#    #+#             */
/*   Updated: 2025/03/16 03:06:53 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

/*
	-   	1		2		3	 4		5
	-	./pipex infile cmd1 cmd2 outfile
	-     1			2		  3 	 4		5		6
	-	./pipex		here_doc   END	cmd1   cmd2   outfile
*/
char	***get_cmds_args(t_pipex *pipex, int i)
{
	pipex->cmds_args = NULL;
	i = 0;
	pipex->cmds_args = ft_calloc(pipex->main_pars.argc - 2, sizeof(char **));
	if (pipex->cmds_args == NULL)
		error_msg_termination(pipex, "ERROR; Malloc Failes.\n", FD2,
			(int)ERR_FAIL_CALLOC_CMDS);
	while ((i < pipex->main_pars.argc - 3) && (pipex->main_pars.argv[i + 2]))
	{
		pipex->cmds_args[i] = ft_split(pipex->main_pars.argv[i + 2], ' ');
		if (pipex->cmds_args[i] == NULL)
			error_msg_termination(pipex, "ERROR; Malloc Failes.\n", FD2,
				(int)ERR_FAIL_CALLOC_CMDS);
		i++;
	}
	pipex->num_cmds_args = i;
	return (pipex->cmds_args);
}
