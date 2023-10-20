/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/20 20:55:53 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(char **env, char **tab)
{
	unsigned int	i;

	i = 0;
	if (tab && tab[0] && tab[0][0] != '\0')
	{
		printf("env: ‘%s’: No such file or directory\n", tab[0]);
		return (0);
	}
	if (!env)
		return (1);
	while (env[i] != NULL)
	{
		printf("%s \n", env[i]);
		i++;
	}
	return (0);
}

int	ft_ordonned_env(char **env, char *tmp, int i, char **env_cop)
{
	int	size;

	if (!env)
		return (-1);
	size = size_env(env);
	env_cop = malloc(sizeof(char *) * (size + 1));
	if (!env_cop)
		return (-1);
	while (++i < size + 1)
		env_cop[i] = env[i];
	i = -1;
	while (++i < size - 1)
	{
		if (ft_strcmp(env_cop[i], env_cop[i + 1]) > 0)
		{
			tmp = env_cop[i];
			env_cop[i] = env_cop[i + 1];
			env_cop[i + 1] = tmp;
			i = -1;
		}
	}
	i = -1;
	while (++i < size)
		printf("export %s\n", env_cop[i]);
	return (free(env_cop), 0);
}
