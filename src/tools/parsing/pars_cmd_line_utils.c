/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaki <zaki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:40:51 by zlemery           #+#    #+#             */
/*   Updated: 2023/09/15 14:11:26 by zaki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_sep(char *line, int i)
{
	if (i > 0 && ft_strchr("<>|;", line[i]) && is_quote(line, i) == 0
		&& line[i - 1] == '\\')
		return (0);
	if (ft_strchr("<>|;", line[i]) && is_quote(line, i) == 0)
		return (1);
	else
		return (0);
}

int	is_quote(char *line, int i)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (line[j] && j != i)
	{
		if (j > 0 && line[j - 1] == '\\')
			;
		else if (count == 0 && line[j] == '\"')
			count = 1;
		else if (count == 0 && line[j] == '\'')
			count = 2;
		else if (count == 1 && line[j] == '\"')
			count = 0;
		else if (count == 2 && line[j] == '\'')
			count = 0;
		j++;
	}
	return (count);
}

int	ignore_sep(char *line, int i)
{
	if (line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
		return (1);
	else if (line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
		return (1);
	else if (line[i] == '\\' && line[i + 1] && line[i + 1] == '>'
		&& line[i + 2] && line[i + 2] == '>')
		return (1);
	else if (line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
		return (1);
	return (0);
}

int	count_quote(char *s)
{
	int	cmp;
	int	cmp2;
	int	i;

	i = 0;
	cmp = 0;
	cmp2 = 0;
	while (s[i])
	{
		if (s[i] == '\"' && cmp2 % 2 == 0)
			cmp++;
		if (s[i] == '\'' && cmp % 2 == 0)
			cmp2++;
		i++;
	}
	return (cmp + cmp2);
}

char	*delete_quote(char *s)
{
	int		i;
	int		j;
	char	*tab;

	i = 0;
	j = 0;
	tab = malloc(sizeof(char) * ((ft_strlen(s) - count_quote(s)) + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		if ((is_quote(s, i) == 1 || !is_quote(s, i))
			&& s[i] == '\"')
			i++;
		else if ((is_quote(s, i) == 2 || !is_quote(s, i))
			&& s[i] == '\'')
				i++;
		if (!s[i])
			break ;
		else
			tab[j++] = s[i++];
	}
	tab[j] = '\0';
	free(s);
	return (tab);
}
