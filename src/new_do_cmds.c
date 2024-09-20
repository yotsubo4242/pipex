/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_do_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:09:54 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/09/19 15:51:52 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "libft.h"

int	err_return(int err_num, int *pipe_fd0_p, int *pipe_fd1_p, int *file_fd_p)
{
	if (err_num)
		perror("");
		//ft_printf("bash: %s\n", strerror(err_num));
	if (pipe_fd0_p)
		close(*pipe_fd0_p);
	if (pipe_fd1_p)
		close(*pipe_fd1_p);
	if (file_fd_p)
		close(*file_fd_p);
	return (EXIT_FAILURE);
}

static void	cmd_proc(t_data *data, char **argv, int pipe_fds[2], t_bool is_last)
{
	extern char	**environ;
	int			file_fd;
	char		*file_name;

	close(pipe_fds[is_last]);
	if (!is_last)
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
		//ft_printf("bash: %s: %s\n", file_name, strerror(errno));
		exit(err_return(errno, &pipe_fds[!is_last], NULL, NULL));
	}
	data->cmd_paths[is_last] = search_cmd_path(data->cmds[is_last][0], environ);
	if (!(data->cmd_paths[is_last]))
	{
		//ft_printf("bash: %s: %s\n", data->cmds[is_last][0], strerror(errno));
		exit(err_return(errno, &pipe_fds[!is_last], NULL, &file_fd));
	}
	if (dup2(pipe_fds[!is_last], !is_last) < 0)
		exit(err_return(errno, &pipe_fds[!is_last], NULL, &file_fd));
	if (dup2(file_fd, is_last) < 0)
		exit(err_return(errno, &pipe_fds[!is_last], NULL, &file_fd));
	if (execve(data->cmd_paths[is_last], data->cmds[is_last], environ) < 0)
	{
		free_data(data);
		exit(err_return(errno, &pipe_fds[!is_last], NULL, &file_fd));
	}
}

void	do_cmds(t_data *data, char **argv)
{
	int		exit_status;
	int		child_fds[2];
	int		pipe_fds[2];

	errno = 0;
	if (pipe(pipe_fds) < 0)
		exit(err_return(errno, NULL, NULL, NULL));
	child_fds[0] = fork();
	if (child_fds[0] < 0)
		exit(err_return(errno, &pipe_fds[0], &pipe_fds[1], NULL));
	else if (!child_fds[0])
		cmd_proc(data, argv, pipe_fds, FALSE);
	child_fds[1] = fork();
	if (child_fds[1] < 0)
		exit(err_return(errno, &pipe_fds[0], &pipe_fds[1], NULL));
	else if (child_fds[1])
		cmd_proc(data, argv, pipe_fds, TRUE);
	waitpid(child_fds[1], &exit_status, 0);
	wait(NULL);
	if (WIFEXITED(exit_status)) {
		free_data(data);
		exit(WEXITSTATUS(exit_status));
	}
}