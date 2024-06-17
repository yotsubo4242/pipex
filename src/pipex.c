#include "../pipex.h"
#include "libft.h"

int	err_return(int err_num)
{
	if (err_num == INPUT_ERR)
		ft_putendl_fd("ERROR: input");
	return (EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = cmd_count(argc, argv);
	if (!data)
		return (err_return(INPUT_ERR));
}