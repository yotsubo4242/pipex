#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define TRUE 1
# define FALSE 0

# define INPUT_ERR -1

typedef int t_bool;

typedef struct s_data {
	int	cmd_num;
	int infile_fd;
	int	outfile_fd;
	char **cmds;
}	t_data;

#endif