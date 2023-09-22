/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:36:49 by zlemery           #+#    #+#             */
/*   Updated: 2023/09/22 18:28:28 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/readline.h>
#include <sys/wait.h>

t_shell	*create_data(void)
{
	static t_shell *shell;
	
	return (shell);
}

int	init_struct(t_shell *shell, char *av)
{
	shell->fdout = 0;
	shell->c_here = 0;
	shell->fdin = 0;
	shell->prev_pipe = -1;
	shell->token = ft_split(av, '|');
	if (!shell->token)
		return (-1);
	shell->av = ft_strdup(av);
	if (!shell->av)
	{
		free_all(shell->token);
		return (-1);
	}
	shell->nb_cmd = count_cmd(shell->token);
	if (shell->nb_cmd)
		shell->pid = malloc(sizeof(int) * shell->nb_cmd);
	if (!shell->pid)
	{
		free(shell->av);
		free_all(shell->token);
		return (-1);
	}
	shell->nb_here = nb_heredoc(av);
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
	if (!new)
		return (NULL);
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
		else if (is_in_quote(line, i, line[i])
			&& (line[i] == ' ' || line[i] == '|'))
			new[j++] = -line[i++];
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	// printf("nouvelle ligne: %s\n", new);
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

void	test_cmd(t_shell *shell)
{
	int		i;
	int		j;
	char	**cmd;

	i = 0;
	while (i < shell->nb_cmd)
	{
		j = 0;
		cmd = init_start_cmd(shell, shell->token[i], 2);
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

int is_empty_line(char *line)
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

void	loop_shell(char **env)
{
	char 	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = readline("minishell>");
		if(line == NULL)
		{
			printf("EOF\n");
		}
		if (line != NULL)
		{
			if (ft_strcmp("exit", line) == 0)
				ft_exit(env);
			else if (strcmp("env", line) == 0)
				ft_env(env);
			else if (line[0] != '\0')
				pars_line(line, env);
			free(line);
		}
	}
}


int	pars_line(char *line, char **env)
{
	char	*av;
	t_shell	*shell;

	if (!is_empty_line(line))
		return (-1);
	shell = create_data();
	shell = malloc(sizeof(t_shell));
	av = line_arg(line);
	if (!av)
	{
		free(shell);
		return (-1);
	}
	if (init_struct(shell, av) == -1)
	{
		free(av);
		free(shell);
		return (-1);
	}
	if (shell->nb_cmd == 1 && find_built(shell) == 1)
		exec_only_built(shell);
	else if (pipex(shell, av, env) == -1)
		return (-1);
	close(shell->pipefd[0]);
	wait_bin(shell);
	close_in_here(shell);
	free_shell(shell, av);
	return (1);
}