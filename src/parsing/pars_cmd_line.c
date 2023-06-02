/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:36:49 by zlemery           #+#    #+#             */
/*   Updated: 2023/05/31 14:04:17 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_is_word(char *new, char *old, int start, int end)
{
	int	i;
	int	chev;

	chev = 0;
	i = start;
	while (start <= end)
	{
		if (old[i] == '<' || old[i] == '>' && chev == 0)
		{
			new[start++] = ' ';
			chev = 1;
		}
		else if (old[i] == '<' || old[i] == '>' && chev == 1)
			new[start++] = old[i++];
		else if (chev == 1 && old[i] != '<' && old[i] != '>')
		{
			new[start++] = ' ';
			chev = 0;
		}
		else
			new[start++] = old[i++];
	}
	return (new);
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
	while (i < (size + (sep * 2)))
	{
		while ((line[i] != '<' && line[i] != '>') && line[i]){
			i++;
			printf("azzazaz%d\n", i);
		}
		if (line[i + 1] == '<' || line[i + 1] == '>')
			i = i + 1;
		ft_is_word(new_line, line, j, i);
		j = i;
		printf("%c\n taille = %d, iiiiii = %d\n", new_line[i], (size + (sep * 2)), i);
	}
	new_line[i] = '\0';
	return (new_line);
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
