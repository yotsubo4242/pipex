/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:09:54 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/14 11:31:14 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

// execve()を用いることでコマンド等を実行できる. 
// ただし, execve()が成功すると, プロセスがそのコマンドに上書きされてしまうため, 子プロセスの中でコマンドを実行する(execve()をする)ようにしている. 
// ファイルは下から読むことを推奨. 

// エラー処理用の関数. 
static int	err_return(int err_num, int *pipe_fd0_p, \
						int *pipe_fd1_p, int *file_fd_p)
{
	if (err_num > 0)
		output_error_message(NULL, strerror(err_num));
	if (pipe_fd0_p)
		close(*pipe_fd0_p);
	if (pipe_fd1_p)
		close(*pipe_fd1_p);
	if (file_fd_p)
		close(*file_fd_p);
	if (err_num == CMD_NOT_FOUND)
		return (CMD_NOT_FOUND_STS);
	if (err_num == CMD_CANT_EXEC)
		return (CMD_CANT_EXEC_STS);
	return (EXIT_FAILURE);
}

// 最後のコマンド（一番右のコマンド）を実行するための関数. 
// 二回目のfork()で作成された子プロセスがこの関数に飛ばされる. 
// outfileのopen(), 入力から渡されたコマンドが存在するかの確認, dup2()を用いてfdの置き換え, execve()を用いてコマンドの実行, を行っている. 
// 処理の順序はbashの挙動に合わせている.  
static void	tail_cmd_proc(t_data *data, char **argv, int pipe_fds[2])
{
	// 環境変数が格納されている環境変数. 
	extern char	**environ;
	int			file_fd;

	// 最後の子プロセスではpipe_fds[1]は使用しないためclose.
	close(pipe_fds[1]);
	// outfileをopenする. (なければ権限644で作成, 存在する場合は上書きされるように開く)
	file_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd < 0)
	{
		output_error_message(argv[4], strerror(errno));
		exit(err_return(0, &pipe_fds[0], NULL, NULL));
	}
	// 入力から渡されたコマンドが存在するか(実行可能かどうかはここでは判断しない)確認する. 
	data->cmd_paths[1] = search_cmd_path(data->cmds[1][0], environ);
	if (!(data->cmd_paths[1]))
		exit(err_return(CMD_NOT_FOUND, &pipe_fds[0], NULL, &file_fd));
	// pipe_fds[0]をSTDIN_FILENOに置き換える. 
	if (dup2(pipe_fds[0], STDIN_FILENO) < 0)
		exit(err_return(errno, &pipe_fds[0], NULL, &file_fd));
	close(pipe_fds[0]);
	// outfileのfdをSTDOUT_FILENOに置き換える.
	if (dup2(file_fd, STDOUT_FILENO) < 0)
		exit(err_return(errno, NULL, NULL, &file_fd));
	close(file_fd);
	// コマンドの実行. 
	if (execve(data->cmd_paths[1], data->cmds[1], environ) < 0)
	{
		free_data(data);
		exit(err_return(CMD_CANT_EXEC, &pipe_fds[0], NULL, &file_fd));
	}
}

// 1つ目のコマンド（一番左のコマンド）を実行するための関数. 
// 一回目のfork()で作成された子プロセスがこの関数に飛ばされる. 
// infileのopen(), 入力から渡されたコマンドが存在するかの確認, dup2()を用いてfdの置き換え, execve()を用いてコマンドの実行, を行っている. 
// 処理の順序はbashの挙動に合わせている.  
static void	head_cmd_proc(t_data *data, char **argv, int pipe_fds[2])
{
	// 環境変数が格納されている環境変数. 
	extern char	**environ;
	int			file_fd;

	// 最初の子プロセスではpipe_fds[0]は使用しないためclose()する. 
	close(pipe_fds[0]);
	file_fd = open(argv[1], O_RDONLY);
	if (file_fd < 0)
	{
		output_error_message(argv[1], strerror(errno));
		exit(err_return(0, &pipe_fds[1], NULL, NULL));
	}
	// 入力から渡されたコマンドが存在するか(実行可能かどうかはここでは判断しない)確認する. 
	data->cmd_paths[0] = search_cmd_path(data->cmds[0][0], environ);
	if (!(data->cmd_paths[0]))
		exit(err_return(0, &pipe_fds[1], NULL, &file_fd));
	// pipe_fds[1]をSTDOUT_FILENOに置き換える. 
	if (dup2(pipe_fds[1], STDOUT_FILENO) < 0)
		exit(err_return(errno, &pipe_fds[1], NULL, &file_fd));
	close(pipe_fds[1]);
	// infileのfdをSTDIN_FILENOに置き換える. 
	if (dup2(file_fd, STDIN_FILENO) < 0)
		exit(err_return(errno, &pipe_fds[1], NULL, &file_fd));
	close(file_fd);
	// コマンドの実行. 
	if (execve(data->cmd_paths[0], data->cmds[0], environ) < 0)
	{
		free_data(data);
		exit(err_return(errno, &pipe_fds[1], NULL, &file_fd));
	}
}

// main()から呼ばれる関数. 
// pipeを作成し, コマンドを実行するための子プロセスをコマンドの数だけ作り, 
// 子プロセスの終了を待って, 最後に作成された子プロセスのexit_statusを返す関数. 
void	do_cmds(t_data *data, char **argv)
{
	int		exit_status;
	pid_t	child_pids[2];
	int		pipe_fds[2];

	// pipeの作成. 
	if (pipe(pipe_fds) < 0)
		exit(err_return(errno, NULL, NULL, NULL));
	// 1つ目の子プロセス（一番左のコマンドを実行するためのプロセス）を作成. 
	child_pids[0] = fork();
	if (child_pids[0] < 0)
		exit(err_return(errno, &pipe_fds[0], &pipe_fds[1], NULL));
	else if (!child_pids[0])
		head_cmd_proc(data, argv, pipe_fds);
	// 2つ目の子プロセス（一番右のコマンドを実行するためのプロセス）を作成. 
	child_pids[1] = fork();
	if (child_pids[1] < 0)
		exit(err_return(errno, &pipe_fds[0], &pipe_fds[1], NULL));
	else if (!child_pids[1])
		tail_cmd_proc(data, argv, pipe_fds);
	// 親プロセスではpipeは使用ないためcloseする. 
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	// 子プロセスの終了を待ち, 最後に作成された子プロセスのexit_statusを受け取る. 
	waitpid(child_pids[0], NULL, 0);
	waitpid(child_pids[1], &exit_status, 0);
	// wait_pid()で受け取ったexut_statusはそのままでは終了ステータスとして使用できないため, マクロ関数を挟む. 
	if (WIFEXITED(exit_status))
	{
		free_data(data);
		exit(WEXITSTATUS(exit_status));
	}
}
