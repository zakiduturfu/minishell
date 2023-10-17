/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:42:04 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/16 17:55:29 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	empty_cmd(char **cmd)
{
	if (!cmd[0])
		return (1);
	if (cmd[0][0] == 0)
		return (1);
	return (0);
}

int	cmd_exist(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] != 0)
			return (i);
		i++;
	}
	return (-1);
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

char	*find_path(char *tab, char **path)
{
	free_all(path);
	return (tab);
}

void	ft_good_bye(t_shell *shell, char ***env)
{
	if (shell->pipefd[0])
		close(shell->pipefd[0]);
	if (shell->pipefd[1])
		close(shell->pipefd[1]);
	free(shell->av);
	free_all(shell->token);
	free_env_tab(*env);
	exit(0);
}
