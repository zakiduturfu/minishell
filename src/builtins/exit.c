/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:22:34 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/20 22:14:24 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_str_isdigit(char *s)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
		i++;
	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	while (s[i])
	{
		if (!is_space(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	exit_mini(char **tab, char **env, t_shell *shell, int n)
{
	free_all(tab);
	free_all(shell->token);
	free(shell->av);
	free_env_tab(env);
	if (shell->nb_here)
		free(shell->here);
	if (shell->nb_cmd == 1)
	{
		dup_and_close(shell->builtin, STDIN_FILENO);
		dup_and_close(shell->builtout, STDOUT_FILENO);
	}
	clear_history();
	exit(n);
}

void	ft_exit(char **tab, t_shell *shell, char **env)
{
	if (shell->nb_cmd == 1)
		printf("exit\n");
	if (!tab[1])
		exit_mini(tab, env, shell, shell->status);
	else if (tab[1] && ft_str_isdigit(tab[1]) && !tab[2])
		exit_mini(tab, env, shell, ft_atoi(tab[1]));
	else if (tab[1] && !ft_str_isdigit(tab[1]))
	{
		ft_putstr_fd(tab[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(tab[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("numeric argument required\n", 2);
		exit_mini(tab, env, shell, 2);
	}
	else
	{
		ft_putstr_fd(tab[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("too many arguments\n", 2);
		shell->status = 1;
	}
	return ;
}
