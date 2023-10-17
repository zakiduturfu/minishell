/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:59:31 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/16 17:40:26 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*create_env(void)
{
	static t_env	env;

	return (&env);
}

char	*dup_var_name(char *str, int index)
{
	int		i;
	char	*var;

	i = 0;
	var = malloc(sizeof(char) * (index + 1));
	if (!var)
		return (NULL);
	while (i < index)
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

char	*find_var_name(char *env)
{
	int		i;
	char	*ret;

	i = 0;
	while (env[i] != '=')
		i++;
	ret = dup_var_name(env, i);
	return (ret);
}

char	*recup_env_ligne(char *str)
{
	char	*var;
	char	*ret;
	char	*value;

	var = find_var_name(str);
	if (!var)
		return (NULL);
	value = getenv(var);
	ret = ft_strjoin(var, "=");
	free(var);
	var = ft_strjoin(ret, value);
	free(ret);
	if (!var)
		return (NULL);
	return (var);
}

char	**recup_env(char **env)
{
	char	**ret;
	int		size;
	int		i;

	i = 0;
	size = size_env(env);
	ret = malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	while (env[i])
	{
		ret[i] = recup_env_ligne(env[i]);
		if (!ret[i])
		{
			free_env_tab(ret);
			return (NULL);
		}
		i++;
	}
	ret[i] = 0;
	return (ret);
}
