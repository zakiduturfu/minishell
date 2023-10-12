/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:51:50 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/12 18:39:18 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	nb_heredoc(char *line)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (line[++i])
	{
		if ((line[i] == '<' && line[i - 1] != '\\')
			&& line[i + 1] == '<')
		{
			count++;
			i++;
		}
	}
	return (count);
}

int	recup_delim2(t_shell *shell, char **tmp, int j)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (!ft_strcmp(tmp[i], "<<"))
		{
			shell->here[j].lim = delete_quote(tmp[i + 1], 0, 0);
			free(tmp[i]);
			i++;
			pipe(shell->here[j].here_pipe);
			j++;
		}
		else
			free(tmp[i]);
		i++;
	}
	free(tmp);
	return (j);
}

int	recup_delim1(t_shell *shell)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	j = 0;
	while (shell->token[++i])
	{
		tmp = ft_split(shell->token[i], ' ');
		if (!tmp)
			return (-1);
		fix_quote((signed char **)tmp);
		tmp = find_expansion(shell, tmp);
		if (check_redirections(tmp) == -1)
		{
			free_all(tmp);
			return (-1);
		}
		j = recup_delim2(shell, tmp, j);
	}
	return (1);
}
