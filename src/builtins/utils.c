/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/09/21 17:57:30 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_and_return(char *str, int i)
{
	printf("%s", str);
	return (i);
}

int	find_var(t_shell *shell, char *var)
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

char	**ft_split_cmd(char *token, char **tab, unsigned int i)
{
	while ((token[i] != ' ' || token[i] == '\t') && token[i] != '\0')
		i++;
	tab = malloc (sizeof(char *) * 2);
	if (!tab)
		return (NULL);
	tab[0] = malloc(sizeof(char) * (i + 1));
	if (!(tab[0]))
	{
		free(tab);
		return (NULL);
	}
	i = 0;
	while ((token[i] != ' ' || token[i] == '\t') && token[i] != '\0')
	{
		tab[0][i] = token[i];
		i++;
	}
	tab[0][i] = '\0';
	while (token[i] == ' ' || token[i] == '\t')
		i++;
	tab[1] = &(token[i]);
	return (tab);
}
