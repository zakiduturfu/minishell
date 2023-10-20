/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/20 15:18:53 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_directory(char **pwd, char *dir, char **tab, int i)
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
		printf("cd: no such file or directory: ");
		print_path(i, tab);
		return (free(path), 0);
	}
	if (S_ISDIR(info.st_mode) != 1)
	{
		printf("cd: not a directory: ");
		print_path(i, tab);
	}
	free(path);
	return (S_ISDIR(info.st_mode));
}

static int	this_directory(char **pwd, char *dir, bool test)
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
			previous_directory(&((*env)[posi]), 0);
		else if (ft_strcmp(".", tab[i]) != 0)
			this_directory(&((*env)[posi]), tab[i], 0);
		i++;
	}
	return (0);
}

static int	ft_verif_path(char **tab, char *test)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_strcmp("..", tab[i]) == 0)
			previous_directory(&test, 1);
		else if (ft_strcmp(".", tab[i]) != 0)
		{
			if (!(is_directory(&test, tab[i], tab, i)))
			{
				free(test);
				return (0);
			}
			else
				this_directory(&test, tab[i], 1);
		}
		i++;
	}
	free(test);
	return (1);
}

int	try_exec_cd(char ***env, char *directory, int posi, char *buf)
{
	char	**tab;
	char	*test;
	char	*start;

	while (posi == -1)
	{
		posi = find_var(*env, "PWD");
		ft_export_one_by_one(env, "PWD=");
	}
	if (!directory || directory[0] == '\0' || directory[0] == '/')
		start = ft_strdup("PWD=/");
	else
	{
		buf = malloc(sizeof(char) * 1000);
		if (!buf)
			return (1);
		start = ft_strjoin("PWD=", getcwd(buf, 1000));
		free(buf);
	}
	if (!start)
		return (1);
	tab = ft_split(directory, '/');
	if (!tab)
		return (free(start), 1);
	test = ft_strdup(start);
	if (!test)
		return (free(start), ft_free_tab(tab), 1);
	if (ft_verif_path(tab, test) == 1)
		exec_cd(env, tab, posi, start);
	else
		free(start);
	ft_free_tab(tab);
	return (0);
}
