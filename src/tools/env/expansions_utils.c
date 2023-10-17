/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:59:59 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/17 19:01:14 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*get_val_env(char *name)
{
	char	*val;

	val = getenv(name);
	if (!val)
	{
		val = malloc(1);
		if (!val)
			return (NULL);
		val[0] = '\0';
		return (val);
	}
	return (name);
}

int	search_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
	{
		i++;
		if (str[i] == '$' && is_quote(str, i) == 2)
			i++;
		else if (str[i] == '$' && str[i - 1] == '\\')
			i++;
		else if (str[i] == '$' && str[i + 1] == '\0')
			i++;
		else if (str[i] == '$' && str[i + 1] && (str[i + 1] == '\''
				|| str[i + 1] == '\"'))
			i++;
	}
	return (i);
}

char	**find_expansion(t_shell *shell, char **tab, char **env)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		tab[i] = ft_expansions(shell, tab[i], env);
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

void	tab_value(char **tab, char *str, int i, char **env)
{
	tab[0] = get_before_expand(str, i);
	if (!tab[0])
		return ;
	tab[1] = get_after_expand(str + i + 1);
	if (!tab[1])
		free_expand(tab, 1);
	tab[2] = get_expand_val(str, i);
	if (!tab[2])
		free_expand(tab, 2);
	tab[3] = ft_avengers(tab[0], tab[1], tab[2], env);
}
