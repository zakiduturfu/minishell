/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:57:08 by zlemery           #+#    #+#             */
/*   Updated: 2023/07/04 22:36:31 by zlemery          ###   ########.fr       */
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
	char	**token;
	char	*type;
}	t_shell;

char	*line_arg(char *line);
void	pars_line(char *line);
int		ignore_sep(char *line, int i);
int		is_quote(char *line, int i);
int		is_sep(char *line, int i);
int		token_alloc(char *line, int *i);
void	get_token(char *line, char **token);
void	v2_pars_line(char *line);
#endif