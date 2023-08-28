/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:45:37 by zlemery           #+#    #+#             */
/*   Updated: 2023/08/25 16:55:17 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_err(t_shell *shell, char **cmd, char **env, char *av)
{
	int	i;

	i = -1;
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(":command not found\n", 2);
	while (cmd[++i])
		free(cmd[i]);
	free(cmd);
	if (shell->pipefd[1])
		close(shell->pipefd[1]);
	free(av);
	free(shell->path);
	free_all(shell->token);
	free_env_tab(env);
	free(shell);
}

char	**get_cmd_path(char **env)
{
	int		i;
	char	*cmd_path;
	char	**path;

	i = 1;
	cmd_path = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			cmd_path = env[i] + 5;
		i++;
	}
	if (!cmd_path)
		return (NULL);
	path = ft_split(cmd_path, ':');
	return (path);
}

char	*recup_path(char *cmd, char **env)
{
	char	*tmp;
	char	*tab;
	char	**path;
	int		i;

	i = -1;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, 0) == 0)
			return (cmd);
	}
	else
	{
		path = get_cmd_path(env);
		while (path[++i])
		{
			tmp = ft_strjoin(path[i], "/");
			tab = ft_strjoin(tmp, cmd);
			free (tmp);
			if (access(tab, 0) == 0)
				return (tab);
			free(tab);
		}
		free_all(path);
	}
	return (NULL);
}

void	parent_process(t_shell *shell)
{
	if (shell->pipefd[1] != -1)
		close(shell->pipefd[1]);
	if (shell->prev_pipe == -1)
		close(shell->prev_pipe);
	shell->prev_pipe = shell->pipefd[0];
	close(shell->pipefd[0]);
}

void	child_process(t_shell *shell, int i, char *av, char **env)
{
	char	**cmd;

	shell->index = i;
	free(shell->pid);
	cmd = init_start_cmd(shell, shell->token[i], 2, av);
	if (is_builtin(cmd[0]))
	{
		printf("exec built\n");
		exit(0);
	}
	if (cmd[0])
		shell->path = recup_path(cmd[0], env);
	if (shell->path)
	{
		if (execve(shell->path, cmd, env) == -1)
		{
			perror("execve");
			exit(2);
		}
	}
	child_err(shell, cmd, env, av);
	exit(127);
}