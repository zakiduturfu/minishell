/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:04:02 by zlemery           #+#    #+#             */
/*   Updated: 2023/08/25 16:42:26 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	free_history(t_lines *lines)
{
	t_lines *tmp;
	t_lines *tmpnext;

	tmp = lines;
	tmpnext = tmp->next;
	while (tmp)
	{
		free(tmp);
		tmp = tmpnext;
		tmpnext = tmp->next;
	}
	free(lines);
}

void	ft_free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->lines)
		free_history(shell->lines);
	if (shell->env)
		free_env_tab(shell->env);
	free(shell);
}

int	size_env(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count++;
	return (count);
}

void	free_env_tab(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
