/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:56:18 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/12 18:57:16 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_avengers(char *before, char *after, char *expand)
{
	char	*val;
	char	*tmp;
	char	*new_line;

	val = getenv(expand);
	free(expand);
	if (!val)
	{
		val = malloc(1);
		val[0] = 0;
		tmp = ft_strjoin(before, val);
		free(val);
	}
	else
		tmp = ft_strjoin(before, val);
	free(before);
	if (!tmp)
		return (free(after), NULL);
	new_line = ft_strjoin(tmp, after);
	free(tmp);
	free(after);
	if (!new_line)
		return (NULL);
	return (new_line);
}

char	*get_expand_val(char *str, int i)
{
	char	*value;
	int		k;
	int		j;

	j = 0;
	if (str[i] == '$')
		i++;
	k = i;
	while (str[i] && ft_isalpha(str[i]))
		i++;
	value = malloc (sizeof(char) * ((i - k) + 1));
	if (!value)
		return (NULL);
	while (str[j] && k < i)
		value[j++] = str[k++];
	value[j] = '\0';
	return (value);
}

char	*get_after_expand(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (str[i] && ft_isalnum(str[i]))
	{
		i++;
		if (ft_isdigit(str[0] || ft_isdigit(str[1])))
			break ;
	}
	ret = malloc(ft_strlen(str) - i + 1);
	if (!ret)
		return (NULL);
	while (str[i + j])
	{
		ret[j] = str[i + j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*get_before_expand(char *str, int i)
{
	int		j;
	char	*ret;

	j = 0;
	while (str[j] && j < i)
		j++;
	ret = malloc(j + 1);
	if (!ret)
		return (NULL);
	j = 0;
	while (str[j] && j < i)
	{
		ret[j] = str[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*ft_expansions(t_shell *shell, char *str)
{
	int		i;
	char	*tab[4];

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		i = search_expand(str);
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
				stat_expand(tab, str, i, shell);
			else
				tab_value(tab, str, i);
			free(str);
			if (!tab[3])
				return (NULL);
			str = tab[3];
		}
	}
	return (str);
}
