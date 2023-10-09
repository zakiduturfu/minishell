/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 23:06:12 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/02 15:46:16 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	count_cmd(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	check_redir(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[i++])
	{
		if ((cmd[i][0] == '<' || cmd[i][0] == '>') && !cmd[i + 1])
			return (-1);
		//message d'erreur pars error near `
	}
	i = -1;
	while (cmd[i++])
	{
		if ((cmd[i][0] == '<' || cmd[i][0] == '>')
			&& (cmd[i + 1][0] == '<' || cmd[i][0] == '>'))
			return (-1);
		//message d'erreur pars errors near `
	}
	return (0);
}

int	size_token(char *line, char c, char *av)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	i = t_ignore_sep(line, i, c, av);
	while (line[i])
	{
		if (is_token(line, &i, c, av) == 1)
			count++;
		i = t_ignore_sep(line, i, c, av);
	}
	return (count);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

int	is_in_quote(char *line, int i, char c)
{
	int		j;
	char	quote;

	j = 0;
	quote = c;
	while (j < i)
	{
		if ((line[j] == '\'' || line[j] == '\"') && quote == c)
			quote = line[j];
		else if ((line[j] == quote) && quote != c)
			quote = c;
		j++;
	}
	if (quote != c)
		return (1);
	return (0);
}
