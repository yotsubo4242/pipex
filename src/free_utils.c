/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:58:34 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/07/09 20:13:49 by yuotsubo         ###   ########.fr       */
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
