/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaki <zaki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:17:32 by zlemery           #+#    #+#             */
/*   Updated: 2023/09/14 14:54:56 by zaki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

void	dup_and_close(int oldfd, int newfd)
{
	dup2(oldfd, newfd);
	close(oldfd);
}

void	open_fdin(t_shell *shell, char **cmd, int i)
{
	shell->fdin = open(cmd[i + 1], O_RDONLY);
	if (shell->fdin == -1)
		ft_putstr_fd("infile: no such file or directory", 2);
}

void	open_fdout(t_shell *shell, char **cmd, int i)
{
	if (is_redir(cmd[i]) == 1)
		shell->fdout = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (is_redir(cmd[i]) == 3)
		shell->fdout = open(cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (shell->fdout == -1)
		ft_putstr_fd("outfile: no such file or directory", 2);
}

void	open_redir(t_shell *shell, char **cmd, int i)
{
	int	redir;

	redir = is_redir(cmd[i]);
	if (redir == 1 || redir == 3)
		open_fdout(shell, cmd, i);
	if (redir == 2)
		open_fdin(shell, cmd, i);
	if (redir == 4)
		dup_and_close(shell->here[shell->c_here].here_pipe[0], STDIN_FILENO);
	if (redir == 1 || redir == 3)
		dup_and_close(shell->fdout, STDOUT_FILENO);
	if (redir == 2)
		dup_and_close(shell->fdin, STDIN_FILENO);
}

void	find_redir(t_shell *shell, char **cmd, int j)
{
	int	i;

	i = 0;
//	printf("%s %d prev%d fd0%d, ==%d\n", cmd[0], shell->index, shell->prev_pipe, shell->pipefd[0], shell->index != shell->nb_cmd - 1);
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
		open_redir(shell, cmd, i);
		i++;
	}	i = -1;
	while (++i < shell->nb_here)
		close(shell->here[i].here_pipe[0]);
}