/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:58:34 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/07/09 18:59:39 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "libft.h"

void	free_data(t_data *data)
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

char	**free_paths(char **paths, int paths_num)
{
	size_t	i;

	if (paths)
	{
		i = 0;
		while (i < (size_t)paths_num)
		{
			if (paths[i])
				free(paths[i]);
			i++;
		}
		free(paths);
	}
	return (NULL);
}