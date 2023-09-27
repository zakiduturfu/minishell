/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/09/27 11:36:33 by hstephan         ###   ########.fr       */
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
		printf("%s\n", &(env[posi][4]));
		return (0);
	}
	printf("pwd: too many arguments\n");
	return (0);
}

int	ft_env(char **env)
{
	unsigned int	i;

	i = 0;
	if (!env)
		return (1);
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

int	exec_only_built(t_shell	*shell, char **env)
{
	char	**tab;

	tab = NULL;
	printf("dans exec only built, token 0 = %s\n", shell->token[0]);
	tab = ft_split_cmd(shell->token[0], tab, 0);
	fix_quote((signed char **)tab);
	if (!tab)
		return (-1);
	else if (ft_strcmp("cd", tab[0]) == 0)
		ft_cd(env, tab[1]);
	else if (ft_strcmp("echo", tab[0]) == 0)
		ft_echo(tab);
	else if (ft_strcmp("exit", tab[0]) == 0)
		ft_exit(env);
	else if (ft_strcmp("pwd", tab[0]) == 0)
		ft_pwd(env, tab[1]);
	else if (ft_strcmp("export", tab[0]) == 0)
		ft_export(env, tab[1]);
	else if (ft_strcmp("unset", tab[0]) == 0)
		ft_unset(env, tab[1]);
	else if (ft_strcmp("env", tab[0]) == 0)
		ft_env(env);
	ft_free_tab(tab);
	return (1);
}
