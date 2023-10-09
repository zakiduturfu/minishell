/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:59:59 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/09 15:33:20 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	search_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
	{
		if (str[i] == '\\' && str[i + 1] && str[i + 1] == '$')
			i++;
		i++;
	}
	return (i);
}

char	**find_expansion(t_shell *shell, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		tab[i] = ft_expansions(shell, tab[i]);
		if (!tab[i])
		{
			free_all(tab);
			return (NULL);
		}
		i++;
	}
	return (tab);
}

int	free_expand(char **tab, int index)
{
	if (index == 1)
		free(tab[0]);
	else if (index == 2)
	{
		free(tab[0]);
		free(tab[1]);
	}
	return (-1);
}

int	tab_value(char **tab, char *str, int i)
{
	tab[0] = get_before_expand(str, i);
	if (!tab[0])
		return (-1);
	tab[1] = get_after_expand(str + i + 1);
	if (!tab[1])
		return (free_expand(tab, 1));
	tab[2] = get_expand_val(str, i);
	if (!tab[2])
		return (free_expand(tab, 2));
	tab[3] = ft_avengers(tab[0], tab[1], tab[2]);
	if (!tab[3])
		return (-1);
	return (1);
}
