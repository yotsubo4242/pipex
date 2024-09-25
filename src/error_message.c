/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:17:39 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/09/25 14:18:09 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

static char	*make_error_message(char *detail, char *err_msg)
{
	char	*res;

	if (!detail)
	{
		res = ft_strdup(err_msg);
		return (res);
	}
	res = (char *)malloc(ft_strlen(detail) + ft_strlen(err_msg) + 4);
	if (!res)
		return (NULL);
	ft_strlcpy(res, detail, ft_strlen(detail) + 1);
	res[ft_strlen(detail)] = ':';
	res[ft_strlen(detail) + 1] = ' ';
	ft_strlcpy(&res[ft_strlen(detail) + 2], err_msg, \
				ft_strlen(err_msg) + 1);
	res[ft_strlen(detail) + ft_strlen(err_msg) + 2] = '\n';
	res[ft_strlen(detail) + ft_strlen(err_msg) + 3] = '\0';
	return (res);
}

void	output_error_message(char *detail, char *err_msg)
{
	if (!detail && !err_msg)
		return ;
	err_msg = make_error_message(detail, err_msg);
	if (!err_msg)
		return ;
	write(STDOUT_FILENO, err_msg, ft_strlen(err_msg));
	free(err_msg);
}
