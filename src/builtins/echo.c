/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:15:54 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/02 15:22:45 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print(char *str, int newline)
{
	int		i;
	bool	open_quote;

	i = 0;
	open_quote = 0;
	while (str && (str[i] == 32 || str[i] == '\t'))
		i++;
	while (str && str[i] != '\0')
	{
		if (str[i] == '"' && open_quote == 0)
			open_quote = 1;
		else if (str[i] == '"' && open_quote == 1)
			open_quote = 0;
		else if (open_quote == 1 || (str[i] != 32 && str[i] != '\t'))
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

// int	open_quote(char *str) / not in the mandatory new subjet
// {
// 	int	i;
// 	int	quotes;

// 	i = 0;
// 	quotes = 0;
// 	if (!str)
// 		return (0);
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '"')
// 			quotes++;
// 		i++;
// 	}
// 	if (quotes % 2 != 0)
// 		return (1);
// 	return (0);
// }

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
			print(&(tab[1][i]), 0);
		else
			print(&(tab[1][i]), 1);
	}
	else
		printf("\n");
	return (0);
}
