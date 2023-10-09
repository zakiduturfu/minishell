/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:39:30 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/09 11:27:07 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_single_quote(char c)
{
	if (c == 39)
		return (1);
	return (0);
}

int	is_double_quote(char c)
{
	if (c == 34)
		return (1);
	return (0);
}

int	open_quotes(t_quotes quotes)
{
	if (quotes.single_open == 1 || quotes.double_open == 1)
		return (1);
	return (0);
}

void	quotes_gestion(int n, int max, bool *boolopen)
{
	if (*boolopen == 0 && n != max)
		*boolopen = 1;
	else if (*boolopen == 1)
		*boolopen = 0;
	// if (n == max && max % 2 == 1) si on veut afficher les quotes ouvertes solitaires
	// 	printf("%c"); 
}

t_quotes	quotes_count(char *str)
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
