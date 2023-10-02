/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:15:54 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/02 17:36:00 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void quotes_gestion(int n, int max, bool *boolopen)
{
	if (*boolopen == 0 && n != max)
		*boolopen = 1;
	else if (*boolopen == 1)
		*boolopen = 0;
	// if (n == max && max % 2 == 1) si on veut afficher les quotes ouvertes solitaires
	// 	printf("%c"); 
}
static t_quotes	quotes_count(char *str)
{
	int			i;
	t_quotes	quotes;

	i = 0;
	quotes.doubles = 0;
	quotes.singles = 0;
	quotes.single_open = 0;
	quotes.double_open = 0;
	quotes.this_s = 0;
	quotes.this_d = 0;
	while (str && !(is_end(str[i])))
	{
		if (is_double_quote(str[i]))
			quotes.doubles++;
		else if (is_single_quote(str[i]))
			quotes.singles++;
		i++;
	}
	return (quotes);
}

void	print(char *str, int newline, int i)
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
		else if (quotes.double_open == 1 || quotes.single_open == 1 || is_space(str[i]) == 0)
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
		if (str[*i] != '-')
			return (n);
		else
		{
			*i = *i + 1;
			while (str[*i] == 'n')
				*i = *i + 1;
			if (!(is_space(str[*i]) && !(is_end(str[*i]))))
			{
				*i = last;
				return (n);
			}
			else
				n = 1;
		}
		while (is_space(str[*i]))
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

int	ft_echo(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		if (n_param(str, &i, 0, 0) == 1)
			print(&(str[i]), 0, 0);
		else
			print(&(str[i]), 1, 0);
	}
	else
		printf("\n");
	return (0);
}
