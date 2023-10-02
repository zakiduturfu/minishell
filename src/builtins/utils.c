/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/02 11:38:05 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_and_return(char *str, int i)
{
	printf("%s", str);
	return (i);
}

int	find_var(char **env, char *var)
{
	unsigned int	size;
	unsigned int	i;

	i = 0;
	if (!env)
		return (-1);
	size = size_env(env);
	while (i < size)
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**ft_split_cmd(char *token, char **tab, unsigned int i)
{
	while ((token[i] != ' ' || token[i] == '\t') && token[i] != '\0')
		i++;
	tab = malloc (sizeof(char *) * 3);
	if (!tab)
		return (NULL);
	tab[2] = NULL;
	tab[0] = malloc(sizeof(char) * (i + 1));
	if (!(tab[0]))
	{
		free(tab);
		return (NULL);
	}
	i = 0;
	while ((token[i] != ' ' || token[i] == '\t') && token[i] != '\0')
	{
		tab[0][i] = token[i];
		i++;
	}
	tab[0][i] = '\0';
	while (token[i] == ' ' || token[i] == '\t')
		i++;
	tab[1] = ft_strdup(&(token[i]));
	if (!tab[1])
	{
		ft_free_tab(tab);
		return (NULL);
	}
	return (tab);
}

void	ft_free_tab(char **tab)
{
	unsigned int i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

int		ft_ordonned_env(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!env)
		return (-1);
	while (env[i + 1] != NULL)
	{
		if (ft_strcmp(env[i], env[i + 1]) > 0)
		{
			tmp = env[i];
			env[i] = env[i + 1];
			env[i + 1] = tmp;	
			i = -1;
		}
		i++;
	}
	ft_env(env);
	return (0);
}
