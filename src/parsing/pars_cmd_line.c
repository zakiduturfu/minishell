/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:36:49 by zlemery           #+#    #+#             */
/*   Updated: 2023/05/23 18:02:07 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	chev_not_sep(char *line)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] != ' ' && line[i + 1] != '<')
			cnt++;
		if (line[i] == '>' && line[i + 1] != '>' && line[i + 1] != ' ')
			cnt++;
		if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] != ' ')
			cnt++;
		if (line[i] == '>' && line[i + 1] == '>' && line[i + 2] != ' ')
			cnt++;
		i++;
	}
	return (cnt);
}

int	need_sep(char *line)
{

}

char	*sep_redir(char *line)
{
	int		count;
	char	new_line;

	count = chev_not_sep(line);
	new_line = malloc(sizeof(char *) * ft_strlen(line) + (count + 1));
	if (!new_line)
		return (NULL);
	while (new_line)
}

int	pars_cmd_line(char *line)
{
	if (!line)
		return (0);
	line = sep_redir(line);
}
