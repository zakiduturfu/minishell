/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:04:02 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/12 18:56:37 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	size_env(char **env)
{
	int	count;

	count = 0;
	if (!env)
		return (0);
	while (env[count])
		count++;
	return (count);
}

void	free_env_tab(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	*ret_status(char *before, char *after, char *status)
{
	char	*tmp;
	char	*new_line;

	tmp = ft_strjoin(before, status);
	free(status);
	free(before);
	if (!tmp)
	{
		free(after);
		return (NULL);
	}
	new_line = ft_strjoin(tmp, after);
	free(tmp);
	free(after);
	if (!new_line)
		return (NULL);
	return (new_line);
}

void	stat_expand(char **tab, char *str, int i, t_shell *shell)
{
	tab[0] = get_before_expand(str, i);
	if (!tab[0])
		return ;
	tab[1] = get_after_expand(str + i + 2);
	if (!tab[1])
		free_expand(tab, 1);
	tab[2] = ft_itoa(shell->status);
	if (!tab[2])
		free_expand(tab, 2);
	tab[3] = ret_status(tab[0], tab[1], tab[2]);
}
