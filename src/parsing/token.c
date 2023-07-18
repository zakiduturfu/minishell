/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:31:19 by zlemery           #+#    #+#             */
/*   Updated: 2023/07/18 15:58:38 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_token(char *line, int *i, char c)
{
	char	quote;

	quote = c;
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
			*i += 1;
		if (line[*i] == '\\' && line[(*i)++])
			*i += 1;
	}
	return (1);
}

int	split_built(char *cmd)
{
	int		ret;
	char	**tab;

	ret = 0;
	tab = split_token(cmd, ' ');
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

char	**init_start_cmd(t_shell *shell, char *cmd_line, int index)
{
	int		i;
	char	**tab;

	i = 0;
	tab = split_token(cmd_line, ' ');
	if (!tab)
		return (NULL);
	if (index)
	{
		if (find_redir(tab))
		{
			/* close les pipes pour cause d'erreur*/
		}
			open_redir(shell);
	}
	tab = delete_redir(tab);
	while (tab[i])
		tab[i++] = delete_quote(tab[i]);
	return (tab);
}
