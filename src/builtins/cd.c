/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/17 16:10:38 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int is_directory(char **pwd, char *dir, char **tab, int i)
{
	char		*path;
	struct stat	info;
	char		*slash;
	int			j;
	
	j = -1;
	slash = ft_strjoin(&((*pwd)[4]), "/");
	if (!slash)
		return (1);
	path = ft_strjoin(slash, dir);
	free(slash);
	if (!path)
		return (0);
	stat(path, &info);
	if (S_ISDIR(info.st_mode) != 1)
	{
		if (S_ISREG(info.st_mode) == 1)
			printf("cd: not a directory: ");
		else
			printf("cd: no such file or directory: ");
		while (++j <= i)
		{
			printf("%s", tab[j]);
			if (j < i)
				printf("/");
		}
		printf("\n");
	}
	free(path);
	return (S_ISDIR(info.st_mode));
}

static int	this_directory(char **pwd, char *dir)
{
	char			*slash;
	char			*new;

	slash = ft_strjoin(*pwd, "/");
	if (!slash)
		return (1);
	new = ft_strjoin(slash, dir);
	free(slash);
	if (!new)
		return (1);
	free(*pwd);
	*pwd = new;
	if (chdir(&((*pwd)[4])) != 0)
		return (1);
	return (0);
}

static int	exec_cd(char **env, char **tab, int posi)
{
	unsigned int	i;

	i = 0;
	old_pwd(env, posi);
	while (tab && tab[i])
	{
		if (ft_strcmp("..", tab[i]) == 0)
			previous_directory(&(env[posi]));
		else if (ft_strcmp(".", tab[i]) != 0)
			this_directory(&(env[posi]), tab[i]);
		i++;
	}
	return (0);
}

static int	ft_verif_path(char **tab, char *test)
{
	unsigned int i;

	i = 0;
	while (tab[i])
	{
		if (ft_strcmp("..", tab[i]) == 0)
			previous_directory(&test);
		else if (ft_strcmp(".", tab[i]) != 0)
		{
			if(!(is_directory(&test, tab[i], tab, i)))
			{
				free(test);
				return (0);
			}
			else
				this_directory(&test, tab[i]);
		}
		i++;
	}
	free(test);
	return (1);
}

int	try_exec_cd(char **env, char *directory)
{
	int				posi;
	char			**tab;
	char			*test;

	posi = -1;
	posi = find_var(env, "PWD");
	if (posi == -1)
		return (1);
	tab = ft_split(directory, '/');
	if (!tab)
		return (1);
	test = ft_strdup(env[posi]);
	if (!test)
		return (ft_free_tab(tab), 1);
	if (ft_verif_path(tab, test) == 1)
		exec_cd(env, tab, posi);
	ft_free_tab(tab);
	return (0);
}
