/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:52:16 by zlemery           #+#    #+#             */
/*   Updated: 2022/11/26 13:03:08 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	countlen(int n)
{
	int	count;

	count = 0;
	if (n < 0)
		count = 1;
	if (n == 0)
	{
		count++;
		return (count);
	}
	while (n)
	{
		n /= 10;
		count ++;
	}
	return (count);
}

static char	*string_min(char *array)
{
	array[0] = '-';
	array[1] = '2';
	array[2] = '1';
	array[3] = '4';
	array[4] = '7';
	array[5] = '4';
	array[6] = '8';
	array[7] = '3';
	array[8] = '6';
	array[9] = '4';
	array[10] = '8';
	array[11] = '\0';
	return (array);
}

static char	*write_nb(char *array, int n, int len)
{
	array[len] = '\0';
	len--;
	while (n != 0)
	{
	array[len] = n % 10 + '0';
	n /= 10;
	len--;
	}
	if (len == 0 && array[1] == 0)
		array[len] = '0';
	else if (len == 0 && array[1] != 0)
		array[len] = '-';
	return (array);
}

char	*ft_itoa(int n)
{
	char	*array;
	int		len;

	len = countlen(n);
	if (n < 0)
		n *= -1;
	array = malloc(sizeof(char) * (len + 1));
	if (!array)
		return (NULL);
	if (n != -2147483648)
		write_nb(array, n, len);
	else
		array = string_min(array);
	return (array);
}
