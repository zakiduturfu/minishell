/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/20 21:37:49 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_parse_var(char *str, unsigned int *i)
{
	if (!str || str[0] == '\0')
		return (0);
	if (str[0] == '=')
	{
		printf("export: '%s': not a valid identifier\n", str);
		return (1);
	}
	while (str[*i] != '\0' && str[*i] != '=')
	{
		if (str[*i] == '-')
		{
			printf("export: '%s': not a valid identifier\n", str);
			return (1);
		}
		*i = *i + 1;
	}
	if (str[*i] == '\0')
		return (1);
	*i = *i + 1;
	return (0);
}

static int	ft_change_val(char **env,
		unsigned int posi, char *val, unsigned int i)
{
	char	*newvar;
	char	*newval;
	char	*new;

	newvar = ft_strndup(env[posi], i);
	if (!newvar)
		return (1);
	if (!val || val[0] == '\0' || val[0] == ' ' || val[0] == '\t')
		newval = ft_strdup("\0");
	else
		newval = ft_strdup(val);
	if (!newval)
		return (free(newvar), 1);
	new = ft_strjoin(newvar, newval);
	free(newvar);
	free(newval);
	if (!new)
		return (1);
	free (env[posi]);
	env[posi] = new;
	return (0);
}

static int	ft_create_var(char ***env, char *var, unsigned int i)
{
	unsigned int	size;
	char			**newenv;

	size = size_env(*env);
	size++;
	newenv = malloc(sizeof(char *) * (size + 1));
	if (!newenv)
		return (1);
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
	if (ft_parse_var(str, &i) != 0)
		return (1);
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

int	ft_export(char ***env, char **tab, t_shell *shell)
{
	unsigned int	i;
	int				tmpstat;
	bool			alwaysgood;

	alwaysgood = 1;
	tmpstat = shell->status;
	i = 0;
	if (!tab || !(tab[0]) || tab[0][0] == '\0')
	{
		shell->status = ft_ordonned_env(*env, NULL, -1, NULL);
		return (shell->status);
	}
	while (tab[i])
	{
		tmpstat = ft_export_one_by_one(env, tab[i]);
		if (tmpstat != 0)
		{
			shell->status = tmpstat;
			alwaysgood = 0;
		}
		i++;
	}
	if (alwaysgood == 1)
		shell->status = 0;
	return (0);
}
