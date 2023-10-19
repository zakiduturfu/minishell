/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/19 15:23:11 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_path(int i, char **tab)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		printf("%s", tab[j]);
		if (j < i)
			printf("/");
		j++;
	}
	printf("\n");
}

int	print_and_return(char *str, int i)
{
	printf("%s", str);
	return (i);
}

int	find_var(char **env, char *var)
{
	unsigned int	size;
	unsigned int	i;

	i = 0;
	if (!env)
		return (-1);
	size = size_env(env);
	while (i < size)
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_free_tab(char **tab)
{
	unsigned int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}
