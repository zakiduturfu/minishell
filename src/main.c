/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaki <zaki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:56:46 by zlemery           #+#    #+#             */
/*   Updated: 2023/08/25 20:36:46 by zaki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_shell	*shell;

	(void)av;
	line = " ";
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	if (ac == 1)
	{
		shell->env = recup_env(env);
		if (!shell->env)
			exit(2);
		increment_shlvl(shell->env);
		while (line)
		{
			line = readline("minishell>");
			if (strcmp("exit", line) == 0)
			{
				free(line);
				free_env_tab(shell->env);
				free(shell);
				exit(0);
			}
			if (pars_line(line, shell, 0, NULL) == -1)
				free(line);
			else
				free(line);
		}
	}
	free(shell);
	return (0);
}

/*	do {
		bjr = readline("> ");
		printf("SALUT %s", bjr);
		if (strcmp("exit", bjr) == 0)
			break;
		free(bjr);
	} while (bjr);*/