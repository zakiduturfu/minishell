/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:56:46 by zlemery           #+#    #+#             */
/*   Updated: 2023/08/25 16:42:27 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	int		i;
	char	**new_env;

	i = 0;
	(void)av;
	line = " ";
	if (ac == 1)
	{
		new_env = recup_env(env);
		if (!new_env)
			exit(2);
		increment_shlvl(new_env);
		while (line)
		{
			line = readline("minishell>");
			if (strcmp("exit", line) == 0)
			{
				free(line);
				free_env_tab(new_env);
				exit(0);
			}
			else if (strcmp("env", line) == 0)
			{
				while (new_env[i])
					printf("%s\n", new_env[i++]);
			}
			else
			{
				if (pars_line(line, new_env) == -1)
					printf("error\n");
				free(line);
			}
		}
	}
}

/*	do {
		bjr = readline("> ");
		printf("SALUT %s", bjr);
		if (strcmp("exit", bjr) == 0)
			break;
		free(bjr);
	} while (bjr);*/