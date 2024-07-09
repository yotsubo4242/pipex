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

static int	err_return(t_data *data)
{
	if (data)
		free_data(data);
	return (EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = data_init(argc, argv);
	if (!data)
		return (err_return(NULL));
	do_cmds(data, argv);
	free_data(data);
	return (0);
}
