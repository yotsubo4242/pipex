#include "../pipex.h"
#include "libft.h"

static void	free_data(t_data *data)
{
	if (data && data->cmds)
		free_cmds(data->cmds);
	if (data)
		free(data);
}

static int	err_return(int err_num)
{
	if (err_num == INPUT_ERR)
		ft_putendl_fd("ERROR: input", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = make_struct(argc, argv);
	if (!data)
		return (err_return(INPUT_ERR));
	printf("cmds[0]: %s\n", data->cmds[0]);
	printf("cmds[1]: %s\n", data->cmds[1]);
	free_data(data);
	return (0);
}