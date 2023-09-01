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

static int	ft_change_val(t_shell *shell, char *var, char *val)
{
	unsigned int	size;
	unsigned int	i;
	unsigned int	j;
	
	i = 0;
	j = 0;
	if (!val || val[0] == '\0' || val[0] == ' ' || val[0] == '\t')
		return (0);
	size = size_env(shell->env);
	while (i < size)
	{
		if (ft_strncmp(shell->env[i], var, ft_strlen(var) == 0))
		{
			printf("sur var existante\n");
			// while (val[0] >= 33)
			// {
			// 	if (val[j] == '"')
			// 	{
			//  }
			// 		else

			// 
			// }
			// return (0);
		}
		i++;
	}
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
	char			*var;

	i = 0;
	if (ft_parse(str, &i) == -1)
		return (0);
	var = malloc(sizeof(char) * i);
	if (!var)
		return (1);
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		var[i] = str[i];
		i++;
	}
	var[i] = '=';
	var[++i] = '\0';
	if (!getenv(var))
		if (ft_create_var(shell, var) == -1)
			return (1);
	if (ft_change_val(shell, var, &(str[i])) == -1)
		return (1);
	i = 0;
	while (shell->env[i])
	{
		printf("%s \n",shell->env[i]);
		i++;
	}
	return (0);
}