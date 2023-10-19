/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:17:32 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/19 14:46:18 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

void	dup_and_close(int oldfd, int newfd)
{
	dup2(oldfd, newfd);
	close(oldfd);
}

void	file_error(char *file, char **cmd, t_shell *shell, char **env)
{
	int	i;

	i = -1;
	perror(file);
	if (shell->nb_cmd == 1 && find_built(shell, env, 0))
		return ;
	else
	{
		while (++i < shell->nb_here)
			close(shell->here[i].here_pipe[0]);
		free_all(cmd);
		free_env_tab(env);
		free_shell(shell, NULL, 2);
		exit(1);
	}
}

int	open_fdin(t_shell *shell, char **cmd, int i, char **env)
{
	shell->fdin = open(cmd[i + 1], O_RDONLY);
	if (shell->fdin == -1)
	{
		file_error(cmd[i + 1], cmd, shell, env);
		return (-1);
	}
	return (1);
}

int	open_fdout(t_shell *shell, char **cmd, int i, char **env)
{
	if (is_redir(cmd[i]) == 1)
		shell->fdout = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (is_redir(cmd[i]) == 3)
		shell->fdout = open(cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (shell->fdout == -1)
	{
		file_error(cmd[i + 1], cmd, shell, env);
		return (-1);
	}
	return (1);
}

int	open_redir(t_shell *shell, char **cmd, int i, char **env)
{
	int	redir;

	redir = is_redir(cmd[i]);
	if (redir == 1 || redir == 3)
	{
		if (open_fdout(shell, cmd, i, env) == -1)
			return (-1);
	}
	if (redir == 2)
	{
		if (open_fdin(shell, cmd, i, env) == -1)
			return (-1);
	}
	if (redir == 4)
		dup_and_close(shell->here[shell->c_here].here_pipe[0], STDIN_FILENO);
	if (redir == 1 || redir == 3)
		dup_and_close(shell->fdout, STDOUT_FILENO);
	if (redir == 2)
		dup_and_close(shell->fdin, STDIN_FILENO);
	return (1);
}

int	find_redir(t_shell *shell, char **cmd, int j, char **env)
{
	int	i;

	i = 0;
	if (shell->index != 0)
		dup_and_close(shell->prev_pipe, STDIN_FILENO);
	if (shell->index != shell->nb_cmd - 1)
		dup2(shell->pipefd[1], STDOUT_FILENO);
	if (j > 1)
	{
		close(shell->pipefd[0]);
		close(shell->pipefd[1]);
	}
	while (cmd[i])
	{
		if (open_redir(shell, cmd, i, env) == -1)
			return (-1);
		i++;
	}
	i = -1;
	while (++i < shell->nb_here)
		close(shell->here[i].here_pipe[0]);
	return (1);
}
