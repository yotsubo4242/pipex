/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 22:17:45 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/07/07 14:51:19 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "libft.h"

// [!] need to modify
// - close fds before program finish. ✅
// - adjust error message.

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q pipex");
// }

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

	data = make_struct(argc, argv);
	if (!data)
		return (err_return(NULL));
	if (!search_paths(data))
		return (err_return(data));
	check_fds(argv);
	cmds_res = do_cmds(data, argv);
	if (cmds_res < 0)
		return (err_return(data));
	free_data(data);
	return (0);
}
