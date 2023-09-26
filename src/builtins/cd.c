/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/09/26 18:03:45 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	cd_home(char **env)
{
	int		posi;
	char	*new;

	posi = -1;
	posi = find_var(env, "HOME");
	if (posi == -1)
		return (1);
	new = ft_strjoin("PWD", &(env[posi][4]));
	if (!new)
		return (1);
	ft_export_one_by_one(env, new);
	free(new);
	return (0);
	}


static int	starting_directory(char **env, int posi)
{
	char			*new;
	
	new = ft_strdup("PWD=/");
	if (!new)
		return (1);
	free(env[posi]);
	env[posi] = new;
	return (0);
}

static int	previous_directory(char **env, int posi)
{
	char			*new;
	unsigned int	i;

	i = 0;
	while (env[posi][i] != '\0')
		i++;
	i--;
	if (i <= 4)
		return (0);
	while (i > 0 && env[posi][i] != '/')
		i--;
	if (i <= 4)
		return (starting_directory(env, posi));
	else
		new = ft_strndup(env[posi], i);
	if (!new)
		return (1);
	free(env[posi]);
	env[posi] = new;
	return (0);
}

static int	exec_cd(char **env, char **tab, int posi)
{
	unsigned int	i;

	i = 0;
	printf("au debut de exec cd\n");
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
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (0);
}

static int 	too_many_args(char **tab)
{
	unsigned int	i;

	i = 0;
	printf("cd: string not in pwd: %s\n", tab[0]);
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (0);
}

int	ft_cd(char **env, char *str)
{
	char			**tab;

	if (str && open_quote(str) == 1)
		return (dquote());
	if (!str || str[0] == '\0')
		return (cd_home(env));
	tab = ft_nsplit(str, ' ', '\t');
	if (!tab)
		return (1);
	if (tab && ft_strcmp(tab[0], "/") != 0 && tab[1])
		return (too_many_args(tab));
	// faire le cas / pwihfp 
	printf("avant try exec on a tab[0] = %s\n", tab[0]);
	try_exec_cd(env, tab[0]);
	free(tab[0]);
	free(tab);
	return (0);
}
