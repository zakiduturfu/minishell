/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:09:56 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/20 21:42:17 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	old_pwd(char ***env, int pwdposi)
{
	char	*new;

	if (pwdposi != -1)
		new = ft_strjoin("OLDPWD", &((*env)[pwdposi][3]));
	else
		new = ft_strdup("OLDPWD=");
	if (!new)
		return (1);
	ft_export_one_by_one(env, new);
	free(new);
	return (0);
}

int	cd_home(char ***env, t_shell *shell)
{
	int		homeposi;

	homeposi = find_var(*env, "HOME");
	if (homeposi == -1)
	{
		printf("cd: HOME not set\n");
		shell->status = 1;
		return (1);
	}
	if (try_exec_cd(env, &(*env)[homeposi][5], -1, NULL) == 1)
		shell->status = 1;
	else
		shell->status = 0;
	return (0);
}

int	starting_directory(char **pwd, bool test)
{
	char			*new;

	new = ft_strdup("PWD=/");
	if (!new)
		return (1);
	free(*pwd);
	*pwd = new;
	if (test == 0 && chdir("/") != 0)
		return (1);
	return (0);
}

int	previous_directory(char **pwd, bool test)
{
	char			*new;
	unsigned int	i;

	i = 0;
	while ((*pwd)[i] != '\0')
		i++;
	i--;
	if (i <= 4)
		return (0);
	while (i > 0 && (*pwd)[i] != '/')
		i--;
	if (i <= 4)
		return (starting_directory(pwd, test));
	else
		new = ft_strndup((*pwd), i);
	if (!new)
		return (1);
	free(*pwd);
	(*pwd) = new;
	if (test == 0 && chdir(&((*pwd)[4])) != 0)
		return (1);
	return (0);
}

char	*start_directory(char *directory)
{
	char	*buf;
	char	*start;

	if (directory && directory[0] == '/')
		start = ft_strdup("PWD=/");
	else
	{
		buf = malloc(sizeof(char) * 1000);
		if (!buf)
			return (NULL);
		start = ft_strjoin("PWD=", getcwd(buf, 1000));
		free(buf);
	}
	return (start);
}
