/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:58:01 by zlemery           #+#    #+#             */
/*   Updated: 2022/11/20 13:50:13 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(char *str)
{
	int		i;
	char	*nstr;

	i = 0;
	nstr = malloc(sizeof(*nstr) * ft_strlen(str) + 1);
	if (!nstr)
		return (NULL);
	while (str[i] != '\0')
	{
		nstr[i] = str[i];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}
