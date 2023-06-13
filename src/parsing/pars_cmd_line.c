/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:36:49 by zlemery           #+#    #+#             */
/*   Updated: 2023/06/13 16:17:04 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdint.h>

int	is_quote(char *line, int i)
{
	int	 j;
	int	count;

	j = 0;
	count = 0;
	while (j < i)
	{
		if (line[j] == '\'')
			count++;
		j++;
	}
	return (count);
}

int	is_sep(char *line, int i)
{
	if (ft_strchr("<>|;", line[i]) && is_quote(line, i) == 0)
		return (1);
	else
		return (0);
}

char	*space_sep(char *line)
{
	int		i;
	int		count;
	char	*new;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (is_sep(line, i) == 1)
			count++;
		i++;
	}
	new = malloc(sizeof(char *) * (i + (2 * count) + 1));
	if (!new)
		return (NULL);
	return (new);
}

char	*line_arg(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = space_sep(line);
	while (line[i])
	{
		if ((is_sep(line, i) == 1) && is_quote(line, i) != 2)
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	printf("nouvelle ligne: %s\n", new);
	return (new);
}

void	pars_line(char *line)
{
	char	*cmd;
	char	**cmd_line;

	cmd = line_arg(line);
	cmd_line = ft_split(cmd, ' ');
	while (*cmd_line)
	{
		printf("%s\n", *cmd_line);
		cmd_line++;
	}
}
