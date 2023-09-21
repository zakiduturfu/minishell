/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:58:15 by zlemery           #+#    #+#             */
/*   Updated: 2022/11/17 14:21:16 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnstr_fd(char *s, int fd, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0' && i < n)
	{
		write(fd, &s[i], 1);
		i++;
	}
}
