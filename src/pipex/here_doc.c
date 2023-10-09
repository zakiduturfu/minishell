/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:51:50 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/09 14:17:33 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_here(t_shell *shell)
{
	if (shell->nb_here == 0)
		return (0);
	shell->here = malloc(sizeof(t_here) * shell->nb_here);
	if (!shell->here)
	{
		free_shell(shell, NULL, 1);
		return (-1);
	}
	return (0);
}

void	file_here(int i, t_here *here)
{
	char	*s;

	while (1)
	{
		s = readline("here_doc>");
		if (!s)
		{
			printf("oulala la catastrophe\n");
			break ;
		}
		else if (!ft_strcmp(s, here[i].lim))
		{
			free(s);
			break ;
		}
		else
		{
			ft_putendl_fd(s, here[i].here_pipe[1]);
			free(s);
		}
	}	
	close(here[i].here_pipe[0]);
	close(here[i].here_pipe[1]);
}

int	exec_here(t_shell *shell, char **env)
{
	int		i;
	pid_t	pid;

	i = -1;
	if (recup_delim1(shell) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
		child_here(shell, env);
	else if (pid > 0)
	{
		while (++i < shell->nb_here)
		{
			free(shell->here[i].lim);
			close(shell->here[i].here_pipe[1]);
		}
	}
	waitpid(pid, NULL, 0);
	return (1);
}

int	init_here(t_shell *shell, char **env)
{
	if (shell->nb_here)
	{
		if (exec_here(shell, env) == -1)
		{
			free(shell->here);
			free_shell(shell, NULL, 1);
			return (-1);
		}
	}
	return (1);
}
