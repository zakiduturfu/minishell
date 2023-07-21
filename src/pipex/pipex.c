/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 03:13:43 by zlemery           #+#    #+#             */
/*   Updated: 2023/07/21 04:54:25 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_process(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < shell->nb_cmd -1)
	{
		if (exec_child(shell) == -1)
			return (-1);
	}
}


int	exec_pipex(t_shell *shell)
{
	if (here_alloc(shell) == -1)
		return (-1);
	if (exec_hd(shell) == -1)
		return (-1);
	if (exec_process(shell) == -1)
		return (-1);
	return (0);
}