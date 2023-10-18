/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/18 15:15:16 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cd(char **env, char *str)
{
	char			**tab;

	if (!str || str[0] == '\0')
		return (cd_home(env));
	tab = ft_nsplit(str, ' ', '\t');
	if (!tab)
		return (1);
	if (tab && ft_strcmp(tab[0], "/") != 0 && tab[1])
		return (too_many_args(tab));
	if (tab && ft_strcmp(tab[0], "/") == 0 && tab[1])
	{
		printf("cd: no such file or directory: %s", tab[1]);
		ft_pwd(env, NULL);
		ft_free_tab(tab);
		return (0);
	}
	try_exec_cd(env, tab[0]);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp("cd", cmd) == 0)
		return (1);
	else if (ft_strcmp("echo", cmd) == 0)
		return (1);
	else if (ft_strcmp("exit", cmd) == 0)
		return (1);
	else if (ft_strcmp("pwd", cmd) == 0)
		return (1);
	else if (ft_strcmp("export", cmd) == 0)
		return (1);
	else if (ft_strcmp("unset", cmd) == 0)
		return (1);
	else if (ft_strcmp("env", cmd) == 0)
		return (1);
	else
		return (0);
}

int	ft_pwd(char **env, char *str)
{
	int	posi;

	posi = -1;
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

int	exec_only_built(t_shell	*shell, char ***env, int i)
{
	char	**tab;

	tab = NULL;
	tab = init_start_cmd(shell, shell->token[shell->index] + i, 1, *env);
	if (!tab)
		return (-1);
	else if (ft_strcmp("cd", tab[0]) == 0)
		ft_cd(*env, tab[1]);
	else if (ft_strcmp("echo", tab[0]) == 0)
		ft_echo(tab[1]);
	else if (ft_strcmp("exit", tab[0]) == 0)
		ft_exit(tab, shell, *env);
	else if (ft_strcmp("pwd", tab[0]) == 0)
		ft_pwd(*env, tab[1]);
	else if (ft_strcmp("export", tab[0]) == 0)
		ft_export(env, tab[1]);
	else if (ft_strcmp("unset", tab[0]) == 0)
		ft_unset(env, tab[1]);
	else if (ft_strcmp("env", tab[0]) == 0)
		ft_env(*env);
	ft_free_tab(tab);
	return (1);
}
