/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:46:39 by zlemery           #+#    #+#             */
/*   Updated: 2023/07/22 02:01:31 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	t_ignore_sep(char *line, int i, char c)
{
	while (line[i] == c)
		i++;
	return (i);
}

int	token_alloc(char *line, int *i, char c)
{
	int		j;
	int		count;
	char	quote;

	j = 0;
	count = 0;
	quote = c;
	while (line[*i + j] && (line[*i + j] != c || quote != c))
	{
		if (quote == c && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			quote = line[*i + j++];
		else if (quote != c && line[*i + j] == quote)
		{
			count += 2;
			quote = c;
			j++;
		}
		else
			j++;
		if (line[*i + j - 1] == '\\')
			count++;
	}
	return (j - count + 1);
}

char	*recup_token(char *line, int *i, char c)
{
	int		j;
	char	quote;
	char	*token;

	j = 0;
	quote = c;
	token = malloc(sizeof(char) * token_alloc(line, i, c));
	if (!token)
		return (NULL);
	while (line[*i] && (line[*i] != c || quote != c))
	{
		if (quote == c && (line[*i] == '\'' || line[*i] == '\"'))
			quote = line[(*i)++];
		else if (quote != c && line[*i] == quote)
		{
			quote = c;
			*i += 1;
		}
		else
			token[j++] = line[(*i)++];
		if (line[*i] == '\\' && line[(*i)++])
			*i += 1;
	}
	token[j] = '\0';
	return (token);
}

char	**split_token(char *line, char c)
{
	int		i;
	int		j;
	char	**token;

	i = 0;
	j = 0;
	token = malloc(sizeof(char *) * (size_token(line, c) + 1));
	if (!token)
		return (NULL);
	i = t_ignore_sep(line, i, c);
	while (line[i])
	{
		token[j] = recup_token(line, &i, c);
		printf("%p\n", token[j]);
		i = t_ignore_sep(line, i, c);
		j++;
	}
	token[j] = 0;
	return (token);
}
