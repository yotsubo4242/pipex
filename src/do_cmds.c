/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:18:39 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/07/09 21:56:37 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "libft.h"

static int	err_return(int err_num, int *fd1_p, int *fd2_p)
{
	if (err_num)
		ft_printf("bash: %s\n", strerror(err_num));
	if (fd1_p)
		close(*fd1_p);
	if (fd2_p)
		close(*fd2_p);
	return (EXIT_FAILURE);
}

static void	first_cmd_prc(t_data *data, char **argv, \
							int *pipe_fds, char **environ)
{
	int		infile_fd;

	close(pipe_fds[0]);
	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd < 0)
	{
		ft_printf("bash: %s: %s\n", argv[1], strerror(errno));
		exit(err_return(0, &pipe_fds[1], NULL));
	}
	data->cmd_paths[0] = search_cmd_path(data->cmds[0][0], environ);
	if (!(data->cmd_paths[0]))
	{
		ft_printf("bash: %s: %s\n", data->cmds[0][0], strerror(errno));
		exit(err_return(0, &pipe_fds[1], &infile_fd));
	}
	if (dup2(pipe_fds[1], 1) < 0)
		exit(err_return(errno, &pipe_fds[1], &infile_fd));
	if (dup2(infile_fd, 0) < 0)
		exit(err_return(errno, &pipe_fds[1], &infile_fd));
	if (execve(data->cmd_paths[0], data->cmds[0], environ) < 0)
		exit(err_return(errno, &pipe_fds[1], &infile_fd));
}

static void	second_cmd_prc(t_data *data, char **argv, char **environ)
{
	int		pipe_fds[2];
	int		child_fd;
	int		outfile_fd;

	if (pipe(pipe_fds) < 0)
		exit(err_return(errno, NULL, NULL));
	child_fd = fork();
	if (child_fd < 0)
		exit(err_return(errno, &pipe_fds[0], &pipe_fds[1]));
	if (child_fd > 0)
	{
		wait(NULL);
		close(pipe_fds[1]);
		outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile_fd < 0)
		{
			ft_printf("bash: %s: %s\n", argv[4], strerror(errno));
			exit(err_return(0, &pipe_fds[0], NULL));
		}
		data->cmd_paths[1] = search_cmd_path(data->cmds[1][0], environ);
		if (!(data->cmd_paths[1]))
		{
			ft_printf("bash: %s: %s\n", data->cmds[1][0], strerror(errno));
			exit(err_return(0, &pipe_fds[0], &outfile_fd));
		}
		if (dup2(pipe_fds[0], 0) < 0)
			exit(err_return(errno, &pipe_fds[0], &outfile_fd));
		if (dup2(outfile_fd, 1) < 0)
			exit(err_return(errno, &pipe_fds[0], &outfile_fd));
		if (execve(data->cmd_paths[1], data->cmds[1], environ) < 0)
			exit(err_return(errno, &pipe_fds[0], &outfile_fd));
	}
	else
		first_cmd_prc(data, argv, pipe_fds, environ);
}

void	do_cmds(t_data *data, char **argv)
{
	int			child_fd;
	extern char	**environ;

	errno = 0;
	child_fd = fork();
	if (child_fd < 0)
	{
		err_return(errno, NULL, NULL);
		return ;
	}
	if (child_fd > 0)
		wait(NULL);
	else
		second_cmd_prc(data, argv, environ);
}