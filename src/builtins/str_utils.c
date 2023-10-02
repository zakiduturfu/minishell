/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:39:30 by hstephan          #+#    #+#             */
/*   Updated: 2023/10/02 16:47:46 by hstephan         ###   ########.fr       */
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

int	is_single_quote(char c)
{
	if (c == 39)
		return (1);
	return (0);
}

int	is_double_quote(char c)
{
	if (c == 34)
		return (1);
	return (0);
}