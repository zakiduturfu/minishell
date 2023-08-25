/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:41:51 by zlemery           #+#    #+#             */
/*   Updated: 2023/08/25 15:20:39 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count(char const *s, char c)
{
	int	i;
	int	len;
	int	word;

	i = 0;
	word = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			word = 0;
		else
		{
			if (!word)
				len++;
			word = 1;
		}
		i++;
	}
	return (len);
}

void	free_all(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static void	write_word(char **tab, char const *s, char c)
{
	char const	*tmp;

	tmp = s;
	while (*tmp)
	{
		while (*s == c)
			s++;
		tmp = s;
		while (*tmp && *tmp != c)
			tmp++;
		if (*tmp == c || tmp > s)
		{
			*tab = ft_substr(s, 0, tmp - s);
			if (!tab)
				free_all(tab);
			tab++;
			s = tmp;
		}
	}
}

char	**ft_split(char *s, char c)
{
	char	**tab;
	size_t	len;

	len = count(s, c);
	if (!s)
		return (0);
	tab = ft_calloc((1 + len), sizeof(char *));
	if (!tab)
		return (NULL);
	write_word(tab, s, c);
	return (tab);
}
