/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/08/28 17:36:00 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	find_var(t_shell *shell, char *var)
{
	unsigned int	size;
	unsigned int	i;

	i = 0;
	size = size_env(shell->env);
	while (i < size)
	{
		if (ft_strncmp(shell->env[i], var, ft_strlen(var)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_parse(char *str, unsigned int *i)
{
	if (!str || str[0] == '\0')
	{
		printf("pas de suite a cmd export, todo\n");
		return (-1);
	}
	if (open_quote(str) == 1)
		return (dquote());
	while (str[*i] != '\0' && str[*i] != '=')
	{
		if (str[*i] == ' ' || str[*i] == '\t')
		{
			printf("zsh: bad assignment\n");
			return (-1);
		}
		if (str[*i] == '-')
		{
			printf("export: not valid in this context: ");
			// ft_putnstr(str, *i);
			return (-1);
		}
		*i = *i + 1;
	}
	printf("apres boucle parcours str \n");
	if (str[*i] == '\0')
		return (-1);
	*i = *i + 1;
	return (0);
}

static int	ft_change_val(t_shell *shell, unsigned int posi, char *val, unsigned int i)
{
	char			*new;
	
	if (!val || val[0] == '\0' || val[0] == ' ' || val[0] == '\t')
		return (0);
	new = ft_strndup(shell->env[posi], i);
	if (!new)
		return (-1);
	
	return (0);
}

static int	ft_create_var(t_shell *shell, char *var)
{
	unsigned int	size;
	char			**newenv;
	unsigned int	i;
	
	i = 0;
	size = size_env(shell->env);
	size++;
	newenv = malloc(sizeof(char *) * (size + 1));
	if (!newenv)
		return (-1);
	newenv[size] = NULL;
	while (i < size - 2)
	{
		newenv[i] = shell->env[i];
		i++;
	}
	newenv[size - 1] = shell->env[size - 2];
	newenv[size - 2] = var;
	free(shell->env);
	shell->env = newenv;
	return (0);
}

int	ft_export(t_shell *shell, char *str)
{
	unsigned int	i;
	int				posi;
	char			*var;

	i = 0;
	if (ft_parse(str, &i) == -1)
		return (0);
	printf("i = %d et str[i] = %c \n", i, str[i]);
	var = ft_strndup(str, i);
	if (!var)
		return (1);
	posi = find_var(shell, var);
	if (posi == -1)
	{
		if (ft_create_var(shell, var) == -1)
			return (1);
		posi = size_env(shell->env) - 1;
	}
	if (ft_change_val(shell, posi, &(str[i]), i) == -1)
		return (1);
	i = 0;
	while (shell->env[i])
	{
		printf("%s \n",shell->env[i]);
		i++;
	}
	return (0);
}