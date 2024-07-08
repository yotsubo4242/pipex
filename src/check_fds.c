/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuotsubo <yuotsubo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 16:56:27 by yuotsubo          #+#    #+#             */
/*   Updated: 2024/07/08 21:43:36 by yuotsubo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include "libft.h"

void	check_fds(char **argv)
{
	int	infile_fd;
	int	outfile_fd;

	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd < 0)
		ft_printf("%s: %s\n", argv[1], strerror(errno));
	else
		close(infile_fd);
	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
		ft_printf("%s: %s\n", argv[4], strerror(errno));
	else
		close(outfile_fd);
}
