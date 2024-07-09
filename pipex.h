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

typedef int t_bool;

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

#endif