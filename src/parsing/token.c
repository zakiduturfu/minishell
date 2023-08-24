/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:31:19 by zlemery           #+#    #+#             */
/*   Updated: 2023/08/24 16:53:22 by zlemery          ###   ########.fr       */
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

int	find_built(t_shell *shell, char *av)
{
	int		ret;
	char	**tab;

	ret = 0;
	tab = init_start_cmd(shell, shell->token[0], 0, av);
	ret = is_builtin(tab[0]);
	if (tab)
		free_all(tab);
//	printf("tab = %p\n", tab);
	return (ret);
}

char	**init_start_cmd(t_shell *shell, char *cmd_line, int index, char *av)
{
	int		i;
	char	**tab;

	i = 0;
	tab = split_token(cmd_line, ' ', av);
	tab = find_expansion(tab);
	if (!tab)
		return (NULL);
	if (index)
	{
		/*if (check_redir(tab) == -1)
		{
			// close les pipes pour cause d'erreur
			return (NULL);
		}*/
		find_redir(shell, tab, index);
	}
	tab = delete_redir(tab);
//	while (tab[i])
//		tab[i++] = delete_quote(tab[i]);
	// while (tab[i])
	// 	printf("cmd process = %s\n", tab[i++]);
	return (tab);
}
