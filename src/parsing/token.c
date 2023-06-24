/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:31:19 by zlemery           #+#    #+#             */
/*   Updated: 2023/06/24 21:04:29 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	token_alloc(char *line, int *i)
{
	int		j;
	int		count;
	char	quote;

	j = 0;
	count = 0;
	quote = ' ';
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
int	is_token(char *line, int *i)
{
	char	quote;

	quote = ' ';
	while (line[*i] && (line[*i] != ' ' || quote != ' '))
	{
		if (quote == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			quote = line[(*i)++];
		else if (quote != ' ' && line[*i] == quote)
		{
			quote = ' ';
			*i += 1;
		}
		else
			*i += 1;
		if (line[*i] == '\\' && line[(*i)++])
			*i += 1;
	}
	return (1);
}

int	ignore_space(char *line, int i)
{
	while (line[i] == ' ')
		i++;
	return (i);
}

int	size_token(char *line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	i = ignore_space(line, i);
	while (line[i])
	{
		if (is_token(line, &i) == 1)
			count++;
		i = ignore_space(line, i);
	}
	return (count);
}

t_token	*recup_token(char *line, int *i, t_token ***token)
{
	int		j;
	char	quote;

	j = 0;
	quote = ' ';
	printf("tokkkkkkkken %d\n", size_token(line) + 1);
	if (!(*token = malloc(sizeof(t_token) * (size_token(line) + 1)))
		|| !((**token)->word = malloc(sizeof(char) * token_alloc(line, i))))
			return (NULL);
	while (line[*i] && (line[*i] != ' ' || quote != ' '))
	{
		if (quote == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			quote = line[(*i)++];
		else if (quote != ' ' && line[*i] == quote)
		{
			quote = ' ';
			*i += 1;
		}
		else
			(**token)->word[j++] = line[(*i)++];
		if (line[*i] == '\\' && line[(*i)++])
			*i += 1;
	}
	(**token)->word[j] = '\0';
//	printf("%p\n%p\n%s\n", token->word, token, token->word);
	return (**token);
}

t_token	**get_token(char *line)
{
	int		i;
	int		j;
	t_token	**token;

	i = 0;
	j = 0;
	i = ignore_space(line, i);
	token = malloc(sizeof(t_token *));
	while (line[i])
	{
		token[j] = recup_token(line, &i, &token);
		printf("token->word = %s\n", token[j]->word);
		i = ignore_space(line, i);
		j++;
	}
	return (token);
}