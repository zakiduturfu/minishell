/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:15:54 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/02 16:34:18 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	open_quote(char *str)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '"')
			quotes++;
		i++;
	}
	return (quotes);
}

void	print(char *str, int newline, int i, int quote)
{
	int		n_quotes;

	n_quotes = open_quote(str);
	while (str && (str[i] == 32 || str[i] == '\t'))
		i++;
	while (str && str[i] != '\0')
	{
		if (str[i] == '"')
		{
			quote++;
			if (quote == n_quotes && n_quotes % 2 == 1)
				printf("%c", str[i]);
			i++;
		}
		if ((quote != n_quotes && quote % 2 == 1)
			|| (str[i] != 32 && str[i] != '\t'))
			printf("%c", str[i]);
		else if ((str[i] == 32 || str[i] == '\t')
			&& str[i + 1] != 32 && str[i + 1] != '\t' && str[i + 1] != '\0')
			printf(" ");
		i++;
	}
	if (newline == 1)
		printf("\n");
}

static int	n_param(char *str, int *i, bool n, int last)
{
	if (!str)
		return (0);
	while (str[*i] != '\0')
	{
		if (str[*i] != '-')
			return (n);
		else
		{
			*i = *i + 1;
			while (str[*i] == 'n')
				*i = *i + 1;
			if (str[*i] != 32 && str[*i] != '\t' && str[*i] != '\0')
			{
				*i = last;
				return (n);
			}
			else
				n = 1;
		}
		while (str[*i] == 32 || str[*i] == '\t')
			*i = *i + 1;
		last = *i;
	}
	return (n);
}

// int	dquote(void) / not in the mandatory new subjet
// {
// 	char	*line;

// 	line = NULL;
// 	line = readline("dquote>");
// 	while (line)
// 	{
// 		free(line);
// 		line = readline("dquote>");
// 	}		
// 	return (0);
// }

int	ft_echo(char **tab)
{
	int	i;

	i = 0;
	if (tab && tab[1])
	{
		if (n_param(tab[1], &i, 0, 0) == 1)
			print(&(tab[1][i]), 0, 0, 0);
		else
			print(&(tab[1][i]), 1, 0, 0);
	}
	else
		printf("\n");
	return (0);
}
