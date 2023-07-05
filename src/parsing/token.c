/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:31:19 by zlemery           #+#    #+#             */
/*   Updated: 2023/07/05 02:08:42 by zlemery          ###   ########.fr       */
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

char	*recup_token(char *line, int *i)
{
	int		j;
	char	quote;
	char	*token;

	j = 0;
	quote = ' ';
//	printf("tokkkkkkkken %d\n", size_token(line) + 1);
	if (!(token = malloc(sizeof(char) * token_alloc(line, i))))
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
			token[j++] = line[(*i)++];
		if (line[*i] == '\\' && line[(*i)++])
			*i += 1;
	}
	token[j] = '\0';
//	printf("%p\n%p\n%s\n", token->word, token, token->word);
	return (token);
}

void	get_token(char *line, char **token)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	token = malloc(sizeof(char *) * size_token(line));
	i = ignore_space(line, i);
	while (line[i])
	{
		token[j] = recup_token(line, &i);
		printf("%s\n", token[j]);
		i = ignore_space(line, i);
		j++;
	}
}
