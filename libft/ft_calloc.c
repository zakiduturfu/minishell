/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:37:10 by zlemery           #+#    #+#             */
/*   Updated: 2022/11/26 13:27:50 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stddef.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*tab;
	size_t	len;

	if (!nmemb || !size)
		return (malloc(0));
	len = nmemb * size;
	if (len / size != nmemb)
		return (NULL);
	tab = malloc(nmemb * size);
	if (!tab)
		return (NULL);
	ft_memset(tab, '\0', (nmemb * size));
	return (tab);
}
