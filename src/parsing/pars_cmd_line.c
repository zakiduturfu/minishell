/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:36:49 by zlemery           #+#    #+#             */
/*   Updated: 2023/05/29 18:18:01 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*int	chev_not_sep(char *line)
{
	int	i;
	int	cnt;

	i = 1;
	cnt = 0;
	if (line[0] == '<' && line [i] != ' ' && line[i] != '<')
		cnt++;
	while (line[i])
	{
		if ((line[i] == '<' || line[i] == '>')
			&& (line[i - 1] != ' ' && line[i - 1] != '>')
				&& (line[i + 1] != ' ' && line[i + 1] != '>'))
			cnt += 2;
		else if ((line[i] == '<' || line[i] == '>')
			&& ((line[i - 1] != ' ' && line[i - 1] != '>')
				|| (line[i + 1] != ' ' && line[i + 1] != '>')))
			cnt += 1;
		i++;
	}
	return (cnt);
}*/

int	chev_not_sep(char *line)
{
	int		ret;
	char	c;
	int		i;

	i = 0;
	ret = 0;
	c = line[i];
	while (line[i])
	{
		if (line[i + 1] == '<')
		{
			if (line[i + 2] == '<')
		}
		i++;
	}
}
/*
int	need_sep(char *line)
{

}*/
/*
char	*sep_redir(char *line)
{
	int		count;
	int		i;
	char	new_line;

	i = 0;
	count = chev_not_sep(line);
	new_line = malloc(sizeof(char *) * ft_strlen(line) + (count + 1));
	if (!new_line)
		return (NULL);
	while (new_line)
	{

	}
}*/
/*int	pars_cmd_line(char *line)
{
	if (!line)
		return (0);
//	line = sep_redir(line);
}*/
