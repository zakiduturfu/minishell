/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:13:42 by zlemery           #+#    #+#             */
/*   Updated: 2022/11/23 16:47:40 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest || !src)
		return (dest);
	while (i < n)
	{
		((unsigned char *) dest)[i] = ((unsigned char *) src)[i];
		i++;
	}
	return ((char *)dest);
}
