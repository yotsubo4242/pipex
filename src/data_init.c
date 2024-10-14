/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:11:59 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/07/09 20:11:59 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

// data_init()では、cmdsのみを設定し、cmd_pathsはdo_cmds()内で設定。

static t_data	*err_return(t_data *data)
{
	if (data)
		free_data(data);
	return (NULL);
}

// cmdsのmallocをした後,
// ft_split()を用いてcmds[0]には{"ls", "-a"}, cmds[1]には{"grep", "-v, ".c"}などのように格納. 
static t_bool	get_cmds(char *argv[], t_data *data)
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

// 構造体自体や後に設定するcmd_pathsのmalloc.
// get_cmds()にて, cmdsのmallocと設定を行う.
t_data	*data_init(int argc, char *argv[])
{
	t_data	*data;

	if (argc != 5 || !argv[2][0] || !argv[3][0])
	{
		ft_printf("Usage: ./pipex <infile> <first cmd>");
		ft_printf(" <second cmd> <outfile>\n");
		return (err_return(NULL));
	}
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (err_return(NULL));
	ft_bzero(data, sizeof(t_data));
	data->cmd_paths = (char **)malloc(sizeof(char *) * 2);
	if (!(data->cmd_paths))
		return (err_return(data));
	ft_bzero(data->cmd_paths, sizeof(char *) * 2);
	if (!get_cmds(argv, data))
		return (err_return(data));
	return (data);
}
