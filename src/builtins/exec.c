/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/08/28 17:36:00 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_shell *shell, char *str)
{
	unsigned int	posi;

	if (open_quote(str) == 1)
		return (dquote());
	if (!str || str[0] == '\0')
	{
		posi = find_var(shell, "PWD");
		printf("%s\n", shell->env[posi]);
		return (0);
	}
	printf("pwd: too many arguments\n");
	return (0);
}

int	ft_env(t_shell *shell)
{
	unsigned int	i;

	i = 0;
	while (shell->env[i] != NULL)
	{
		printf("%s \n", shell->env[i]);
		i++;
	}
	return (0);
}

int	exec_only_built(t_shell	*shell)
{
	char	**tab;

	tab = NULL;
	tab = ft_split_cmd(shell->token[0], tab, 0);
	if (!tab)
		return (-1);
	// if (ft_strcmp("cd", shell->token[0]) == 0)
	// 	return (ft_cd(shell));
	if (ft_strcmp("echo", tab[0]) == 0)
		return (ft_echo(tab));
	// if (ft_strcmp("exit", tab[0]) == 0)
	// 	return (ft_exit(shell));
	if (ft_strcmp("pwd", tab[0]) == 0)
		return (ft_pwd(shell, tab[1]));
	if (ft_strcmp("export", tab[0]) == 0)
		return (ft_export(shell, tab[1]));
	if (ft_strcmp("unset", tab[0]) == 0)
		return (ft_unset(shell, tab[1]));
	if (ft_strcmp("env", tab[0]) == 0)
		return (ft_env(shell));
	return (1);
}
