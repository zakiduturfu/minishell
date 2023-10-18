/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/18 12:44:10 by hstephan         ###   ########.fr       */
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

int	ft_exit(char **env, t_shell shell)
{
	free_env_tab(env);
	clear_history();
	exit(shell.status);
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

int	exec_only_built(t_shell	*shell, char ***env)
{
	char	**tab;

	tab = NULL;
	tab = ft_split_cmd(shell->token[0], tab, 0);
	fix_quote((signed char **)tab);
	tab = find_expansion(shell, tab, *env);
	if (!tab)
		return (-1);
	else if (ft_strcmp("cd", tab[0]) == 0)
		ft_cd(*env, tab[1]);
	else if (ft_strcmp("echo", tab[0]) == 0)
		ft_echo(tab[1]);
	else if (ft_strcmp("exit", tab[0]) == 0)
		ft_exit(*env, *shell);
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
