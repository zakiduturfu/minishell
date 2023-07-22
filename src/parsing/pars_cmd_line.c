/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:36:49 by zlemery           #+#    #+#             */
/*   Updated: 2023/07/22 02:04:18 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/readline.h>
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

	cmd_line = split_token(cmd, '|');
	while (*cmd_line)
	{
		printf("%s\n", *cmd_line);
		cmd_line++;
	}
}

int	pars_line(char *line)
{
	char	*cmd;
	t_shell	*shell;

	cmd = line_arg(line);
//	affiche_test(cmd);
	shell = malloc(sizeof(t_shell));
	if (!init_struct(shell, cmd))
		return (-1);
	if (!shell->token)
		return ;
	free(cmd);
	shell->nb_cmd = (count_cmd(shell->token));
	if (shell->nb_cmd == 1 && split_built(shell) == 1)
		exec_only_built(shell);
	exec_pipex(shell);
	free_all(shell->token);
	free(shell);
}