/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:45:37 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/18 13:29:29 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	child_err(t_shell *shell, char **cmd, char **env, int i)
{
	ft_putstr_fd(cmd[i], 2);
	ft_putstr_fd(":command not found\n", 2);
	free_all(cmd);
	if (shell->nb_here)
		free(shell->here);
	if (shell->pipefd[1])
		close(shell->pipefd[1]);
	if (shell->path)
		free(shell->path);
	free(shell->av);
	free_all(shell->token);
	free_env_tab(env);
}

char	**get_cmd_path(char *cmd, char **env)
{
	int		i;
	char	*cmd_path;
	char	**path;

	i = 1;
	(void)cmd;
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
	if (ft_strchr(cmd, '/') && access(cmd, 0) == 0)
		return (ft_strdup(cmd));
	else
	{
		path = get_cmd_path(cmd, env);
		if (!path)
			return (NULL);
		while (path[++i])
		{
			tmp = ft_strjoin(path[i], "/");
			tab = ft_strjoin(tmp, cmd);
			free (tmp);
			if (access(tab, 0) == 0)
				return (find_path(tab, path));
			free(tab);
		}
		free_all(path);
	}
	return (NULL);
}

void	parent_process(t_shell *shell)
{
	close(shell->pipefd[1]);
	if (shell->prev_pipe != -1)
		close(shell->prev_pipe);
	shell->prev_pipe = shell->pipefd[0];
}

void	child_process(t_shell *shell, int i, char ***env)
{
	char	**cmd;

	shell->index = i;
	free(shell->pid);
	cmd = init_start_cmd(shell, shell->token[i], 2, *env);
	if (!cmd || (cmd_exist(cmd) == -1 && empty_cmd(cmd)))
	{
		if (cmd)
			free_all(cmd);
		ft_good_bye(shell, env);
	}
	i = cmd_exist(cmd);
	if (is_builtin(cmd[0]))
	{
		free_all(cmd);
		exit (process_built(shell, env, i));
	}
	if (cmd[0])
		shell->path = recup_path(cmd[i], *env);
	if (shell->path)
		ft_exec(shell, cmd, i, env);
	child_err(shell, cmd, *env, i);
	exit(127);
}
