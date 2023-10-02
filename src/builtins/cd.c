/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/02 15:12:50 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	exec_cd(char **env, char **tab, int posi)
{
	unsigned int	i;

	i = 0;
	old_pwd(env, posi);
	while (tab && tab[i])
	{
		if (ft_strcmp("..", tab[i]) == 0)
			previous_directory(env, posi);
		// else if (ft_strcmp(".", tab[i]) != 0)
			// si repertoire ok
		i++;
	}
	return (0);
}

static int	try_exec_cd(char **env, char *directory)
{
	int				posi;
	char			**tab;
	unsigned int	i;

	posi = -1;
	i = 0;
	posi = find_var(env, "PWD");
	if (posi == -1)
		return (1);
	tab = ft_split(directory, '/');
	if (!tab)
		return (1);
	// while (tab[i])
	// {
	// 	ici on verifiera la validite de tout le chemin, si pas valide message d'erreur et quitte
	// 		// cd: no such file or directory: %s\n
	// 	i++;
	// }
	exec_cd(env, tab, posi);
	ft_free_tab(tab);
	return (0);
}

int	ft_cd(char **env, char *str)
{
	char			**tab;

	if (!str || str[0] == '\0')
		return (cd_home(env));
	tab = ft_nsplit(str, ' ', '\t');
	if (!tab)
		return (1);
	if (tab && ft_strcmp(tab[0], "/") != 0 && tab[1])
		return (too_many_args(tab));
	// faire le cas / pwihfp 
	try_exec_cd(env, tab[0]);
	return (0);
}
