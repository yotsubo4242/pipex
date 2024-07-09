/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:46:59 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/07/09 21:51:27 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "libft.h"

static int	get_paths_num(char **paths)
{
	int	paths_num;

	paths_num = 0;
	while (paths[paths_num])
		paths_num++;
	return (paths_num);
}

static t_bool	is_relative_path(char *cmd_name)
{
	if (!ft_strncmp(cmd_name, "./", ft_strlen("./")))
		return (TRUE);
	if (!ft_strncmp(cmd_name, "../", ft_strlen("../")))
		return (TRUE);
	return (FALSE);
}

static char	**get_paths(char **environ)
{
	char		**paths;

	if (!environ)
		return (NULL);
	while (*environ)
	{
		if (!ft_strncmp(*environ, "PATH=", ft_strlen("PATH=")))
		{
			paths = ft_split((*environ) + ft_strlen("PATH="), ':');
			if (!paths)
				return (NULL);
			return (paths);
		}
		environ++;
	}
	return (NULL);
}

static char	**adjust_paths(char **paths)
{
	int		paths_num;
	int		i;
	char	*tmp;
	size_t	path_len;

	paths_num = get_paths_num(paths);
	i = 0;
	while (paths[i])
	{
		path_len = ft_strlen(paths[i]);
		if (paths[i][path_len - 1] != '/')
		{
			tmp = (char *)malloc(sizeof(char) * (path_len + 2));
			if (!tmp)
				return (free_paths(paths, paths_num));
			ft_strlcpy(tmp, paths[i], path_len + 2);
			tmp[path_len] = '/';
			tmp[path_len + 1] = '\0';
			free(paths[i]);
			paths[i] = tmp;
		}
		i++;
	}
	return (paths);
}

static char	*get_cmd_path(char *cmd_name, char **paths)
{
	char	*tmp;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, cmd_name);
		if (!tmp)
			return (NULL);
		if (!access(tmp, X_OK | F_OK))
			return (tmp);
		free(tmp);
		paths++;
	}
	return (NULL);
}

char	*search_cmd_path(char *cmd_name, char **environ)
{
	char	**paths;
	char	*res;

	if (!access(cmd_name, X_OK | F_OK))
	{
		res = ft_strdup(cmd_name);
		return (res);
	}
	if (is_relative_path(cmd_name))
		return (NULL);
	paths = get_paths(environ);
	if (!paths)
		return (NULL);
	adjust_paths(paths);
	if (!paths)
		return (NULL);
	res = get_cmd_path(cmd_name, paths);
	free_paths(paths, get_paths_num(paths));
	return (res);
}
