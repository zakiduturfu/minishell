/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:36:49 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/09 16:38:37 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <signal.h>

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

char	*line_arg(char *line, int i, int j)
{
	char	*new;

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

// void	test_cmd(t_shell *shell)
// {
// 	int		i;
// 	int		j;
// 	char	**cmd;

// 	i = 0;
// 	while (i < shell->nb_cmd)
// 	{
// 		j = 0;
// 		cmd = init_start_cmd(shell, shell->token[i], 2);
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

int	is_empty_line(char *line)
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

void	loop_shell(char **env, char *line)
{
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, &handler_sig);
		line = readline("minishell>");
		if (line == NULL)
		{
			printf("exit\n");
			free_env_tab(env);
			exit(2);
		}
		if (line != NULL)
		{
			if (ft_strcmp("exit", line) == 0)
				ft_exit(env);
			else if (ft_strcmp("cd", line) == 0)
				ft_cd(env, NULL);
			else if (strcmp("env", line) == 0)
				ft_env(env);
			else if (strcmp("pwd", line) == 0)
				ft_pwd(env, NULL);
			else if (strcmp("echo", line) == 0)
				ft_echo(NULL, env);
			else if (strcmp("export", line) == 0)
				ft_export(&env, NULL);
			else if (strcmp("unset", line) == 0)
				ft_unset(&env, NULL);
			else if (line[0] != '\0')
				pars_line(line, &env);
			free(line);
		}
	}
}

int	pars_line(char *line, char ***env)
{
	char	*av;
	t_shell	*shell;

	if (!is_empty_line(line))
		return (-1);
	shell = create_data();
	av = line_arg(line, 0, 0);
	if (!av)
		return (-1);
	if (init_struct(shell, av) == -1)
		return (free(av), -1);
	if (check_line(shell, line))
		return (free(av), -1);
	if (shell->nb_cmd == 1 && find_built(shell) == 1)
		exec_only_built(shell, env);
	else if (pipex(shell, av, env) == -1)
		return (-1);
	close(shell->pipefd[0]);
	wait_bin(shell);
	close_in_here(shell);
	free_shell(shell, NULL, 1);
	return (shell->status);
}
