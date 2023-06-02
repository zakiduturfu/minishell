/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:56:46 by zlemery           #+#    #+#             */
/*   Updated: 2023/05/31 13:39:24 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*cmd;
	char	**cmd_line;

	(void)av;
	line = " ";
	if (ac == 1)
	{
		while (line)
		{
			line = readline("> ");
			printf("nombre de chevron = %d\n", chev_not_sep(line));
			cmd = sep_chev(line, chev_not_sep(line));
			cmd_line = ft_split(line, ' ');
			while (*cmd_line)
			{
				printf("%s\n", *cmd_line);
				cmd_line++;
			}
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