/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:57:08 by zlemery           #+#    #+#             */
/*   Updated: 2023/08/21 18:35:22 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <sys/types.h>
#include <fcntl.h>
#include "../libft/libft.h"

typedef	struct s_shell
{
	char	**token;
	char	**env;
	int		pipefd[2];
	int		prev_pipe;
	int		nb_here;
	int		fdin;
	int		fdout;
	pid_t	*pid;
	char	*path;
	char	*type;
	int		nb_cmd;
	int		index;
}	t_shell;

/* /src/env/env.c */
char	**recup_env(char **env);
char	*recup_env_ligne(char *str);
char	*find_var_name(char *env);
char	*dup_var_name(char *str, int index);

/* /src/env/expansions.c */
char	*ft_expansions(char *str);
char	*get_before_expand(char *str, int i);
char	*get_after_expand(char *str);
char	*get_expand_val(char *str, int i);
char	*ft_avengers(char *before, char *after, char *expand);

/* /src/env/shlvl.c */
void	increment_shlvl(char **env);
char	*recup_val_shlvl(char **env);
char	*modify_var_env(char *name, char **env, char *var);

/* /src/tools/env/env_utils */
int		size_env(char **env);
void	free_env_tab(char **env);
int		tab_value(char **tab, char *str, int i);

/* /src/tools/env/expansions_utils.c */
int	free_expand(char **tab, int index);
int	search_expand(char *str);


char	*line_arg(char *line);
int		pars_line(char *line, char **env);
int		ignore_sep(char *line, int i);
int		is_quote(char *line, int i);
int		is_sep(char *line, int i);
int		is_token(char *line, int *i, char c);
int		token_alloc(char *line, int *i, char c);
char	**split_token(char *line, char c);
int		count_cmd(char **tab);
int		t_ignore_sep(char *line, int i, char c);
int		size_token(char *line, char c);
int		split_built(t_shell *shell);
int		init_struct(t_shell *shell, char *line);
int		is_builtin(char **cmd);
int		ft_strcmp(const char *str1, const char *str2);
int		exec_pipex(t_shell *shell);
int		check_redir(char **cmd);
char	**init_start_cmd(t_shell *shell, char *cmd_line, int index);
void	find_redir(t_shell *shell, char **cmd, int j);
void	dup_and_close(int oldfd, int newfd);
#endif