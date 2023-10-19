/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/19 18:59:05 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_parse_var(char *str, unsigned int *i)
{
	if (!str || str[0] == '\0')
		return (0);
	if (str[0] == '=')
		return (print_and_return("zsh: bad assignment\n", -1));
	while (str[*i] != '\0' && str[*i] != '=')
	{
		if (str[*i] == '-')
		{
			ft_putstr_fd("export: not valid in this context: ", 1);
			ft_putnstr_fd(str, 1, *i + 1);
			ft_putstr_fd("\n", 1);
			return (-1);
		}
		*i = *i + 1;
	}
	if (str[*i] == '\0')
		return (-1);
	*i = *i + 1;
	return (0);
}

static int	ft_change_val(char **env,
		unsigned int posi, char *val, unsigned int i)
{
	char	*newvar;
	char	*newval;
	char	*new;

	if (!val || val[0] == '\0' || val[0] == ' ' || val[0] == '\t')
		return (0);
	newvar = ft_strndup(env[posi], i);
	if (!newvar)
		return (-1);
	newval = ft_strdup(val);
	if (!newval)
		return (free(newvar), -1);
	new = ft_strjoin(newvar, newval);
	free(newvar);
	free(newval);
	if (!new)
		return (-1);
	free (env[posi]);
	env[posi] = new;
	return (1);
}

static int	ft_create_var(char ***env, char *var, unsigned int i)
{
	unsigned int	size;
	char			**newenv;

	size = size_env(*env);
	size++;
	newenv = malloc(sizeof(char *) * (size + 1));
	if (!newenv)
		return (-1);
	while (i < size - 2)
	{
		newenv[i] = (*env)[i];
		i++;
	}
	newenv[size - 2] = ft_strdup(var);
	if (!(newenv[size - 2]))
	{
		free(newenv);
		return (1);
	}
	newenv[size - 1] = (*env)[size - 2];
	newenv[size] = NULL;
	free(*env);
	*env = newenv;
	return (0);
}

int	ft_export_one_by_one(char ***env, char *str)
{
	unsigned int	i;
	int				posi;
	char			*var;

	i = 0;
	if (ft_parse_var(str, &i) == -1)
		return (0);
	var = ft_strndup(str, i);
	if (!var)
		return (1);
	posi = find_var(*env, var);
	if (posi == -1)
	{
		if (ft_create_var(env, var, 0) == -1)
			return (free(var), 1);
		posi = find_var(*env, var);
	}
	if (ft_change_val(*env, posi, &(str[i]), i) == -1)
		return (free(var), 1);
	free(var);
	return (0);
}

int	ft_export(char ***env, char **tab)
{
	unsigned int	i;

	i = 0;
	if (!tab || !(tab[0]) || tab[0][0] == '\0')
		return (ft_ordonned_env(*env, NULL, -1, NULL));
	while (tab[i])
	{
		ft_export_one_by_one(env, tab[i]);
		i++;
	}
	return (0);
}
