/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:09:54 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/09/24 20:26:39 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int	err_return(int err_num, int *pipe_fd0_p, int *pipe_fd1_p, int *file_fd_p)
{
	if (err_num)
		perror("");
	if (pipe_fd0_p)
		close(*pipe_fd0_p);
	if (pipe_fd1_p)
		close(*pipe_fd1_p);
	if (file_fd_p)
		close(*file_fd_p);
	return (EXIT_FAILURE);
}

static void	tail_cmd_proc(t_data *data, char **argv, int pipe_fds[2])
{
	extern char	**environ;
	int			file_fd;

	close(pipe_fds[1]);
		file_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd < 0)
	{
		ft_printf("%s: %s\n", argv[4], strerror(errno));
		exit(err_return(0, &pipe_fds[0], NULL, NULL));
	}
	data->cmd_paths[1] = search_cmd_path(data->cmds[1][0], environ);
	if (!(data->cmd_paths[1]))
		exit(err_return(0, &pipe_fds[0], NULL, &file_fd));
	if (dup2(pipe_fds[0], STDIN_FILENO) < 0)
		exit(err_return(errno, &pipe_fds[0], NULL, &file_fd));
	close(pipe_fds[0]);
	if (dup2(file_fd, STDOUT_FILENO) < 0)
		exit(err_return(errno, NULL, NULL, &file_fd));
	close(file_fd);
	if (execve(data->cmd_paths[1], data->cmds[1], environ) < 0)
	{
		free_data(data);
		exit(err_return(errno, &pipe_fds[0], NULL, &file_fd));
	}
}

static void	head_cmd_proc(t_data *data, char **argv, int pipe_fds[2])
{
	extern char	**environ;
	int			file_fd;

	close(pipe_fds[0]);
	file_fd = open(argv[1], O_RDONLY);
	if (file_fd < 0)
	{
		ft_printf("%s: %s\n", argv[1], strerror(errno));
		exit(err_return(0, &pipe_fds[1], NULL, NULL));
	}
	data->cmd_paths[0] = search_cmd_path(data->cmds[0][0], environ);
	if (!(data->cmd_paths[0]))
		exit(err_return(0, &pipe_fds[1], NULL, &file_fd));
	if (dup2(pipe_fds[1], STDOUT_FILENO) < 0)
		exit(err_return(errno, &pipe_fds[1], NULL, &file_fd));
	close(pipe_fds[1]);
	if (dup2(file_fd, STDIN_FILENO) < 0)
		exit(err_return(errno, &pipe_fds[1], NULL, &file_fd));
	close(file_fd);
	if (execve(data->cmd_paths[0], data->cmds[0], environ) < 0)
	{
		free_data(data);
		exit(err_return(errno, &pipe_fds[1], NULL, &file_fd));
	}
}

void	do_cmds(t_data *data, char **argv)
{
	int		exit_status;
	pid_t	child_pids[2];
	int		pipe_fds[2];

	errno = 0;
	if (pipe(pipe_fds) < 0)
		exit(err_return(errno, NULL, NULL, NULL));
	child_pids[0] = fork();
	if (child_pids[0] < 0)
		exit(err_return(errno, &pipe_fds[0], &pipe_fds[1], NULL));
	else if (child_pids[0] == 0)
		head_cmd_proc(data, argv, pipe_fds);
	child_pids[1] = fork();
	if (child_pids[1] < 0)
		exit(err_return(errno, &pipe_fds[0], &pipe_fds[1], NULL));
	else if (child_pids[1] == 0)
		tail_cmd_proc(data, argv, pipe_fds);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	waitpid(child_pids[0], NULL, 0);
	waitpid(child_pids[1], &exit_status, 0);
	if (WIFEXITED(exit_status)) {
		free_data(data);
		exit(WEXITSTATUS(exit_status));
	}
}