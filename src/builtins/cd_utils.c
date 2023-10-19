/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:09:56 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/19 16:15:26 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	old_pwd(char **env, int pwdposi)
{
	char	*new;

	new = ft_strjoin("OLDPWD", &(env[pwdposi][3]));
	if (!new)
		return (1);
	ft_export_one_by_one(&env, new);
	free(new);
	return (0);
}

int	cd_home(char **env)
{
	int		homeposi;
	int		pwdposi;
	char	*new;

	homeposi = -1;
	pwdposi = -1;
	homeposi = find_var(env, "HOME");
	if (homeposi == -1)
		return (1);
	pwdposi = find_var(env, "PWD");
	if (pwdposi == -1)
		return (1);
	old_pwd(env, pwdposi);
	new = ft_strjoin("PWD", &(env[homeposi][4]));
	if (!new)
		return (1);
	ft_export_one_by_one(&env, new);
	free(new);
	if (chdir(&(env[homeposi][5])) != 0)
		return (1);
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
