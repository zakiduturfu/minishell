/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:15:54 by hstephan          #+#    #+#             */
/*   Updated: 2023/08/29 11:15:55 by hstephan         ###   ########.fr       */
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

static int	n_param(char *str, int *i)
{
	if (!str)
		return (0);
	if (str[0] == '-')
	{
		*i = *i + 1;
		while (str[*i] == 'n')
			*i = *i + 1;
		if (str[*i] != 32 && str[*i] != '\0')
		{
			*i = 0;
			return (0);
		}
		else
			return (1);
	}
	return (0);
}

int	open_quote(char *str)
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
	if (quotes % 2 != 0)
		return (1);
	return (0);
}

int	dquote(void)
{
	char	*line;

	line = NULL;
	line = readline("dquote>");
	while (line)
	{
		free(line);
		line = readline("dquote>");
	}		
	return (0);
}

int	ft_echo(char **tab)
{
	int	i;

	i = 0;
	if (tab[1])
	{
		if (open_quote(tab[1]) == 1)
			return (dquote());
		else
		{
			if (n_param(tab[1], &i) == 1)
				print(&(tab[1][i]), 0);
			else
				print(&(tab[1][i]), 1);
		}
	}
	else
		printf("\n");
	free(tab[0]);
	free(tab);
	return (0);
}
