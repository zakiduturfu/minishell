/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/02 11:28:48 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_parse_var(char *str, unsigned int *i)
{
	if (!str || str[0] == '\0')
		return (0);
	if (open_quote(str) == 1)
		return (dquote());
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
	i = 0;
	while (val[i] >= 33 && val[i] <= 126)
		i++;
	newval = ft_strndup(val, i);
	if (!newval)
	{
		free(newvar);
		return (-1);
	}
	new = ft_strjoin(newvar, newval);
	// printf("apres join new = %s\n", new);
	free(newvar);
	free(newval);
	if (!new)
		return (-1);
	free (env[posi]);
	env[posi] = new;
	return (0);
}

static int	ft_create_var(char ***env, char *var)
{
	unsigned int	size;
	char			**newenv;
	unsigned int	i;

	i = 0;
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
	// printf("avant de changer (*env)[size - 2] = %s\n)", (*env)[size - 2]);
	// printf("avant de changer (*env)[size - 1] = %s\n)", (*env)[size - 1]);
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
		// printf("avant create var, env = \n");
		// ft_env(env);
		if (ft_create_var(env, var) == -1)
			return (1);
		// printf("apres create var, env = \n");
		// ft_env(*env);
		posi = find_var(*env, var);
	}
	if (ft_change_val(*env, posi, &(str[i]), i) == -1)
		return (1);
	// printf("apres change val, env = \n");
	// ft_env(*env);
	return (0);
}

int		ft_export(char ***env, char *str)
{
	char			**tab;
	unsigned int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return(ft_ordonned_env(*env));
	tab = ft_nsplit(str, ' ', '\t');
	if (!tab)
		return (1);
	while (tab[i])
	{
		ft_export_one_by_one(env, tab[i]);
		i++;
	}
	ft_free_tab(tab);
	return (0);
}
