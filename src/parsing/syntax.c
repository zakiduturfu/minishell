/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:49:25 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/11 17:56:52 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*space_sep(char *line)
{
	int		i;
	int		count;
	char	*new;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (is_sep(line, i) == 1)
			count++;
		i++;
	}
	new = malloc(sizeof(char *) * (i + (2 * count) + 1));
	if (!new)
		return (NULL);
	return (new);
}

char	*syntax_line(char *line, int i, int j)
{
	char	*new;

	new = space_sep(line);
	if (!new)
		return (NULL);
	while (line[i])
	{
		if ((is_sep(line, i) == 1) && is_quote(line, i) == 0)
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (is_quote(line, i) == 0 && (line[i] == '>' || line[i] == '<'))
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else if (is_in_quote(line, i, line[i])
			&& (line[i] == ' ' || line[i] == '|'))
			new[j++] = -line[i++];
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	return (new);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && (line[i] < 7 || line[i] > 13))
			return (1);
		i++;
	}
	return (0);
}
