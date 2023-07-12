/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:31:19 by zlemery           #+#    #+#             */
/*   Updated: 2023/07/12 03:39:01 by zlemery          ###   ########.fr       */
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

char	*recup_token(char *line, int *i)
{
	int		j;
	char	quote;
	char	*token;

	j = 0;
	quote = ' ';
	token = malloc(sizeof(char) * token_alloc(line, i));
	if (!token)
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
	return (token);
}

char	**get_token(char *line)
{
	int		i;
	int		j;
	char	**token;

	i = 0;
	j = 0;
	token = malloc(sizeof(char *) * (size_token(line) + 1));
	if (!token)
		return (NULL);
	i = ignore_space(line, i);
	while (line[i])
	{
		token[j] = recup_token(line, &i);
		printf("%p\n", token[j]);
		i = ignore_space(line, i);
		j++;
	}
	token[j] = 0;
	return (token);
}

int	split_built(char *cmd)
{
	int		ret;
	char	**tab;

	ret = 0;
	tab = get_token(cmd);
	if (!tab)
		return (0);
	ret = is_builtin(tab);
	free_all(tab);
	return (ret);
}

/*
int	find_redir(t_shell *shell)
{
	char	**tab;
	int		i;

	i = 0;
	tab = get_token(shell->token[0]);
	if (!tab)
		return (0);
	if (!ft_strcmp("<<", shell->token[0]))
		shell->here = 1;
	free_all(tab);
	tab = get_token(shell->token[shell->nb_cmd]);
	if (!tab)
		return (0);
	while (tab[i])
	{
		if (!ft_strcmp(">>", tab[i]))
			shell->append = 1;
		i++;
	}
	free_all(tab);
	return (1);
}
*/
int	find_redir(char **redir)
{
	int	i;

	i = 0;
	while (redir[i])
	{
		if (!ft_strcmp(">", redir[i]))
			return (1);
		else if (!ft_strcmp(">>", redir[i]))
			return (1);
		else if (!ft_strcmp("<", redir[i]))
			return (2);
		else if (!ft_strcmp("<<", redir[i]))
			return (2);
	}
	return (0);
}

char	**delete_redir(char **line)
{
	int		i;
	char	**ret;
	int		size;

	i = 0;
	size = find_redir(line);
	if (!size)
		return (line);
	ret = malloc(sizeof(char *) * (size + 1));
	while (line[i])
	{
		if (line[i][0] == '<' || line[i][0] == '>')
			i++;
		else
			ret[i] = ft_strdup(line[i]);
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char	**init_start_cmd(t_shell *shell, char *cmd_line)
{
	int		i;
	char	**tab;

	i = 0;
	tab = get_token(cmd_line);
	if (!tab)
		return (NULL);
	if (find_redir(tab))
		open_redir(shell);
	tab = delete_redir(tab);
	while (tab[i])
		tab[i++] = delete_quote(tab[i]);
	return (tab);
}