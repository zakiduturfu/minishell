/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:22:08 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/20 18:16:21 by zlemery          ###   ########.fr       */
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

char	**delete_redir(char **line, int i, int j)
{
	char	**ret;
	int		size;

	size = count_redir(line);
	if (!size)
		return (free_all(line), NULL);
	ret = malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (free_all(line), NULL);
	while (line[++i])
	{
		if ((line[i][0] == '<' || line[i][0] == '>') && line[i + 1])
			i++;
		else
		{
			ret[j] = ft_strdup(line[i]);
			if (!ret[j])
				return (free_all(line), free_all(ret), NULL);
			j++;
		}
	}
	ret[j] = 0;
	free_all(line);
	return (ret);
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
