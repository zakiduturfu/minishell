/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/09/25 18:12:12 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_cd(char **env, char *str)
{
	int		posi;
	char	*new;

	posi = -1;
	if (str && open_quote(str) == 1)
		return (dquote());
	if (!str || str[0] == '\0')
	{
		posi = find_var(env, "HOME");
		if (posi == -1)
			return (-1);
		new = ft_strjoin("PWD", &(env[posi][4]));
		if (!new)
			return (-1);
		ft_export_one_by_one(env, new);
		free(new);
		return (0);
	}
	printf("pwd: too many arguments\n");
	return (0);
}
