/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:37:43 by zlemery           #+#    #+#             */
/*   Updated: 2022/11/20 17:54:23 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	m;

	i = 0;
	m = (unsigned char)c;
	if (!s)
		return (0);
	while (s[i] != '\0' && s[i] != m)
		i++;
	if (s[i] == m)
		return ((char *)s + i);
	return (0);
}
