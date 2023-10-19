/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:15:54 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/19 15:24:44 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print(char **tab, bool newline)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		if (i != 0)
			printf(" ");
		printf("%s", tab[i]);
		i++;
	}
	if (newline == 1)
		printf("\n");
}

static int	n_param(char **tab, int *i, bool n)
{
	unsigned int	j;

	if (!(tab[*i]))
		return (n);
	while (tab[*i])
	{
		j = 0;
		while (is_space(tab[*i][j]))
			j++;
		if (tab[*i][j++] != '-')
			return (n);
		while (tab[*i][j] == 'n')
			j++;
		if (tab[*i][j - 1] != 'n'
			|| (is_space(tab[*i][j]) == 0 && is_end(tab[*i][j] == 0)))
			return (n);
		else
			n = 1;
		*i = *i + 1;
	}
	return (n);
}

int	ft_echo(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		if (n_param(tab, &i, 0) == 1)
			print(&(tab[i]), 0);
		else
			print(&(tab[i]), 1);
	}
	else
		printf("\n");
	return (0);
}
