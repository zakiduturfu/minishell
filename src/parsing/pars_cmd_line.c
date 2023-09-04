/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaki <zaki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:36:49 by zlemery           #+#    #+#             */
/*   Updated: 2023/08/25 20:37:16 by zaki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/readline.h>
#include <stdint.h>

static int	init_struct(t_shell *shell, char *av)
{
	shell->index = 0;
	shell->fdin = 0;
	shell->fdout = 0;
	shell->prev_pipe = 0;
	shell->token = split_token(av, '|', av);
	if (!shell->token)
		return (-1);
	shell->nb_cmd = count_cmd(shell->token);
	if (shell->nb_cmd)
		shell->pid = malloc(sizeof(int) * shell->nb_cmd);
	if (!shell->pid)
		return (-1);
	ft_lines_history(shell, av);
	return (0);
}

static char	*space_sep(char *line)
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

static char	*line_arg(char *line)
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
//	printf("nouvelle ligne: %s\n", new);
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

// static void	test_cmd(t_shell *shell, char *av)
// {
// 	int		i;
// 	int		j;
// 	char	**cmd;

// 	i = 0;
// 	while (i < shell->nb_cmd)
// 	{
// 		j = 0;
// 		cmd = init_start_cmd(shell, shell->token[i], 2, av);
// 		if (cmd)
// 		{
// 			while (cmd[j])
// 			{
// 				printf("cmd = %s\n", cmd[j]);
// 				j++;
// 			}
// 		}
// 		printf("fdin = %d\n", shell->fdin);
// 		printf("fdout = %d\n", shell->fdout);
// 		printf("--------------------------\n");
// 		i++;
// 		shell->index = i;
// 		free_all(cmd);
// 	}
// }

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && (line[i] < 7 || line[i] > 13))
			return (1);
		i++;
	}
	return (0);
}

int	pars_line(char *line, t_shell *shell, int i, char *av)
{
	if (!is_empty_line(line))
		return (-1);
	av = line_arg(line);
	if (init_struct(shell, av) == -1)
		return (-1);
	if (shell->nb_cmd == 1 && find_built(shell, av) == 1)
		exec_only_built(shell);
	else
	{
		if (pipex(shell, av, shell->env) == -1)
		{
			free_all(shell->token);
			free(shell);
			return (-1);
		}
		close(shell->pipefd[0]);
		while (i < shell->nb_cmd)
		{
			waitpid(shell->pid[i], NULL, 0);
			i++;
		}
	}
	free(shell->pid);
	free_all(shell->token);
	return (1);
}
