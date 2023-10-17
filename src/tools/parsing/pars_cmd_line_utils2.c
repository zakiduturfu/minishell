/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_line_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:46:53 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/12 18:50:26 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

int	del_quote(char *s)
{
	int	cmp;
	int	cmp2;
	int	i;

	i = 0;
	cmp = 0;
	cmp2 = 0;
	while (s[i])
	{
		if (i == 0 && s[i] == '\"' && cmp2 % 2 == 0)
			cmp++;
		if (i == 0 && s[i] == '\'' && cmp % 2 == 0)
			cmp2++;
		if (i > 0 && s[i] == '\"' && cmp2 % 2 == 0 && s[i - 1] != '\\')
			cmp++;
		if (i > 0 && s[i] == '\'' && cmp % 2 == 0 && s[i - 1] != '\\')
			cmp2++;
		i++;
	}
	return (cmp + cmp2);
}

int	del_slash(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((is_quote(str, i) == 1 || is_quote(str, i) == 0) && str[i] == '\\'
			&& str[i + 1] && str[i + 1] == '$')
			j++;
		else if (!is_quote(str, i) && str[i] == '\\')
			j++;
		i++;
	}
	return (i - j);
}

int	is_slash(char *s, int i)
{
	if (i == 0 && (s[i] == '\'' || s[i] == '\"'))
		return (1);
	else if (i > 0 && (!is_quote(s, i)) && s[i] == '\"' && s[i - 1] == '\\')
		return (0);
	else if (i > 0 && (!is_quote(s, i)) && s[i] == '\'' && s[i - 1] == '\\')
		return (0);
	return (1);
}
