/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 23:06:12 by zlemery           #+#    #+#             */
/*   Updated: 2023/07/21 03:15:26 by zlemery          ###   ########.fr       */
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

int	is_builtin(char **cmd)
{
	if (ft_strcmp("cd", cmd[0]) == 0)
		return (1);
	else if (ft_strcmp("echo", cmd[0]) == 0)
		return (1);
	else if (ft_strcmp("exit", cmd[0]) == 0)
		return (1);
	else if (ft_strcmp("pwd", cmd[0]) == 0)
		return (1);
	else if (ft_strcmp("export", cmd[0]) == 0)
		return (1);
	else if (ft_strcmp("unset", cmd[0]) == 0)
		return (1);
	else if (ft_strcmp("env", cmd[0]) == 0)
		return (1);
	else
		return (0);
}

int	size_token(char *line, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	i = t_ignore_sep(line, i, c);
	while (line[i])
	{
		if (is_token(line, &i, c) == 1)
			count++;
		i = t_ignore_sep(line, i, c);
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
			return (str1 - str2);
		i++;
	}
	return (0);
}
