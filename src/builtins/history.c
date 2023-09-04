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
	int		i;
	
	i = 0;
	tmp = lines;
	if (!tmp)
		return (-1);
	while (tmp->next != NULL)
	{
		if (ft_strcmp(tmp->line, cmd) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_all_history(t_lines *lines)
{
	t_lines			*tmp;
	unsigned int	i;

	tmp = lines;
	if (!tmp)
		return (0);
	while (tmp->next != NULL)
	{
		i = tmp->index;
		tmp = tmp->next;
	}
	if (tmp->index == 1)
	{
		printf("   %d  ", tmp->index);
		printf("%s\n", tmp->line);
		return (0);
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
	return (0);
}

static int	ft_print_history_part(t_lines *lines, unsigned int start, unsigned int end)
{
	t_lines			*tmp;

	tmp = lines;
	while (tmp != NULL && tmp->index != start)
		tmp = tmp->next;
	if (end > start || end == 0)
	{
		while (tmp->next != NULL || (tmp->index <= end && end != 0))
		{
			printf("   %d  ", tmp->index);
			printf("%s\n", tmp->line);
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp->prev != NULL || (tmp->index >= end))
		{
			printf("   %d  ", tmp->index);
			printf("%s\n", tmp->line);
			tmp = tmp->prev;
		}
	}
	return (0);
}

static int	ft_history_part(t_lines *lines, char **tab)
{
	int				start;
	int				end;

	end = 0;
	start = find_cmd(lines, tab[0]);
	if (start == -1)
	{
		printf("fc: event not found: %s\n", tab[0]);
		return (0);
	}
	if (tab[1] != NULL)
	{
		end = find_cmd(lines, tab[1]);
		if (end == -1)
		{
			printf("fc: event not found: %s\n", tab[0]);
			return (0);
		}
		if (tab[2] != NULL)
			print_and_return("fc: too many arguments\n", 0);
	}
	ft_print_history_part(lines, start, end);
	return (0);
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
		return (ft_all_history(shell->lines));
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