/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 03:13:43 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/14 14:43:22 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_process(t_shell *shell, int i, char ***env)
{
	if (pipe(shell->pipefd) == -1)
		return (-1);
	signal(SIGINT, &handler_cmd);
	shell->pid[i] = fork();
	if (shell->pid[i] == -1)
	{
		close_all_pipe(shell);
		return (-1);
	}
	if (shell->pid[i] == 0)
		child_process(shell, i, env);
	else if (shell->pid[i] > 0)
		parent_process(shell);
	return (0);
}

int	exec_pipex(t_shell *shell, char ***env)
{
	int	i;

	i = 0;
	while (i < (shell->nb_cmd))
	{
		if (exec_process(shell, i, env) == -1)
			return (-1);
		if (shell->nb_here && strstr(shell->token[i], "<<"))
			shell->c_here++;
		i++;
	}
	return (0);
}

int	pipex(t_shell *shell, char *av, char ***env)
{
	free(av);
	if (create_here(shell) == -1)
		return (-1);
	if (init_here(shell, *env) == -1)
		return (-1);
	if (exec_pipex(shell, env) == -1)
	{
		free_shell(shell, NULL, 1);
		return (-1);
	}
	return (0);
}
