/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:31:19 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/16 17:57:46 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <unistd.h>

int	is_token(char *line, int *i, char c, char *av)
{
	char	quote;

	quote = c;
	while (line[*i] && (line[*i] != c || is_in_quote(av, *i, c)))
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
		if (line[*i] == '\\' && line[(*i)++] && !is_in_quote(av, *i, c))
			*i += 1;
	}
	if (line[*i] == c && is_in_quote(av, *i, c) == 1)
		return (0);
	return (1);
}

int	find_built(t_shell *shell, char **env)
{
	int		ret;
	char	**tab;

	ret = 0;
	tab = init_start_cmd(shell, shell->token[0], 0, env);
	if (tab)
	{
		ret = is_builtin(tab[0]);
		if (tab)
			free_all(tab);
	}
	return (ret);
}

void	fix_quote(signed char **line)
{
	int	i;
	int	j;

	i = 0;
	if (!line)
		return ;
	while (line[i])
	{
		j = 0;
		while (line[i][j])
		{
			if (line[i][j] == -32 || line[i][j] == -124)
				line[i][j] = -line[i][j];
			j++;
		}
		i++;
	}
}

int	check_redirections(char **tab, int i)
{
	i = -1;
	while (tab[++i])
	{
		if ((tab[i][0] == '<' || tab[i][0] == '>') && (!tab[i + 1]))
			break ;
		if ((tab[i][0] == '<' || tab [i][0] == '>')
			&& (tab[i + 1][0] == '<' || tab[i + 1][0] == '>'))
		{
			ft_putstr_fd("shell: pars error near `", 2);
			ft_putstr_fd(tab[i + 1], 2);
			ft_putstr_fd("'\n", 2);
			return (1);
		}
	}
	i = -1;
	while (tab[++i])
	{
		if ((tab[i][0] == '<' || tab[i][0] == '>') && (!tab[i + 1]))
		{
			ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
			return (1);
		}
	}
	return (0);
}

char	**init_start_cmd(t_shell *shell, char *cmd_line, int index, char **env)
{
	int		i;
	char	**tab;

	i = -1;
	tab = ft_split(cmd_line, ' ');
	fix_quote((signed char **)tab);
	tab = find_expansion(shell, tab);
	if (!tab)
		return (NULL);
	if (index)
	{
		if (check_redirections(tab, 0))
		{
			if (shell->prev_pipe != -1)
				close(shell->prev_pipe);
			close_all_pipe(shell);
			free_all(tab);
			return (NULL);
		}
		find_redir(shell, tab, index, env);
	}
	tab = delete_redir(tab);
	while (tab[++i])
		tab[i] = delete_quote(tab[i], 0, 0);
	return (tab);
}
