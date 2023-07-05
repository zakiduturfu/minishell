/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:56:46 by zlemery           #+#    #+#             */
/*   Updated: 2023/07/04 22:36:30 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)av;
	(void)env;
	line = " ";
	if (ac == 1)
	{
		while (line)
		{
			line = readline("minishell>");
			pars_line(line);
			if (strncmp("exit", line, 4) == 0)
				exit(0);
			free(line);
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