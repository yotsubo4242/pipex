/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:24:45 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/06/30 22:22:32 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "libft.h"

void	first_cmd_prc(t_data *data, int *pipe_fds, char **environ)
{
	close(pipe_fds[0]);
	close(1);
	if (dup2(pipe_fds[1], 1) < 0)
		exit(ERR_DUP2);
	if (execve(data->cmd_paths[0], data->cmds[0], environ) < 0)
		exit(ERR_EXECVE);
}

void	second_cmd_prc(t_data *data, char **environ)
{
	int	pipe_fds[2];
	int	child_fd;
	int	status;

	if (pipe(pipe_fds) < 0)
		exit(ERR_PIPE);
	if ((child_fd = fork()) < 0)
		exit(ERR_FORK);
	if (child_fd > 0)
	{
		wait(&status);
		if (status == ERR_EXECVE || status == ERR_DUP2)
			exit(ERR_EXECVE);
		close(pipe_fds[1]);
		close(0);
		if (dup2(pipe_fds[0], 0) < 0)
			exit(ERR_DUP2);
		if (execve(data->cmd_paths[1], data->cmds[1], environ) < 0)
			exit(ERR_EXECVE);
	}
	else
		first_cmd_prc(data, pipe_fds, environ);
}

int	do_cmds(t_data *data)
{
	int			child_fd;
	int			status;
	extern char	**environ;

	status = 0;
	if ((child_fd = fork()) < 0)
		return (ERR_FORK);
	if (child_fd > 0)
		wait(&status);
	else
		second_cmd_prc(data, environ);
	if (status == ERR_DUP2 || status == ERR_EXECVE)
		return (status);
	return (EXIT_SUCCESS);
}