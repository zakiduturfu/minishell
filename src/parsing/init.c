/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaki <zaki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:30:26 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/09 21:33:53 by zaki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_shell	*create_data(void)
{
	static t_shell	shell;

	return (&shell);
}

int	init_struct(t_shell *shell, char *av)
{
	shell->fdout = 0;
	shell->c_here = 0;
	shell->fdin = 0;
	shell->prev_pipe = -1;
	shell->token = ft_split(av, '|');
	if (!shell->token)
		return (-1);
	shell->av = ft_strdup(av);
	if (!shell->av)
	{
		free_all(shell->token);
		return (-1);
	}
	shell->nb_cmd = count_cmd(shell->token);
	if (shell->nb_cmd)
		shell->pid = malloc(sizeof(int) * shell->nb_cmd);
	if (!shell->pid)
	{
		free(shell->av);
		free_all(shell->token);
		return (-1);
	}
	shell->nb_here = nb_heredoc(av);
	return (0);
}
