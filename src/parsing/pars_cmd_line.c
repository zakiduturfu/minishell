/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:36:49 by zlemery           #+#    #+#             */
/*   Updated: 2023/08/23 18:06:25 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/readline.h>
#include <stdint.h>


int	init_struct(t_shell *shell, char *av)
{
	shell->index = 0;
	shell->fdin = 0;
	shell->fdout = 0;
	shell->token = split_token(av, '|', av);
	if (!shell->token)
		return (-1);
	shell->nb_cmd = count_cmd(shell->token);
	if (shell->nb_cmd)
		shell->pid = malloc(sizeof(int) * shell->nb_cmd);
	if (!shell->pid)
		return (-1);
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
/*
void	affiche_test(char *cmd)
{
	char	**cmd_line;

	cmd_line = split_token(cmd, '|');
	while (*cmd_line)
	{
		printf("%s\n", *cmd_line);
		cmd_line++;
	}
}*/

void	test_cmd(t_shell *shell, char *av)
{
	int		i;
	int		j;
	char	**cmd;

	i = 0;
	while (i < shell->nb_cmd)
	{
		j = 0;
		cmd = init_start_cmd(shell, shell->token[i], 2, av);
		if (cmd)
		{
			while (cmd[j])
			{
				printf("cmd = %s\n", cmd[j]);
				j++;
			}
		}
		printf("fdin = %d\n", shell->fdin);
		printf("fdout = %d\n", shell->fdout);
		printf("--------------------------\n");
		i++;
		shell->index = i;
		free_all(cmd);
	}
}

int	pars_line(char *line, char **env)
{
	char	*av;
	t_shell	*shell;

	av = line_arg(line);
	shell = malloc(sizeof(t_shell));
	if (init_struct(shell, av) == -1)
		return (-1);
	if (shell->nb_cmd == 1 && find_built(shell, av) == 1)
		printf("pas de  bin\n");
//		exec_only_built(shell);
	if (pipex(shell, av, env) == -1)
	{
		free_all(shell->token);
		free(shell);
		return (-1);
	}
	free_all(shell->token);
	free(shell);
	return (1);
}