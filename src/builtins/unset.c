/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/08/28 17:36:00 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	find_var(t_shell *shell, char *var)
{
	unsigned int	size;
	unsigned int	i;

	i = 0;
	size = size_env(shell->env);
	while (i < size)
	{
		if (ft_strncmp(shell->env[i], var, ft_strlen(var)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_parse(char *str, unsigned int i)
{
	if (!str || str[0] == '\0')
	{
		printf("unset: not enough arguments\n");
		return (-1);
	}
	if (open_quote(str) == 1)
		return (dquote());
	while (str[i] != '\0')
	{
		if (str[i] == '=' || str[i] == '-')
		{
			ft_putstr_fd("unset: ", 1);
			ft_putnstr_fd(str, 1, i + 1);
			ft_putstr_fd(": invalid parameter name\n", 1);
			return (-1);
		}
		i = i + 1;
	}
	if (str[i] == '\0')
		return (-1);
	i = i + 1;
	return (0);
}

static int	ft_erase_var(t_shell *shell, int posi)
{
	int	size;
	char			**newenv;
	int	i;
	
	i = 0;
	size = size_env(shell->env);
	size--;
	newenv = malloc(sizeof(char *) * (size + 1));
	if (!newenv)
		return (-1);
	newenv[size] = NULL;
	while (i < posi)
	{
		newenv[i] = shell->env[i];
		i++;
	}
	while (i < size)
	{
		newenv[i] = shell->env[i + 1];
		i++;
	}
	free(shell->env);
	shell->env = newenv;
	return (0);
}

int	ft_unset_one_by_one(t_shell *shell, char *str)
{
	int				posi;

	if (ft_parse(str, 0) == -1)
		return (0);
	posi = find_var(shell, str);
	if (posi == -1)
		return (0);
	if (ft_erase_var(shell, posi) == -1)
		return (1);
	return (0);
}

int	ft_unset(t_shell *shell, char *str)
{
	char **tab;
	unsigned int i;

	i = 0;
	tab = ft_nsplit(str, ' ', '\t');
	if (!tab)
		return (1);
	while (tab[i])
	{
		ft_unset_one_by_one(shell, tab[i]);
		i++;
	}
	while (shell->env[i])
	{
		printf("%s \n",shell->env[i]);
		i++;
	}
	return (0);
}