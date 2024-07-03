/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:24:45 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/07/03 21:29:56 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "libft.h"

// [!] need to modify
// - close pipe_fsd when error occurred.

static int	err_return(int err_num, int *fd_1, int *fd_2)
{
	if (fd_1)
		close(*fd_1);
	if (fd_2)
		close(*fd_2);
	return (err_num);
}

static void	first_cmd_prc(t_data *data, char **argv, int *pipe_fds, char **environ)
{
	int	infile_fd;

	close(pipe_fds[0]);
	if (dup2(pipe_fds[1], 1) < 0)
		exit(err_return(ERR_DUP2, NULL, &pipe_fds[1]));
	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd < 0)
		ft_printf("%s: %s\n", argv[1], strerror(errno));
	if (dup2(data->infile_fd, 0) < 0)
		exit(err_return(ERR_DUP2, NULL, &pipe_fds[1]));
	if (execve(data->cmd_paths[0], data->cmds[0], environ) < 0)
		exit(err_return(ERR_EXECVE, NULL, &pipe_fds[1]));
}

static void	second_cmd_prc(t_data *data, char **argv, char **environ)
{
	int	pipe_fds[2];
	int	child_fd;
	int	status;
	int	outfile_fd;

	if (pipe(pipe_fds) < 0)
		exit(err_return(ERR_PIPE, NULL, NULL));
	if ((child_fd = fork()) < 0)
		exit(err_return(ERR_FORK, &pipe_fds[0], &pipe_fds[1]));
	if (child_fd > 0)
	{
		wait(&status);
		if (status == ERR_EXECVE || status == ERR_DUP2)
			exit(err_return(status, &pipe_fds[0], &pipe_fds[1]));
		outfile_fd = open(argv[4], O_WRONLY | O_CREAT, 0644);
		if (outfile_fd < 0)
		{
			ft_printf("%s: %s\n", argv[4], strerror(errno));
			return ;
		}
		close(pipe_fds[1]);
		close(0);
		if (dup2(pipe_fds[0], 0) < 0)
			exit(err_return(ERR_DUP2, &pipe_fds[0], &pipe_fds[1]));
		close(1);
		if (dup2(outfile_fd, 1) < 0)
			exit(err_return(ERR_DUP2, &pipe_fds[0], &pipe_fds[1]));
		if (execve(data->cmd_paths[1], data->cmds[1], environ) < 0)
			exit(err_return(ERR_EXECVE, &pipe_fds[0], &pipe_fds[1]));
	}
	else
		first_cmd_prc(data, argv, pipe_fds, environ);
}

int	do_cmds(t_data *data, char **argv)
{
	int			child_fd;
	int			status;
	extern char	**environ;

	status = 0;
	if ((child_fd = fork()) < 0)
		return (ERR_FORK);
	if (child_fd > 0)
	{
		wait(&status);
		if (status == ERR_DUP2 || status == ERR_EXECVE)
		return (status);
	}
	else
		second_cmd_prc(data, argv, environ);
	if (status == ERR_DUP2 || status == ERR_EXECVE)
		return (status);
	return (EXIT_SUCCESS);
}