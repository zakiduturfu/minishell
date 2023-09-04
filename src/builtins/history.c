/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:35:59 by hstephan          #+#    #+#             */
/*   Updated: 2023/08/28 17:36:00 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	find_cmd(t_lines *lines, char *cmd)
{
	t_lines	*tmp;

	tmp = lines;
	if (!tmp)
		return (-1);
	while (tmp->next != NULL)
		tmp = tmp->next;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->line, cmd) == 0)
			return (tmp->index);
		tmp = tmp->prev;
	}
	return (-1);
}

static void	ft_all_history(t_lines *lines, unsigned int i)
{
	t_lines			*tmp;

	tmp = lines;
	if (!tmp)
		return ;
	while (tmp->next != NULL)
	{
		i = tmp->index;
		tmp = tmp->next;
	}
	if (tmp->index == 1)
	{
		printf("   %d  ", tmp->index);
		printf("%s\n", tmp->line);
		return ;
	}
	tmp = tmp->prev;
	while (tmp->index > 1 && (i <= 16 || i - tmp->index < 15))
		tmp = tmp->prev;
	while (tmp->next != NULL)
	{
		printf("   %d  ", tmp->index);
		printf("%s\n", tmp->line);
		tmp = tmp->next;
	}
}

static void	ft_print_history_part(t_lines *lines,
	unsigned int start, unsigned int end)
{
	t_lines			*tmp;

	tmp = lines;
	while (tmp != NULL && tmp->index != start)
		tmp = tmp->next;
	if (end >= start || end == 0)
	{
		while (tmp->next != NULL && (tmp->index <= end || end == 0))
		{
			printf("   %d  ", tmp->index);
			printf("%s\n", tmp->line);
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp && tmp->index >= end)
		{
			printf("   %d  ", tmp->index);
			printf("%s\n", tmp->line);
			tmp = tmp->prev;
		}
	}
}

static void	ft_history_part(t_lines *lines, char **tab)
{
	int				start;
	int				end;

	end = 0;
	start = find_cmd(lines, tab[0]);
	if (start == -1)
	{
		printf("fc: event not found: %s\n", tab[0]);
		return ;
	}
	if (tab[1] != NULL)
	{
		end = find_cmd(lines, tab[1]);
		if (end == -1)
		{
			printf("fc: event not found: %s\n", tab[1]);
			return ;
		}
		if (tab[2] != NULL)
		{
			printf("fc: too many arguments\n");
			return (0);
		}
	}
	ft_print_history_part(lines, start, end);
}

int	ft_history(t_shell *shell, char *str)
{
	t_lines			*tmp;
	char			**tab;
	unsigned int	i;

	tmp = shell->lines;
	if (!tmp)
		return (0);
	if (!str || str[0] == '\0')
	{
		ft_all_history(shell->lines, 0);
		return (0);
	}
	tab = ft_nsplit(str, ' ', '\t');
	if (!tab)
		return (1);
	ft_history_part(shell->lines, tab);
	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}
