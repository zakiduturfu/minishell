/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:58:28 by hstephan          #+#    #+#             */
/*   Updated: 2022/05/11 15:58:53 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	char	*dst;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	dst = (char *)malloc(sizeof(char) * (n + 1));
	if (dst == NULL)
		return (NULL);
	while (*src != '\0' && n != 0)
	{
		*(dst + i) = *src;
		i++;
		src++;
		n--;
	}
	*(dst + i) = '\0';
	return (dst);
}
