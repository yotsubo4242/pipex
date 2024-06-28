#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define TRUE 1
# define FALSE 0

# define INPUT_ERR -1
# define CMD_NOT_FOUND -2

typedef int t_bool;

typedef struct s_data {
	int		infile_fd;
	int		outfile_fd;
	char	***cmds;
	char	**cmd_paths;
}	t_data;

void	free_cmds(char ***cmds);

void	free_strs(char **strs);

char	**free_paths(char **paths, int paths_num);

t_data	*make_struct(int argc, char *argv[]);

t_bool	search_paths(t_data *data);

#endif