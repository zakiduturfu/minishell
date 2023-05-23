/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:11:46 by zlemery           #+#    #+#             */
/*   Updated: 2022/11/20 18:51:21 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (str2[i] == '\0')
		return ((char *)str1);
	while (str1[i] != '\0' && (i + j) < n)
	{
		while (str1[i + j] == str2[j])
		{
			if (str2[j + 1] == '\0')
				return ((char *)str1 + i);
			j++;
		}
		i++;
	}
	return (0);
}
