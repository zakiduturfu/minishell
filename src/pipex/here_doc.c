/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:51:50 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/02 15:54:05 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_here(t_shell *shell, char *av)
{
	if (shell->nb_here == 0)
		return (0);
	shell->here = malloc(sizeof(t_here) * shell->nb_here);
	if (!shell->here)
	{
		free_shell(shell, av);
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

void	child_here(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->nb_here)
	{
		file_here(i, shell->here);
		i++;
	}
	i = -1;
	while (++i < shell->nb_here)
		free(shell->here[i].lim);
	free(shell->pid);
	free(shell->av);
	free_all(shell->token);
	free(shell->here);
	free(shell);
	exit(0);
}

int	exec_here(t_shell *shell)
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
		child_here(shell);
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

int	init_here(t_shell *shell, char *av)
{
	if (shell->nb_here)
	{
		if (exec_here(shell) == -1)
		{
			free(shell->here);
			free_shell(shell, av);
			return (-1);
		}
	}
	return (1);
}
