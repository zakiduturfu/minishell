/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:59:34 by zlemery           #+#    #+#             */
/*   Updated: 2022/11/21 15:01:07 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	countstrs(char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[j] != '\0')
		j++;
	return (i + j);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	i = 0;
	j = 0;
	tab = malloc(sizeof(char) * (countstrs(s1, s2) + 1));
	if (!tab)
		return (NULL);
	while (s1[i] != '\0')
	{
		tab[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		tab[i] = s2[j];
		j++;
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
