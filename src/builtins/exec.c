/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/09/25 18:07:56 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(char **env, char *str)
{
	int	posi;

	posi = -1;
	if (str && open_quote(str) == 1)
		return (dquote());
	if (!str || str[0] == '\0')
	{
		posi = find_var(env, "PWD");
		if (posi == -1)
			return (-1);
		printf("%s\n", env[posi]);
		return (0);
	}
	printf("pwd: too many arguments\n");
	return (0);
}

int	ft_env(char **env)
{
	unsigned int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s \n", env[i]);
		i++;
	}
	return (0);
}

int	ft_exit(char **env)
{
	free_env_tab(env);
	exit(0);
}

int	exec_only_built(t_shell	*shell)
{
	char	**tab;

	tab = NULL;
	tab = ft_split_cmd(shell->token[0], tab, 0);
	fix_quote((signed char **)tab);
	if (!tab)
		return (-1);
	if (ft_strcmp("cd", shell->token[0]) == 0)
		return (ft_cd(shell->env, tab[1]));
	if (ft_strcmp("echo", tab[0]) == 0)
		return (ft_echo(tab));
	if (ft_strcmp("exit", tab[0]) == 0)
		return (ft_exit(shell->env));
	if (ft_strcmp("pwd", tab[0]) == 0)
		return (ft_pwd(shell->env, tab[1]));
	if (ft_strcmp("export", tab[0]) == 0)
		return (ft_export(shell->env, tab[1]));
	if (ft_strcmp("unset", tab[0]) == 0)
		return (ft_unset(shell->env, tab[1]));
	if (ft_strcmp("env", tab[0]) == 0)
		return (ft_env(shell->env));
	return (1);
}
