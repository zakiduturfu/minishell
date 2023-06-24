/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:36:49 by zlemery           #+#    #+#             */
/*   Updated: 2023/06/24 16:42:40 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdint.h>

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
		else if (count == 1 && count == '\"')
			count = 0;
		else if (count == 2 && line[j] == '\'')
			count = 0;
		j++;
	}
	return (count);
}

int	ignore_sep(char *line, int i)
{
	if (line[i] == '\\' && line[i + 1] && line[i + 1] == '|')
		return (1);
	else if (line[i] == '\\' && line[i + 1] && line[i + 1] == ';')
		return (1);
	else if (line[i] == '\\' && line[i + 1] && line[i + 1] == '>'
		&& line[i + 2] && line[i + 2] == '>')
		return (1);
	else if (line[i] == '\\' && line[i + 1] && line[i + 1] == '>')
		return (1);
	return (0);
}

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
		if ((is_sep(line, i) == 1) && is_quote(line, i) == 0)
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (is_quote(line, i) == 0 && (line[i] == '>' || line[i] == '<'))
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

void	affiche_test(char *cmd)
{
	char	**cmd_line;

	cmd_line = ft_split(cmd, '|');
	while (*cmd_line)
	{
		printf("%s\n", *cmd_line);
		cmd_line++;
	}
}

void	pars_line(char *line)
{
	char	*cmd;
	char	**cmd_line;
	t_shell	*shell;

	cmd = line_arg(line);
	affiche_test(cmd);
	cmd_line = ft_split(cmd, '|');
	shell = NULL;
//	printf("%p\n%p\n%p\n", cmd, cmd_line, shell);
	shell->token = get_token(*cmd_line);
/*	while (*cmd_line)
	{
		get_token(*cmd_line, token);
		*cmd_line++;
	}*/
}
/*
void	v2_pars_line(char *line)
{
	char	*tmp;
	char	**cmd_line;
	t_shell	*shell;

	tmp = line_arg(line);
	affiche_test(tmp);
	cmd_line = ft_split(tmp, '|');
	shell->token->word = NULL;
	shell->token->next = NULL;
	get_token(*cmd_line, shell->token);
}*/