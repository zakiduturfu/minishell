/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:37:35 by zlemery           #+#    #+#             */
/*   Updated: 2022/11/20 18:32:13 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	m;

	i = ft_strlen(s);
	m = (unsigned char)c;
	if (!s)
		return (0);
	while (i > 0 && s[i] != m)
		i--;
	if (s[i] == m)
		return ((char *)s + i);
	return (0);
}
