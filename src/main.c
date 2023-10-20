/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:56:46 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/20 17:26:30 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	**new_env;

	(void)av;
	if (!env)
		exit(0);
	if (ac == 1)
	{
		new_env = recup_env(env);
		if (!new_env)
			exit(2);
		if (increment_shlvl(new_env) == -1)
		{
			free_env_tab(new_env);
			exit(2);
		}
		loop_shell(new_env, NULL);
	}
}
