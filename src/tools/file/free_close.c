/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:09:02 by zaki              #+#    #+#             */
/*   Updated: 2023/10/19 16:31:10 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	dup_and_close(int oldfd, int newfd)
{
	dup2(oldfd, newfd);
	close(oldfd);
}

void	free_shell(t_shell *shell, char *av, int index)
{
	if (!index)
		free(av);
	if (index == 1)
		free(shell->pid);
	free_all(shell->token);
	free(shell->av);
	if (shell->nb_here && shell->here)
		free(shell->here);
}

void	close_all_pipe(t_shell *shell)
{
	close(shell->pipefd[0]);
	close(shell->pipefd[1]);
}

void	safe_close(int fd)
{
	if (close(fd) == -1)
	{
		perror("fd");
		exit(errno);
	}
}
