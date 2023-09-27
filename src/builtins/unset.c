/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/09/27 12:05:16 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	return (0);
}

static int	ft_erase_var(char ***env, int posi)
{
	int		size;
	char	**newenv;
	int		i;

	i = 0;
	size = size_env(*env);
	size--;
	newenv = malloc(sizeof(char *) * (size + 1));
	if (!newenv)
		return (-1);
	newenv[size] = NULL;
	while (i < posi)
	{
		newenv[i] = (*env)[i];
		i++;
	}
	while (i < size)
	{
		newenv[i] = (*env)[i + 1];
		i++;
	}
	free(*env);
	*env = newenv;
	return (0);
}

static int	ft_unset_one_by_one(char **env, char *str)
{
	int	posi;

	if (ft_parse(str, 0) == -1)
		return (0);
	posi = find_var(env, str);
	if (posi == -1)
		return (0);
	if (ft_erase_var(&env, posi) == -1)
		return (1);
	return (0);
}

int	ft_unset(char **env, char *str)
{
	char			**tab;
	unsigned int	i;

	i = 0;
	if (!str)
		return(print_and_return("unset: not enough arguments\n", -1));
	tab = ft_nsplit(str, ' ', '\t');
	if (!tab)
		return (1);
	while (tab[i])
	{
		ft_unset_one_by_one(env, tab[i]);
		i++;
	}
	ft_free_tab(tab);
	return (0);
}
