/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 03:13:43 by zlemery           #+#    #+#             */
/*   Updated: 2023/08/25 16:52:44 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_process(t_shell *shell, int i, char *av, char **env)
{
	if (pipe(shell->pipefd) == -1)
		return (-1);
	shell->pid[i] = fork();
	if (shell->pid[i] == -1)
		return (-1);
	if (shell->pid[i] == 0)
		child_process(shell, i, av, env);
	else if (shell->pid[i] > 0)
		parent_process(shell);
	return (0);
}

int	exec_pipex(t_shell *shell, char *av, char **env)
{
	int	i;

	i = -1;
	while (++i < (shell->nb_cmd))
	{
		if (exec_process(shell, i, av, env) == -1)
			return (-1);
	}
	return (0);
}

int	pipex(t_shell *shell, char *av, char **env)
{
	if (exec_pipex(shell, av, env) == -1)
		return (-1);
	return (0);
}
