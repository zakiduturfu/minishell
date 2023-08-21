/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:59:59 by zlemery           #+#    #+#             */
/*   Updated: 2023/08/21 16:33:02 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	search_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	return (i);
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
	return (1);
}
