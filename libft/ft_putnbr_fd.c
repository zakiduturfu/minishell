/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:13:16 by zlemery           #+#    #+#             */
/*   Updated: 2022/11/22 16:11:39 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int nbr, int fd)
{
	if (nbr == 2147483647)
	{
		write(fd, "2147483647", 10);
		return ;
	}
	if (nbr == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (nbr >= 0 && nbr < 10)
		ft_putchar_fd((nbr + 48), fd);
	else if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd((-nbr), fd);
	}
	else
	{
		ft_putnbr_fd((nbr / 10), fd);
		ft_putchar_fd(((nbr % 10) + '0'), fd);
	}
}
