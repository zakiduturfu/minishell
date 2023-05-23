/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:06:22 by zlemery           #+#    #+#             */
/*   Updated: 2022/11/20 12:36:29 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char const *nb)
{
	int	i;
	int	sign;
	int	ret;

	i = 0;
	ret = 0;
	sign = 1;
	while (nb[i] == ' ' || (nb[i] >= 9 && nb[i] <= 13))
		i++;
	if (nb[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (nb[i] == '+')
		i++;
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		ret = ret * 10 + (nb[i] - '0');
		i++;
	}
	return (ret * sign);
}
