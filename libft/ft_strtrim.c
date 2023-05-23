/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:21:53 by zlemery           #+#    #+#             */
/*   Updated: 2022/11/21 15:17:03 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static unsigned int	checkstart(char const *s1, char const *set)
{
	unsigned int	start;
	int				i;
	int				j;

	j = 0;
	i = 0;
	start = 0;
	while (set[i] != '\0')
	{
		if (set[i] == s1[j])
		{
			start++;
			j++;
			i = 0;
		}
		else
			i++;
	}
	return (start);
}

static size_t	checksize(char const *s1, char const *set)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (s1[len] != '\0')
		len++;
	while (set[i] != '\0')
	{
		if (set[i] == s1[len - 1])
		{
			len--;
			i = 0;
		}
		else
			i++;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*tab;
	unsigned int	start;
	size_t			size;

	if (!s1 || !set)
	{
		return (0);
	}
	start = checkstart(s1, set);
	size = checksize(s1, set);
	tab = ft_substr(s1, start, (size - start));
	return (tab);
}
