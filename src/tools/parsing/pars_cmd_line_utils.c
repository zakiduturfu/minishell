/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:40:51 by zlemery           #+#    #+#             */
/*   Updated: 2023/08/24 11:20:50 by zlemery          ###   ########.fr       */
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
		else if (count == 1 && count == '\"')
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
