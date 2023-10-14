/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:17:32 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/14 14:49:29 by zlemery          ###   ########.fr       */
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
	perror(file);
	free_all(cmd);
	free_env_tab(env);
	free_shell(shell, NULL, 2);
	exit(1);
}

void	open_fdin(t_shell *shell, char **cmd, int i, char **env)
{
	shell->fdin = open(cmd[i + 1], O_RDONLY);
	if (shell->fdin == -1)
		file_error(cmd[i + 1], cmd, shell, env);
}

void	open_fdout(t_shell *shell, char **cmd, int i, char **env)
{
	if (is_redir(cmd[i]) == 1)
		shell->fdout = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (is_redir(cmd[i]) == 3)
		shell->fdout = open(cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (shell->fdout == -1)
		file_error(cmd[i + 1], cmd, shell, env);
}

void	open_redir(t_shell *shell, char **cmd, int i, char **env)
{
	int	redir;

	redir = is_redir(cmd[i]);
	if (redir == 1 || redir == 3)
		open_fdout(shell, cmd, i, env);
	if (redir == 2)
		open_fdin(shell, cmd, i, env);
	if (redir == 4)
		dup_and_close(shell->here[shell->c_here].here_pipe[0], STDIN_FILENO);
	if (redir == 1 || redir == 3)
		dup_and_close(shell->fdout, STDOUT_FILENO);
	if (redir == 2)
		dup_and_close(shell->fdin, STDIN_FILENO);
}

void	find_redir(t_shell *shell, char **cmd, int j, char **env)
{
	int	i;

	i = 0;
	if (shell->index != 0)
		dup_and_close(shell->prev_pipe, STDIN_FILENO);
	if (shell->index != shell->nb_cmd - 1)
		dup2(shell->pipefd[1], STDOUT_FILENO);
	if (j > 0)
	{
		close(shell->pipefd[0]);
		close(shell->pipefd[1]);
	}
	while (cmd[i])
	{
		open_redir(shell, cmd, i, env);
		i++;
	}
	i = -1;
	while (++i < shell->nb_here)
		close(shell->here[i].here_pipe[0]);
}
