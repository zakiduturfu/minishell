/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:36:49 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/11 12:52:05 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
			else if (strcmp("echo", line) == 0)
				ft_echo(NULL, env);
			else if (strcmp("export", line) == 0)
				ft_export(&env, NULL);
			else if (strcmp("unset", line) == 0)
				ft_unset(&env, NULL);
			else if (line[0] != '\0')
				pars_line(line, &env);
			add_history(line);
			free(line);
		}
	}
}

int	process_one_built(t_shell *shell, char *line, char ***env)
{
	free(line);
	exec_only_built(shell, env);
	free_all(shell->token);
	free(shell->av);
	free(shell->pid);
	return (shell->status);
}

int	pars_line(char *line, char ***env)
{
	char	*av;
	t_shell	*shell;

	if (!is_empty_line(line))
		return (-1);
	shell = create_data();
	av = syntax_line(line, 0, 0);
	if (!av)
		return (-1);
	if (init_struct(shell, av) == -1)
		return (free(av), -1);
	if (check_line(shell, line))
		return (free(av), -1);
	if (shell->nb_cmd == 1 && find_built(shell) == 1)
		return (process_one_built(shell, av, env));
	else if (pipex(shell, av, env) == -1)
		return (-1);
	close(shell->pipefd[0]);
	wait_bin(shell);
	close_in_here(shell);
	free_shell(shell, NULL, 1);
	return (shell->status);
}
