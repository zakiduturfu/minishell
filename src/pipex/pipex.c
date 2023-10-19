/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 03:13:43 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/19 16:32:00 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_process(t_shell *shell, int i, char ***env)
{
	if (pipe(shell->pipefd) == -1)
		return (-1);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGQUIT, &handler_cmd);
	signal(SIGINT, &handler_cmd);
	shell->pid[i] = fork();
	if (shell->pid[i] == -1)
	{
		close_all_pipe(shell);
		return (-1);
	}
	if (shell->pid[i] == 0)
		child_process(shell, i, env);
	else if (shell->pid[i] > 0)
		parent_process(shell);
	return (0);
}

int	exec_pipex(t_shell *shell, char ***env)
{
	int	i;

	i = 0;
	while (i < (shell->nb_cmd))
	{
		if (exec_process(shell, i, env) == -1)
			return (-1);
		if (find_built(shell, *env, i))
			waitpid(shell->pid[i], &shell->status, 0);
		if (shell->nb_here && strstr(shell->token[i], "<<"))
			shell->c_here++;
		i++;
	}
	return (0);
}

int	pipex(t_shell *shell, char *av, char ***env)
{
	free(av);
	if (create_here(shell) == -1)
		return (-1);
	if (init_here(shell, *env) == -1)
		return (-1);
	if (exec_pipex(shell, env) == -1)
	{
		free_shell(shell, NULL, 1);
		return (-1);
	}
	return (0);
}

char	*ft_strstr(char *str, char *needle)
{
	int	i;
	int	j;

	i = 0;
	if (!needle[i])
		return (str);
	while (str[i])
	{
		j = 0;
		while (needle[j] == str[i + j])
		{
			if (needle[j + 1] == '\0')
				return (str + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

void	ft_exec(t_shell *shell, char **cmd, int i, char ***env)
{
	if (execve(shell->path, cmd + i, *env) == -1)
	{
		perror("execve");
		close(shell->pipefd[0]);
		if (shell->pipefd[1])
			close(shell->pipefd[1]);
		free(shell->av);
		if (shell->path)
			free(shell->path);
		if (cmd)
			free_all(cmd);
		free_all(shell->token);
		free_env_tab(*env);
		exit(2);
	}
}
