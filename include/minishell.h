/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:57:08 by zlemery           #+#    #+#             */
/*   Updated: 2023/06/24 16:06:53 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "../libft/libft.h"

typedef struct s_token
{
	char	*word;
}	t_token;

typedef	struct s_shell
{
	t_token	**token;
}	t_shell;

char	*line_arg(char *line);
void	pars_line(char *line);
int		ignore_sep(char *line, int i);
int		is_quote(char *line, int i);
int		is_sep(char *line, int i);

int		token_alloc(char *line, int *i);
t_token	**get_token(char *line);
void	v2_pars_line(char *line);
#endif