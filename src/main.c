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

#include "pipex.h"
#include "libft.h"

// プログラムのメインとなるファイル：main.c, data_init.c, do_cmds.c, search_cmd_path.c
// それらの補助となるファイル：error_message.c, free_utils.c, search_cmd_path_utils.c

static int	err_return(t_data *data)
{
	if (data)
		free_data(data);
	return (EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	// inputから構造体の初期化
	data = data_init(argc, argv);
	if (!data)
		return (err_return(NULL));
	// コマンドの実行
	do_cmds(data, argv);
	// cleanup
	free_data(data);
	return (0);
}
