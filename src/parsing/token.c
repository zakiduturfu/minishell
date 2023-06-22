/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:31:19 by zlemery           #+#    #+#             */
/*   Updated: 2023/06/22 17:55:20 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	token_alloc(char *line, int *i)
{
	int		j;
	int		count;
	char	quote;

	j = 0;
	quote = ' ';
	while (line[*i + j] == ' ')
		j++;
	while (line[*i + j] && (line[*i + j] != ' ' || quote != ' '))
	{
		if (quote == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			quote = line[*i + j++];
		else if (quote != ' ' && line[*i + j] == quote)
		{
			count += 2;
			quote = ' ';
			j++;
		}
		else
			j++;
		if (line[*i + j - 1] == '\\')
			count++;
	}
	return (j - count + 1);
}

int	ignore_space(char *line, int i)
{
	while (line[i] == ' ')
		i++;
	return (i);
}

t_token	*recup_token(char *line, int *i)
{
	t_token	*token;
	int		j;
	char	quote;

	j = 0;
	quote = ' ';
	if (!(token = malloc(sizeof(t_token)))
		|| (token->word = malloc(sizeof(char *) * token_alloc(line, i))))
		return (NULL);
	while (line[*i] && (line[*i] != ' ' || quote != ' '))
	{
		if (quote == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			quote = line[*i++];
		else if (quote != ' ' && line[*i] == quote)
		{
			quote = ' ';
			*i += 1;
		}
		else if (line[*i] == '\\' && line[*i++])
			*i += 1;
		else
			token->word[j++] = line[*i++];
	}
	return (token);
}

void	get_token(char *line, t_token **token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = ignore_space(line, i);
	while (line[i])
	{
		*token = recup_token(line, &i);
		i = ignore_space(line, i);
		*token += 1;
	}
}