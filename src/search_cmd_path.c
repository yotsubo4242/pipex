/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:48:14 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/10/14 11:53:35 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

// 渡されたコマンドのpathを探す機能のファイル. 
// コマンドのpathは環境変数PATH内にあるパスから探す. 
// ファイルは下から読んでいくことを推奨. 

// 環境変数PATHからコマンドが使用可能なパスを取ってくる関数. 
static char	**get_paths(char **environ)
{
	char		**paths;

	if (!environ)
		return (NULL);
	while (*environ)
	{
		// environの中からPATHが格納されている場所を探し, そこから':'区切りでパスを取る.
		// (PATHの中身に関しては, `echo $PATH`などを参照) 
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

// /usr/binなどの末尾に'/'がなければ追加し, コマンドをそのまま取り付けられるようにする関数. 
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

// pathsに格納されているパスたちの末尾に, 入力から受け取ったコマンドを追加し,
// そのパスが存在したらそれを返し(/usr/bin/lsなど), どのパスでも存在しなかったらNULLを返す関数. 
static char	*get_cmd_path(char *cmd_name, char **paths)
{
	char	*tmp;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, cmd_name);
		if (!tmp)
			return (NULL);
		// access()を用いて, そのパスが存在しているかを確認(F_OK).
		// bashの挙動に合わせて, ここではそのパスが実行可能かどうかは判断しない(X_OK).
		if (!access(tmp, F_OK))
			return (tmp);
		free(tmp);
		paths++;
	}
	return (NULL);
}

// 渡されたコマンドのpathが存在している場合はそのpathを返し, 
// 存在していない場合はNULLを返す関数. 
// bashの挙動に合わせ, 渡されたコマンドに'/'が含まれている場合と, 
// '/'が含まれていない場合で処理を分けている. 
char	*search_cmd_path(char *cmd_name, char **environ)
{
	char	**paths;
	char	*res;

	// '/'が含まれている場合は, 実行可能pathがそのまま渡されていることを想定し, 
	// 渡されてきたpathをそのままaccess()に渡して存在しているかどうかを判断する. 
	if (ft_strchr(cmd_name, '/'))
	{
		res = passed_path(cmd_name);
		if (!res)
			output_error_message(cmd_name, "No such file or directory");
		return (res);
	}
	// 環境変数PATHからコマンドが使用できるパスたちを取ってきてpathsに格納する. (/usr/binなど)
	paths = get_paths(environ);
	if (!paths)
		return (NULL);
	// 環境変数PATHから取ってきたpathたちの末尾に'/'を追加する. (/usr/bin/など)
	adjust_paths(paths);
	if (!paths)
		return (NULL);
	// pathsに格納されているパスたちの末尾に, 入力から受け取ったコマンドを追加し,
	// そのパスが存在したらresに格納する(/usr/bin/lsなど). どのパスでも存在しなかったらNULLとなる. 
	res = get_cmd_path(cmd_name, paths);
	if (!res)
		output_error_message(cmd_name, "command not found");
	// pathsのfree
	free_paths(paths, get_paths_num(paths));
	return (res);
}
