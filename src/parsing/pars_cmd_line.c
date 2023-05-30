/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:36:49 by zlemery           #+#    #+#             */
/*   Updated: 2023/05/30 15:41:25 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_is_word(char *new, char *old, int start, int end)
{

}

char	*sep_chev(char *line, int sep)
{
	int		size;
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = ft_strlen(line);
	new_line = malloc(sizeof(char *) * (size + (sep * 2)));
	if (!new_line)
		return (NULL);
	while (i <= (size + (sep * 2)))
	{
		while (line[i] != '<' && line[i] != '>')
			i++;
		if (line[i + 2] == '<' || line[i + 2] == '>')
			i = i + 2;
	}
}

int	chev_not_sep(char *line)
{
	int		ret;
	int		chev;
	int		i;

	i = 0;
	ret = 0;
	chev = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			chev = 1;
			if (line[i + 1] == '<' || line[i + 1] == '>')
				chev = 2;
			ret = ret + chev;
			i = i + chev;
		}
		else
			i++;
	}
	return (ret);
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
