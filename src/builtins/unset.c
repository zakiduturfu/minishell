/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/20 21:48:54 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_erase_var(char ***env, int posi)
{
	int		size;
	char	**newenv;
	int		i;

	i = 0;
	size = size_env(*env);
	size--;
	newenv = malloc(sizeof(char *) * (size + 1));
	if (!newenv)
		return (1);
	newenv[size] = NULL;
	free((*env)[posi]);
	while (i < posi)
	{
		newenv[i] = (*env)[i];
		i++;
	}
	while (i < size)
	{
		newenv[i] = (*env)[i + 1];
		i++;
	}
	free(*env);
	*env = newenv;
	return (0);
}

static int	ft_unset_one_by_one(char ***env, char *str)
{
	int	posi;

	posi = find_var(*env, str);
	if (posi == -1)
		return (0);
	if (ft_erase_var(env, posi) == 1)
		return (1);
	return (0);
}

int	ft_unset(char ***env, char **tab, t_shell *shell)
{
	unsigned int	i;
	int				tmpstat;
	bool			alwaysgood;

	alwaysgood = 1;
	tmpstat = shell->status;
	i = 0;
	if (!tab || !(tab[0]) || tab[0][0] == '\0')
	{
		shell->status = 0;
		return (0);
	}
	while (tab[i])
	{
		tmpstat = ft_unset_one_by_one(env, tab[i]);
		if (tmpstat != 0)
		{
			shell->status = tmpstat;
			alwaysgood = 0;
		}
		i++;
	}
	if (alwaysgood == 1)
		shell->status = 0;
	return (0);
}
