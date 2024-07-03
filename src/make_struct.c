/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:17:42 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/06/30 22:17:42 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// [!]need to fix
// - openはforkした後にやってそう...

#include "../pipex.h"
#include "libft.h"

void	free_cmds(char ***cmds)
{
	if (!cmds)
		return ;
	if (cmds[0])
		free_strs(cmds[0]);
	if (cmds[1])
		free_strs(cmds[1]);
	free(cmds);
}

void	free_strs(char **strs)
{
	size_t	i;
	if (strs)
	{
		i = 0;
		while (strs[i])
			free(strs[i++]);
		free(strs);
	}
}

static t_data	*err_return(t_data *data)
{
	if (data && data->cmds)
		free_cmds(data->cmds);
	if (data)
		free(data);
	return (NULL);
}

static void	get_fds(char *argv[], t_data *data)
{
	int	ifd;
	int	ofd;

	ifd = open(argv[1], O_RDONLY);
	if (ifd < 0)
		ft_printf("%s: %s\n", argv[1], strerror(errno));
	ofd = open(argv[4], O_WRONLY | O_CREAT, 0644);
	if (ofd < 0)
	{
		ft_printf("%s: %s\n", argv[4], strerror(errno));
		return ;
	}
	data->infile_fd = ifd;
	data->outfile_fd = ofd;
	return ;
}

static t_bool get_cmds(char *argv[], t_data *data)
{
	data->cmds = (char ***)malloc(sizeof(char **) * 2);
	if (!data->cmds)
		return (FALSE);
	ft_bzero(data->cmds, sizeof(char *) * 2);
	data->cmds[0] = ft_split(argv[2], ' ');
	if (!data->cmds[0])
		return (FALSE);
	data->cmds[1] = ft_split(argv[3], ' ');
	if (!data->cmds[1])
	{
		free_strs(data->cmds[0]);
		return (FALSE);
	}
	return (TRUE);
}

t_data	*make_struct(int argc, char *argv[])
{
	t_data	*data;

	if (argc != 5)
		return (err_return(NULL));
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (err_return(NULL));
	ft_bzero(data, sizeof(t_data));
	get_fds(argv, data);
	if (!get_cmds(argv, data))
		return (err_return(data));
	return (data);
}