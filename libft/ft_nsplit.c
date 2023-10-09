/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:41:51 by zlemery           #+#    #+#             */
/*   Updated: 2023/08/25 15:20:39 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count(char const *s, char c, char d)
{
	int	i;
	int	len;
	int	word;

	i = 0;
	word = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c || s[i] == d)
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

static void	write_word(char **tab, char const *s, char c, char d)
{
	char const	*tmp;

	tmp = s;
	while (*tmp)
	{
		while (*s == c || *s == d)
			s++;
		tmp = s;
		while (*tmp && *tmp != c && *tmp != d)
			tmp++;
		if (*tmp == c || *tmp == d || tmp > s)
		{
			*tab = ft_substr(s, 0, tmp - s);
			if (!tab)
				free_all(tab);
			tab++;
			s = tmp;
		}
	}
}

char	**ft_nsplit(char *s, char c, char d)
{
	char	**tab;
	size_t	len;

	len = count(s, c, d);
	if (!s)
		return (0);
	tab = ft_calloc((1 + len), sizeof(char *));
	if (!tab)
		return (NULL);
	write_word(tab, s, c, d);
	return (tab);
}
