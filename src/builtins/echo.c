/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:15:54 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/09 11:16:32 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	dollar_gestion(char *str, int *i, char **env)
{
	int	posi;
	unsigned int j;

	j = 0;
	posi = -1;
	*i = *i + 1;
	if (is_dollar(str[*i]))
		printf("4202"); // verif pourquoi c'est ca qui se printe et si ca peut varier du coup...
	else if (is_end(str[*i]) || is_space(str[*i]))
		printf("$");
	else 
	{
		posi = find_var(env, &(str[*i]));
		if (posi != -1)
		{
			while (!(is_end(str[*i + j]) && !(is_space(str[*i + j]))))
				j++;
			printf("%s", &(env[posi][j]));
		}
	}	
}

static void	print(char *str, int newline, int i, char **env)
{
	t_quotes	quotes;

	quotes = quotes_count(str);
	while (is_space(str[i]))
		i++;
	while (str && !(is_end(str[i])))
	{
		if (is_single_quote(str[i]) && quotes.double_open == 0)
			quotes_gestion(quotes.this_s++, quotes.singles, &quotes.single_open);
		else if (is_double_quote(str[i]) && quotes.single_open == 0)
			quotes_gestion(quotes.this_d++, quotes.doubles, &quotes.double_open);
		else if (is_dollar(str[i] == 1))
			dollar_gestion(str, &i, env);
		else if (open_quotes(quotes) == 1 || is_space(str[i]) == 0)
			printf("%c", str[i]);
		else if (is_space(str[i]) && !(is_space(str[i + 1])) && !(is_end(str[i + 1])))
			printf(" ");
		i++;
	}
	if (newline == 1)
		printf("\n");
}

static int	n_param(char *str, int *i, bool n, int last)
{
	last = *i;
	if (!str)
		return (n);
	while (!(is_end(str[*i])))
	{
		while (is_space(str[*i]))
			*i =  *i + 1;
		if (str[*i] != '-')
			return (n);
		*i = *i + 1;
		while (str[*i] == 'n')
			*i = *i + 1;
		if (str[*i - 1] != 'n' || (is_space(str[*i]) == 0 && is_end(str[*i] == 0)))
		{
			*i = last;
			return (n);
		}
		else
			n = 1;
		last = *i;
	}
	return (n);
}

int	ft_echo(char *str, char **env)
{
	int	i;

	i = 0;
	if (str)
	{
		if (n_param(str, &i, 0, 0) == 1)
			print(&(str[i]), 0, 0, env);
		else
			print(&(str[i]), 1, 0, env);
	}
	else
		printf("\n");
	return (0);
}
