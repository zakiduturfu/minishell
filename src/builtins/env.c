/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/18 13:30:35 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(char **env)
{
	unsigned int	i;

	i = 0;
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
	env_cop = malloc(sizeof(char) * size);
	if (!env_cop)
		return (-1);
	while (++i < size)
	{
		printf("ici i = %i\n", i);
		printf("on copie la ligne %s\n", env[i]);
		env_cop[i] = env[i];
	}
	i = 0;
	while (i + 1 < size)
	{
		if (ft_strcmp(env_cop[i], env_cop[i + 1]) > 0)
		{
			tmp = env_cop[i];
			env_cop[i] = env_cop[i + 1];
			env_cop[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	ft_env(env_cop);
	free(env_cop);
	return (0);
}
