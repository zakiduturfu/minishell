/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:40:51 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/20 17:29:54 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_sep(char *line, int i)
{
	if (i > 0 && ft_strchr("<>|;", line[i]) && is_quote(line, i) == 0
		&& line[i - 1] == '\\')
		return (0);
	if (ft_strchr("<>|;", line[i]) && is_quote(line, i) == 0)
		return (1);
	else
		return (0);
}

int	is_quote(char *line, int i)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (line[j] && j != i)
	{
		if (j > 0 && line[j - 1] == '\\')
			;
		else if (count == 0 && line[j] == '\"')
			count = 1;
		else if (count == 0 && line[j] == '\'')
			count = 2;
		else if (count == 1 && line[j] == '\"')
			count = 0;
		else if (count == 2 && line[j] == '\'')
			count = 0;
		j++;
	}
	return (count);
}

int	count_quote(char *s)
{
	int	cmp;
	int	cmp2;
	int	i;

	i = -1;
	cmp = 0;
	cmp2 = 0;
	while (s[++i])
	{
		if (i == 0 && s[i] == '\"' && cmp2 % 2 == 0)
			cmp++;
		else if (i > 0 && s[i] == '\"' && cmp2 % 2 == 0 && s[i - 1] != '\\')
			cmp++;
		if (i == 0 && s[i] == '\'' && cmp % 2 == 0)
			cmp2++;
		else if (i > 0 && s[i] == '\'' && cmp % 2 == 0 && s[i - 1] != '\\')
			cmp2++;
	}
	if (cmp % 2 != 0 || cmp2 % 2 != 0)
	{
		ft_putstr_fd("syntaxe error: quote must be closed\n", 2);
		return (-1);
	}
	return (cmp + cmp2);
}

char	*delete_quote(char *s, int i, int j)
{
	char	*tab;

	tab = malloc(sizeof(char) * ((del_slash(s) - del_quote(s)) + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		if (is_quote(s, i) != 2 && s[i] == '\"' && is_slash(s, i))
			i++;
		else if (is_quote(s, i) != 1 && s[i] == '\'' && is_slash(s, i))
			i++;
		else if (!s[i])
			break ;
		else if (s[i] == '\\' && (is_quote(s, i) != 2) && s[i + 1]
			&& (s[i + 1] == '$' || s[i + 1] == '\"'))
			i++;
		else if (s[i] == '\\' && !is_quote(s, i))
			i++;
		else
			tab[j++] = s[i++];
	}
	tab[j] = '\0';
	free(s);
	return (tab);
}

int	check_line(t_shell *shell, char *line)
{
	if (count_quote(line) == -1 || check_pipe(line, shell, -1) == -1)
	{
		shell->status = 1;
		if (shell->token)
		{
			free_all(shell->token);
			if (shell->av)
				free(shell->av);
			if (shell->pid)
				free(shell->pid);
		}
		return (1);
	}
	return (0);
}
