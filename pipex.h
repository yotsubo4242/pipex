/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:22:01 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/09/25 14:22:01 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>

# define TRUE 1
# define FALSE 0

# define CMD_NOT_FOUND -1
# define CMD_CANT_EXEC -2
# define CMD_CANT_EXEC_STS 126
# define CMD_NOT_FOUND_STS 127

typedef int	t_bool;

typedef struct s_data {
	char	***cmds;
	char	**cmd_paths;
}	t_data;

void	free_cmds(char ***cmds);

void	free_strs(char **strs);

char	**free_paths(char **paths, int paths_num);

void	free_data(t_data *data);

t_data	*data_init(int argc, char *argv[]);

char	*search_cmd_path(char *cmd_name, char **environ);

void	do_cmds(t_data *data, char **argv);

void	check_fds(char **argv);

void	output_error_message(char *detail, char *err_msg);

char	*passed_path(char *cmd_name);

int		get_paths_num(char **paths);

#endif