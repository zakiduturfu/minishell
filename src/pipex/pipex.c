/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 03:13:43 by zlemery           #+#    #+#             */
/*   Updated: 2023/08/02 03:55:59 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_cmd_path(char **env)
{
	int		i;
	char	*cmd_path;
	char	**path;

	i = 0;
	if (env[i])
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			cmd_path = env[i] + 5;
	}
	if (!cmd_path)
		return (NULL);
	path = ft_split(cmd_path, ':');
	free(cmd_path);
	return (path);
}

char	*recup_path(t_shell *shell, char *cmd)
{
	char	*tmp;
	char	*tab;
	char	**path;
	int		i;

	i = -1;
	if (ft_strchr("/", cmd))
	{
		if (access(cmd, 0) == 0)
			return (cmd);
	}
	else
	{
		path = get_cmd_path(shell->env);
		while (path[i++])
		{
			tmp = ft_strjoin(path[i], "/");
			tab = ft_strjoin(tmp, tab);
			free (tmp);
			if (access(tab, 0) == 0)
				return (tab);
			free(tab);
		}
		return (NULL);
	}
}

void	child_err(t_shell *shell, char **cmd)
{
	int	i;

	i = -1;
	/*messsage d'erreur commande introuvable*/
	while (cmd[i++])
		free(cmd[i]);
	free(cmd);
	if (pipefd[1])
		close(pipefd[1]);
}
void	parent_process(t_shell *shell)
{
	if (shell->pipefd[1] != -1)
		close(shell->pipefd[1]);
	if (shell->prev_pipe)
		close(shell->prev_pipe);
	shell->prev_pipe = shell->pipefd[0];
}
void	child_process(t_shell *shell, int i)
{
	char	**cmd;

	cmd = init_start_cmd(shell, shell->token[i], 2);
	if (!cmd)
		return (-1);
	/*if builtin finder*/
	if (cmd[0])
		shell->path = recup_path(shell, cmd[0]);
	if (shell->path)
		exec
	child_err(shell, cmd);
	exit(0);

}

int	exec(t_shell *shell, int i)
{
	if (pipe(shell->pipefd) == -1)
		return (-1);
	shell->pid[i] = fork();
	if (shell->pid[i] == -1)
		return (-1);
	if (!shell->pid)
		child_process(shell, i);
	else if (shell->pid > 0)
		parent_process(shell);
	return (0);
}


int	exec_process(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i + shell->nb_here < (shell->nb_cmd + shell->nb_here))
	{
		if (exec(shell, i) == -1)
			return (-1);
		if (split_built(shell))
			//wait_pid
		/*waitpid*/

	}
}


int	exec_pipex(t_shell *shell)
{
	if (here_alloc(shell) == -1)
		return (-1);
	if (exec_hd(shell) == -1)
		return (-1);
	if (exec_process(shell) == -1)
		return (-1);
	return (0);
}

void	dup_and_close(int oldfd, int newfd)
{
	dup2(oldfd, newfd);
	close(oldfd);
}