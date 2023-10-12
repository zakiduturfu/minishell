/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:39:30 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/09 11:30:16 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_space(char c)
{
	if (c == 32 || c == '\t')
		return (1);
	return (0);
}

int	is_end(char c)
{
	if (c == '\0')
		return (1);
	return (0);
}

int	is_dollar(char c)
{
	if (c == 36)
		return (1);
	return (0);
}
