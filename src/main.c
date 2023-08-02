/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:56:46 by zlemery           #+#    #+#             */
/*   Updated: 2023/08/01 23:13:28 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)av;
	line = " ";
	if (ac == 1)
	{
		while (line)
		{
			line = readline("minishell>");
			if (pars_line(line) == -1)
				printf("error\n");
			if (strncmp("exit", line, 4) == 0)
			{
				free(line);
				exit(0);
			}
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