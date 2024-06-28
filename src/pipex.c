#include "../pipex.h"
#include "libft.h"

static void	free_data(t_data *data)
{
	if (data && data->cmds)
		free_cmds(data->cmds);
	if (data && data->cmd_paths)
		free_paths(data->cmd_paths, 2);
	if (data)
		free(data);
}

static int	err_return(t_data *data, int err_num)
{
	if (data)
		free_data(data);
	if (err_num == INPUT_ERR)
		ft_putendl_fd("ERROR: input", STDERR_FILENO);
	if (err_num == CMD_NOT_FOUND)
		ft_putendl_fd("ERROR: command not found", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = make_struct(argc, argv);
	if (!data)
		return (err_return(NULL, INPUT_ERR));
	if (!search_paths(data))
		return (err_return(data, CMD_NOT_FOUND));
	for (int i = 0; i < 2 ; i++)
	{
		for (int j = 0; data->cmds[i][j]; j++)
			printf("cmds[%d][%d]: %s\n", i, j, data->cmds[i][j]);
	}
	printf("cmd_paths[0]: %s\n", data->cmd_paths[0]);
	printf("cmd_paths[1]: %s\n", data->cmd_paths[1]);
	free_data(data);
	return (0);
}