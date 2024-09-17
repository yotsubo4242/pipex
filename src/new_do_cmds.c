/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_do_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:09:54 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/09/17 14:06:59 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "libft.h"

//int	err_return(int errno, int pipe_fd0, int pipe_fd1, int file_fd)
//{
//	if (errno)
//		ft_printf()
//}

static void	cmd_proc(t_data *data, char **argv, int pipe_fds[2], t_bool is_second)
{
	extern char	**environ;
	int			file_fd;
	char		*file_name;

	close(pipe_fds[is_second]);
	if (!is_second)
	{
		file_name = argv[1];
		file_fd = open(file_name, O_RDONLY);
	}
	else
	{
		file_name = argv[4];
		file_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (file_fd < 0)
	{
		ft_printf("bash: %s: %s\n", file_name, strerror(errno));
		exit(err_return());
	}
	data->cmd_paths[is_second] = search_cmd_path(data->cmds[is_second][0], environ);
	if (!(data->cmd_paths[is_second]));
	{
		ft_printf("bash: %s: %s\n", data->cmds[is_second][0], strerror(errno));
		exit(err_return());
	}
	if (dup2(pipe_fds[!is_second], !is_second) < 0)
		exit(err_return());
	if (dup2(file_fd, is_second) < 0)
		exit(err_return());
	if (execve(data->cmd_paths[is_second], data->cmds[is_second], environ) < 0)
		exit(err_return());
}

// 親がpipe作れば兄弟間でもきょうゆうされる？？

void	do_cmds(t_data *data, char **argv)
{
	int		exit_status;
	int		child_fds[2];
	int		pipe_fds[2];

	errno = 0;
	if (pipe(pipe_fds) < 0)
		exit(err_return());
	child_fds[0] = fork();
	if (child_fds[0] < 0)
		return (err_return());
	else if (!child_fds[0])
		cmd_proc(data, argv, pipe_fds, FALSE);
	child_fds[1] = fork();
	if (child_fds[1] < 0)
		return (err_return());
	else if (child_fds[1])
		cmd_proc(data, argv, pipe_fds[2], TRUE);
	waitpid(child_fds[1], &exit_status, 0);
	wait(NULL);
	if (exit_status) {
		free_data(data);
		exit(exit_status);
	}
}