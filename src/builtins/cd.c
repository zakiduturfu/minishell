/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/20 22:45:25 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_directory(char **pwd, char *dir, char *initialpath)
{
	char		*path;
	struct stat	info;
	char		*slash;

	slash = ft_strjoin(&((*pwd)[4]), "/");
	if (!slash)
		return (1);
	path = ft_strjoin(slash, dir);
	free(slash);
	if (!path)
		return (0);
	if (stat(path, &info) == -1)
	{
		printf("cd: %s: No such file or directory\n", initialpath);
		return (free(path), 0);
	}
	if (S_ISDIR(info.st_mode) != 1)
	{
		printf("cd: %s: Not a directory\n", initialpath);
		return (free(path), 0);
	}
	free(path);
	return (S_ISDIR(info.st_mode));
}

static int	this_directory(char **pwd, char *dir, bool test, char *initialpath)
{
	char	*slash;
	char	*new;

	if (ft_strcmp("PWD=/", *pwd) != 0)
		slash = ft_strjoin(*pwd, "/");
	else
		slash = ft_strdup(*pwd);
	if (!slash)
		return (1);
	new = ft_strjoin(slash, dir);
	free(slash);
	if (!new)
		return (1);
	free(*pwd);
	*pwd = new;
	if (access(&((*pwd)[4]), F_OK | X_OK) != 0)
	{
		printf("cd: %s: Permission denied\n", initialpath);
		return (1);
	}
	if (test == 0 && chdir(&((*pwd)[4])) != 0)
		return (1);
	return (0);
}

static int	exec_cd(char ***env, char **tab, int posi, char *start)
{
	unsigned int	i;

	i = 0;
	old_pwd(env, posi);
	free((*env)[posi]);
	(*env)[posi] = start;
	if (chdir((&((*env)[posi][4]))) != 0)
		return (1);
	while (tab && tab[i])
	{
		if (ft_strcmp("..", tab[i]) == 0)
		{
			if (previous_directory(&((*env)[posi]), 0, NULL, 0) == 1)
				return (1);
		}
		else if (ft_strcmp(".", tab[i]) != 0)
		{
			if (this_directory(&((*env)[posi]), tab[i], 0, NULL) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

static int	ft_verif_path(char **tab, char *test, char *initialpath, int i)
{
	while (tab[i])
	{
		if (ft_strcmp("..", tab[i]) == 0)
		{
			if (previous_directory(&test, 1, initialpath, 0) == 1)
				return (1);
		}
		else if (ft_strcmp(".", tab[i]) != 0)
		{
			if (!(is_directory(&test, tab[i], initialpath)))
			{
				free(test);
				return (1);
			}
			else if (this_directory(&test, tab[i], 1, initialpath) == 1)
			{
				free(test);
				return (1);
			}
		}
		i++;
	}
	return (free(test), 0);
}

int	try_exec_cd(char ***env, char *directory, int posi, char *start)
{
	char	**tab;
	char	*test;

	posi = find_var(*env, "PWD");
	while (posi == -1)
	{
		posi = find_var(*env, "PWD");
		ft_export_one_by_one(env, "PWD=");
	}
	start = start_directory(directory);
	if (!start)
		return (1);
	tab = ft_split(directory, '/');
	if (!tab)
		return (free(start), 1);
	test = ft_strdup(start);
	if (!test)
		return (free(start), ft_free_tab(tab), 1);
	if (ft_verif_path(tab, test, directory, 0) == 0)
		if (exec_cd(env, tab, posi, start) == 0)
			return (ft_free_tab(tab), 0);
	return (free(start), ft_free_tab(tab), 1);
}
