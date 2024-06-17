#include "../pipex.h"
#include "libft.h"

t_bool	get_fds(int argc, char *argv[], t_data *data)
{
	int	ifd;
	int	ofd;

	ifd = open(argv[1], O_RDONLY);
	if (ifd < 0)
	{
		ft_printf("ERROR: can't opent the file: %s\n", argv[1]);
		return (FALSE);
	}
	ofd = open(argv[argc - 1], O_WRONLY);
	if (ofd < 0)
	{
		ft_printf("ERROR: can't opent the file: %s\n", argv[argc - 1]);
		return (FALSE);
	}
	data->infile_fd = ifd;
	data->outfile_fd = ofd;
	return (TRUE);
}

t_data	*make_struct(int argc, char *argv[])
{
	t_data	*data;

	if (argc < 5)
		return (NULL);
	if (!get_fds(argc, argv, data))
		return (0);
}