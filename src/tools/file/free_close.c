/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:09:02 by zaki              #+#    #+#             */
/*   Updated: 2023/10/09 14:09:50 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_shell(t_shell *shell, char *av, int index)
{
	if (!index)
		free(av);
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
