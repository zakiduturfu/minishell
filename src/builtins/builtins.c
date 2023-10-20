/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/20 20:41:15 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cd(char ***env, char **tab)
{
	if (!tab || !(tab[0]) || tab[0][0] == '\0')
		return (cd_home(env));
	if (tab[0] && tab[1])
	{
		printf("cd: too many arguments\n");
		return (0);
	}
	try_exec_cd(env, tab[0], -1, NULL);
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

int	ft_pwd(void)
{
	char	*buf;

	buf = malloc(sizeof(char) * 1000);
	if (!buf)
		return (1);
	printf("%s\n", getcwd(buf, 1000));
	free(buf);
	return (0);
}

int	exec_only_built(t_shell	*shell, char ***env, int i, char **tab)
{
	tab = init_start_cmd(shell, shell->token[shell->index] + i, 1, *env);
	if (!tab)
		return (-1);
	else if (ft_strcmp("cd", tab[0]) == 0)
		ft_cd(env, &(tab[1]));
	else if (ft_strcmp("echo", tab[0]) == 0)
		ft_echo(&(tab[1]));
	else if (ft_strcmp("exit", tab[0]) == 0)
		ft_exit(tab, shell, *env);
	else if (ft_strcmp("pwd", tab[0]) == 0)
		ft_pwd();
	else if (ft_strcmp("export", tab[0]) == 0)
		ft_export(env, &(tab[1]));
	else if (ft_strcmp("unset", tab[0]) == 0)
		ft_unset(env, &(tab[1]));
	else if (ft_strcmp("env", tab[0]) == 0)
		ft_env(*env, &(tab[1]));
	ft_free_tab(tab);
	return (1);
}
