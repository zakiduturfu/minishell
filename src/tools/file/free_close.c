/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:09:02 by zaki              #+#    #+#             */
/*   Updated: 2023/10/02 15:46:28 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_shell(t_shell *shell, char *av)
{
	free(av);
	free(shell->pid);
	free_all(shell->token);
	free(shell->av);
	if (shell->nb_here && shell->here)
		free(shell->here);
	free(shell);
}

void	close_all_pipe(t_shell *shell)
{
	close(shell->pipefd[0]);
	close(shell->pipefd[1]);
}
