/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:24:44 by zlemery           #+#    #+#             */
/*   Updated: 2022/11/21 14:25:58 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tab;
	size_t	i;
	size_t	slen;

	i = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > (ft_strlen(s) - start))
		slen = (ft_strlen(s) - start);
	else
		slen = len;
	tab = malloc(sizeof(char) * (slen + 1));
	if (!tab)
		return (NULL);
	while (i < slen && start < ft_strlen(s))
	{
		tab[i] = s[start];
		i++;
		start++;
	}
	tab[i] = '\0';
	return (tab);
}
