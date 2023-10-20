/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:22:08 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/11 16:57:01 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include <stdlib.h>

int	count_redir(char **line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i][0] == '<' || line[i][0] == '>') && line[i + 1])
			i++;
		else
			count++;
		i++;
	}
	return (count);
}

int	is_redir(char *redir)
{
	if (!ft_strcmp(">", redir))
		return (1);
	else if (!ft_strcmp(">>", redir))
		return (3);
	else if (!ft_strcmp("<", redir))
		return (2);
	else if (!ft_strcmp("<<", redir))
		return (4);
	return (0);
}

char	**delete_redir(char **line)
{
	int		i;
	int		j;
	char	**ret;
	int		size;

	i = -1;
	j = 0;
	size = count_redir(line);
	if (!size)
		return (free_all(line), NULL);
	ret = malloc(sizeof(char *) * (size + 1));
	while (line[++i])
	{
		if ((line[i][0] == '<' || line[i][0] == '>') && line[i + 1])
			i++;
		else
		{
			ret[j] = ft_strdup(line[i]);
			j++;
		}
	}
	ret[j] = 0;
	free_all(line);
	return (ret);
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

void	close_in_here(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->nb_here)
	{
		close(shell->here[i].here_pipe[0]);
		i++;
	}
}
