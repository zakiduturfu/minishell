/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:57:08 by zlemery           #+#    #+#             */
/*   Updated: 2023/07/21 03:15:25 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include "../libft/libft.h"

typedef	struct s_shell
{
	char	**token;
	int		here;
	int		fdin;
	int		fdout
	char	*type;
	int		nb_cmd;
}	t_shell;

char	*line_arg(char *line);
void	pars_line(char *line);
int		ignore_sep(char *line, int i);
int		is_quote(char *line, int i);
int		is_sep(char *line, int i);
int		is_token(char *line, int *i, char c);
int		token_alloc(char *line, int *i, char c);
char	**split_token(char *line, char c);
int		count_cmd(char **tab);
int		t_ignore_sep(char *line, int i, char c);
int		size_token(char *line, char c);
int		split_built(char *cmd);
int		init_struct(t_shell *shell, char *line);
int		is_builtin(char **cmd);
int		find_redir(char **redir);
int		ft_strcmp(const char *str1, const char *str2);
void	v2_pars_line(char *line);
int		exec_pipex(t_shell *shell)
#endif