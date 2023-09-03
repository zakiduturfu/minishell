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

static char	**ft_split_cmd(char *token, char **tab)
{
	int		i;

	i = 0;
	while (token[i] != ' ' && token[i] != '\0')
		i++;
	tab = malloc (sizeof(char *) * 2);
	if (!tab)
		return (NULL);
	tab[0] = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (token[i] != ' ' && token[i] != '\0')
	{
		tab[0][i] = token[i];
		i++;
	}
	tab[0][i] = '\0';
	if (!(tab[0]))
	{
		free(tab);
		return (NULL);
	}
	while (token[i] == ' ')
		i++;
	tab[1] = &(token[i]);
	return (tab);
}

int	ft_pwd(void)
{
	printf("%s\n", getenv("PWD"));
	return (0);
}

int	ft_env(t_shell *shell)
{
	unsigned int	i;

	i = 0;
	while (shell->env[i])
	{
		printf("%s \n",shell->env[i]);
		i++;
	}
	return (0);
}

int	exec_only_built(t_shell	*shell)
{
	char	**tab;

	// printf("au debut de exec only built, token[0] = %s\n", shell->token[0]);
	tab = NULL;
	tab = ft_split_cmd(shell->token[0], tab);
	// printf("apres split cmd, cmd = %s \n et suite = %s\n", tab[0], tab[1]);
	if (!tab)
		return (-1);
	// if (ft_strcmp("cd", shell->token[0]) == 0)
	// 	return (ft_cd(shell));
	if (ft_strcmp("echo", tab[0]) == 0)
		return (ft_echo(tab));
	// if (ft_strcmp("exit", tab[0]) == 0)
	// 	return (ft_exit(shell));
	if (ft_strcmp("pwd", tab[0]) == 0)
		return (ft_pwd());
	if (ft_strcmp("export", tab[0]) == 0)
		return (ft_export(shell, tab[1]));
	// if (ft_strcmp("unset", tab[0]) == 0)
	// 	return (ft_unset(shell));
	// if (ft_strcmp("env", tab[0]) == 0)
	// 	return (ft_env(shell));
	return (1);
}
