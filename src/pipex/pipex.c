/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 03:13:43 by zlemery           #+#    #+#             */
/*   Updated: 2023/07/22 04:05:39 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_process(t_shell *shell)
{
	
}

int	exec(t_shell *shell, int i)
{
	if (pipe(shell->pipefd) == -1)
		return (-1);
	shell->pid[i] = fork();
	if (shell->pid[i] == -1)
		return (-1);
	if (!shell->pid)
		child_process(shell);
	else if (shell->pid > 0)
		parent_process(shell);
	return (0);
}


int	exec_process(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < (shell->nb_cmd + shell->here) - 1)
	{
		if (exec(shell, i) == -1)
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

void	dup_and_close(int oldfd, int newfd)
{
	dup2(oldfd, newfd);
	close(oldfd);
}