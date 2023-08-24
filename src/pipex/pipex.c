/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 03:13:43 by zlemery           #+#    #+#             */
/*   Updated: 2023/08/24 16:39:45 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/rltypedefs.h>
#include <stdlib.h>

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
	if (ft_strchr("/", cmd[0]))
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
	}
	return (NULL);
}

void	child_err(t_shell *shell, char **cmd)
{
	int	i;

	i = -1;
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("command not found", 2);
	while (cmd[i++])
		free(cmd[i]);
	free(cmd);
	if (shell->pipefd[1])
		close(shell->pipefd[1]);
}
void	parent_process(t_shell *shell)
{
	if (shell->pipefd[1] != -1)
		close(shell->pipefd[1]);
	if (shell->prev_pipe == -1)
		close(shell->prev_pipe);
	shell->prev_pipe = shell->pipefd[0];
}

void	exec_child(t_shell *shell, char **cmd, char **env)
{
		if (execve(shell->path, cmd, env) == -1)
		{
			perror("execve");
			exit(2);
		}
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
//		exec_builtin(shell);
	if (cmd[0])
		shell->path = recup_path(cmd[0], env);
	if (shell->path)
		exec_child(shell, cmd, env);
	child_err(shell, cmd);
	exit(127);
}

int	exec(t_shell *shell, int i, char *av, char **env)
{
	if (pipe(shell->pipefd) == -1)
		return (-1);
	shell->pid[i] = fork();
	if (shell->pid[i] == -1)
		return (-1);
	if (shell->pid[i] == 0)
		child_process(shell, i, av, env);
	else if (shell->pid[i] > 0)
		parent_process(shell);
	return (0);
}

int	exec_process(t_shell *shell, char *av, char **env)
{
	int	i;

	i = -1;
	while (++i < (shell->nb_cmd))
	{
		if (find_built(shell, av))
			printf("BUILT\n");
		if (exec(shell, i, av, env) == -1)
			return (-1);
		//waitpid
	}
	return (0);
}

int	pipex(t_shell *shell, char *av, char **env)
{
	// if (here_alloc(shell) == -1)
	// 	return (-1);
	// if (exec_hd(shell) == -1)
	// 	return (-1);
	if (exec_process(shell, av, env) == -1)
		return (-1);
	return (0);
}
