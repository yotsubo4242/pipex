/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:17:45 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/07/08 21:02:40 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "libft.h"

static void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->cmds)
		free_cmds(data->cmds);
	if (data->cmd_paths)
		free_paths(data->cmd_paths, 2);
	if (data)
		free(data);
}

static int	err_return(t_data *data)
{
	if (data)
		free_data(data);
	return (EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	int		cmds_res;

	data = check_input(argc, argv);
	if (!data)
		return (err_return(NULL));
	check_fds(argv);
	if (!search_paths(data))
		return (err_return(data));
	cmds_res = do_cmds(data, argv);
	if (cmds_res < 0)
		return (err_return(data));
	free_data(data);
	return (0);
}
