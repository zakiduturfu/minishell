/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:47:14 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/16 15:39:47 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/readline.h>

void	handler_sig(int sig)
{
	t_shell	*shell;

	shell = create_data();
	(void)sig;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	shell->status = 130;
}

void	handler_cmd(int sig)
{
	t_shell	*shell;

	(void)sig;
	shell = create_data();
	write(2, "\n", 1);
	shell->status = 130;
}

void	handler_here(int sig)
{
	t_shell	*shell;
	t_env	*env;
	int		i;

	i = -1;
	(void)sig;
	shell = create_data();
	env = create_env();
	write(2, "\n", 1);
	while (++i < shell->nb_here)
	{
		close(shell->here[i].here_pipe[0]);
		close(shell->here[i].here_pipe[1]);
		free(shell->here[i].lim);
	}
	free_env_tab(env->env);
	free(shell->pid);
	free(shell->av);
	free_all(shell->token);
	free(shell->here);
	exit(130);
}

void	child_here(t_shell *shell, char **env)
{
	int		i;
	t_env	*envp;

	i = 0;
	signal(SIGINT, &handler_here);
	envp = create_env();
	envp->env = env;
	while (i < shell->nb_here)
	{
		file_here(i, shell->here);
		i++;
	}
	i = -1;
	while (++i < shell->nb_here)
		free(shell->here[i].lim);
	free_env_tab(env);
	free(shell->pid);
	free(shell->av);
	free_all(shell->token);
	free(shell->here);
	exit(0);
}
