/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:09:56 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/02 15:22:26 by hstephan         ###   ########.fr       */
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
	// chdir("~/");
	old_pwd(env, pwdposi);
	new = ft_strjoin("PWD", &(env[homeposi][4]));
	if (!new)
		return (1);
	ft_export_one_by_one(&env, new);
	free(new);
	return (0);
}

int	starting_directory(char **env, int posi)
{
	char			*new;

	new = ft_strdup("PWD=/");
	if (!new)
		return (1);
	free(env[posi]);
	env[posi] = new;
	return (0);
}

int	previous_directory(char **env, int posi)
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

int	too_many_args(char **tab)
{
	unsigned int	i;

	i = 0;
	printf("cd: string not in pwd: %s\n", tab[0]);
	ft_free_tab(tab);
	return (0);
}
