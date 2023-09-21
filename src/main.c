/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaki <zaki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:56:46 by zlemery           #+#    #+#             */
/*   Updated: 2023/09/15 18:12:14 by zaki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	main(int ac, char **av, char **env)
{
	char	**new_env;

	(void)av;
	if (ac == 1)
	{
		new_env = recup_env(env);
		if (!new_env)
			exit(2);
		increment_shlvl(new_env);
		loop_shell(new_env);
	}
}

/*	do {
		bjr = readline("> ");
		printf("SALUT %s", bjr);
		if (strcmp("exit", bjr) == 0)
			break;
		free(bjr);
	} while (bjr);*/