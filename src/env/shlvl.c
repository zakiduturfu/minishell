/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:08:35 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/12 18:45:00 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*modify_var_env(char *name, char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(name, env[i], 6))
			break ;
		i++;
	}
	free(env[i]);
	env[i] = ft_strdup(var);
	free(var);
	return (env[i]);
}

char	*recup_val_shlvl(char **env)
{
	int		i;
	int		j;
	int		k;
	char	*val;

	i = 0;
	j = 0;
	k = 0;
	while (env[i])
	{
		if (!ft_strncmp("SHLVL=", env[i], 6))
			break ;
		i++;
	}
	while (env[i][j] != '=')
		j++;
	j++;
	val = malloc(sizeof(char) * ((ft_strlen(env[i]) - j) + 1));
	if (!val)
		return (NULL);
	while (env[i][j])
		val[k++] = env[i][j++];
	val[k] = '\0';
	return (val);
}

int	increment_shlvl(char **env)
{
	char	*val;
	char	*new_var;
	int		nb;

	if (!env)
		return (-1);
	val = getenv("SHLVL");
	if (!val)
		return (-1);
	nb = ft_atoi(val);
	nb += 1;
	val = ft_itoa(nb);
	new_var = ft_strjoin("SHLVL=", val);
	free(val);
	if (!modify_var_env("SHLVL=", env, new_var))
		return (-1);
	return (1);
}
