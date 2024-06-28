#include "libft.h"
#include "../pipex.h"

static char	**free_paths(char **paths, int paths_num)
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

static int	get_paths_num(char **paths)
{
	int	paths_num;

	paths_num = 0;
	while (paths[paths_num])
		paths_num++;
	return (paths_num);
}

static char	**get_paths(void)
{
	extern char	**environ;
	char		**paths;

	while (*environ)
	{
		if (!ft_strncmp(*environ, "PATH=", ft_strlen("PATH=")))
		{
			paths = ft_split((*environ) + ft_strlen("PATH="), ':');
			if (!paths)
				return (NULL);
			return (paths);
		}
		(*environ)++;
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

t_bool	get_abs_paths(t_data *data, char **paths)
{
	t_bool	first_cmd_flag;
	t_bool	second_cmd_flag;
	char	*tmp1;
	char	*tmp2;

	first_cmd_flag = FALSE;
	second_cmd_flag = FALSE;
	while (*paths)
	{
		tmp1 = ft_strjoin(*paths, data->cmds[0]);
		if (!tmp1)
			return (FALSE);
		tmp2 = ft_strjoin(*paths, data->cmds[1]);
		if (!tmp2)
		{
			free(tmp1);
			return (FALSE);
		}
		if (!access(tmp1, X_OK))
		{
			first_cmd_flag = TRUE;
			data->cmds[0] = map_and_free(ft_strjoin(*paths, data->cmds[0]), data->cmds[0]);
		}
		if (!access(tmp2, X_OK))
		{
			second_cmd_flag = TRUE;
			data->cmds[1] = map_and_free(ft_strjoin(*paths, data->cmds[1]), data->cmds[1]);
		}
		free(tmp1);
		free(tmp2);
		paths++;
	}
	if (!first_cmd_flag || !second_cmd_flag)
		return (FALSE);
	return (TRUE);
}

t_bool	search_paths(t_data *data)
{
	char **paths;

	paths = get_paths();
	if (!paths)
		return (FALSE);
	paths = adjust_paths(paths);
	if (!paths)
		return (FALSE);
	for (int i = 0; paths[i]; i++)
		printf("paths[%d]: %s\n", i, paths[i]);
	if (!get_abs_paths(data, paths))
	{
		free_paths(paths, get_paths_num(paths));
		return (FALSE);
	}
	free_paths(paths, get_paths_num(paths));
	return (TRUE);
}