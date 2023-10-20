/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:36:49 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/20 18:14:52 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	exec_line(char *line, char ***env)
{
	if (ft_strcmp("cd", line) == 0)
		ft_cd(env, NULL);
	else if (ft_strcmp("env", line) == 0)
		ft_env(*env, NULL);
	else if (ft_strcmp("echo", line) == 0)
		ft_echo(NULL);
	else if (ft_strcmp("export", line) == 0)
		ft_export(env, NULL);
	else if (ft_strcmp("unset", line) == 0)
		ft_unset(env, NULL);
	else if (line[0] != '\0')
		pars_line(line, env);
}

void	loop_shell(char **env, char *line)
{
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handler_sig);
		line = readline("minishell>");
		if (!is_empty_line(line))
			free(line);
		else if (line == NULL)
		{
			printf("exit\n");
			free_env_tab(env);
			exit(2);
		}
		else if (line != NULL)
		{
			exec_line(line, &env);
			add_history(line);
			free(line);
		}
	}
}

int	process_one_built(t_shell *shell, char *line, char ***env)
{
	free(shell->pid);
	shell->builtin = dup(STDIN_FILENO);
	shell->builtout = dup(STDOUT_FILENO);
	free(line);
	exec_only_built(shell, env, 0, NULL);
	free_all(shell->token);
	free(shell->av);
	dup_and_close(shell->builtin, STDIN_FILENO);
	dup_and_close(shell->builtout, STDOUT_FILENO);
	return (shell->status);
}

void	wait_bin(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->nb_cmd)
	{
		waitpid(shell->pid[i], &shell->status, 0);
		if (WIFEXITED(shell->status))
			shell->status = WEXITSTATUS(shell->status);
		i++;
	}
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
	if (shell->nb_cmd == 1 && find_built(shell, *env, 0) == 1)
		return (process_one_built(shell, av, env));
	else if (pipex(shell, av, env) == -1)
		return (-1);
	close(shell->pipefd[0]);
	wait_bin(shell);
	close_in_here(shell);
	free_shell(shell, NULL, 1);
	return (shell->status);
}
