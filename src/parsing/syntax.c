/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:49:25 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/19 19:41:21 by zlemery          ###   ########.fr       */
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
	if (!line)
		return (1);
	if (!line[0])
		return (0);
	else
	{
		while (line[i])
		{
			if (line[i] != ' ' && (line[i] < 7 || line[i] > 13))
				return (1);
			i++;
		}
		return (-1);
	}
	return (0);
}

int	pipe_error(t_shell *shell)
{
	ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	shell->status = 2;
	return (-1);
}

int	check_pipe(char *line, t_shell *shell, int i)
{
	char	c;

	c = 'p';
	while (line[++i])
	{
		if (i == 0 && line[i] == '|' && !is_quote(line, i))
			return (pipe_error(shell));
		else if (line[i] == '|' && c == '|' && !is_quote(line, i))
			return (pipe_error(shell));
		else if (line[i] == '|' && !is_quote(line, i) && line[i + 1] == '|')
			return (pipe_error(shell));
		else if (line[i] == '|' && c == '|')
			return (pipe_error(shell));
		else if (line[i] != ' ' && c == '|')
			c = 'p';
		if (line[i] == '|' && !is_quote(line, i))
			c = '|';
	}
	if (c == '|')
		return (pipe_error(shell));
	return (1);
}
