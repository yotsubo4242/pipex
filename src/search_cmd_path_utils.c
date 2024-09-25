/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd_path_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:18:40 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/09/25 14:21:26 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int	get_paths_num(char **paths)
{
	int	paths_num;

	paths_num = 0;
	while (paths[paths_num])
		paths_num++;
	return (paths_num);
}

char	*passed_path(char *cmd_name)
{
	char	*res;

	res = NULL;
	if (!access(cmd_name, F_OK))
		res = ft_strdup(cmd_name);
	return (res);
}
