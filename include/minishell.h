/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:57:08 by zlemery           #+#    #+#             */
/*   Updated: 2023/08/25 15:54:56 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include <stdbool.h>

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
int		free_expand(char **tab, int index);
char	**find_expansion(char **tab);
int		search_expand(char *str);

/* /src/file/redirections.c */
void	dup_and_close(int oldfd, int newfd);
void	open_fdin(t_shell *shell, char **cmd, int i);
void	open_fdout(t_shell *shell, char **cmd, int i);
void	open_redir(t_shell *shell, char **cmd, int i);
void	find_redir(t_shell *shell, char **cmd, int j);

/* /src/parsing/pars_cmd_line.c */
char	*space_sep(char *line);
char	*line_arg(char *line);
int		init_struct(t_shell *shell, char *av, char **env);
int		pars_line(char *line, char **env);

/* /src/parsing/split_token.c */
char	**split_token(char *line, char c, char *av);
char	*recup_token(char *line, int *i, char c, char *av);
int		token_alloc(char *line, int *i, char c, char *av);
int		t_ignore_sep(char *line, int i, char c, char *av);

/* /src/parsing/token.c */
int		is_token(char *line, int *i, char c, char *av);
int		find_built(t_shell *shell, char *av);
char	**init_start_cmd(t_shell *shell, char *cmd_line, int index, char *av);

/* /src/tools/parsing/token_utils.c*/
int		is_in_quote(char *line, int i, char c);
int		ft_strcmp(const char *str1, const char *str2);
int		size_token(char *line, char c, char *av);
int		check_redir(char **cmd);
int		is_builtin(char *cmd);
int		count_cmd(char **tab);

/* /src/tools/parsing/pars_cmd_line_utils.c */
int		is_sep(char *line, int i);
int		is_quote(char *line, int i);
int		ignore_sep(char *line, int i);

/* /src/tools/file/redirections_utiles.c*/
char	**delete_redir(char **line);
int		count_redir(char **line);
int		is_redir(char *redir);

/* /src/pipex/process.c */
void	child_err(t_shell *shell, char **cmd, char **env, char *av);
char	**get_cmd_path(char **env);
char	*recup_path(char *cmd, char **env);
void	child_process(t_shell *shell, int i, char *av, char **env);
void	parent_process(t_shell *shell);

/* /src/pipex/pipex.c */
int		pipex(t_shell *shell, char *av, char **env);
void	dup_and_close(int oldfd, int newfd);

/* /src/builtins/exec.c */
/*static char	**ft_split_cmd(char *token, char **tab)*/
int		ft_pwd(void);
int		ft_export(t_shell *shell, char *str);
int		exec_only_built(t_shell	*shell);

/* /src/builtins/echo.c */
/*void		print(char *str, int newline)*/
/*static int	n_param(char *str, int *i)*/
int		open_quote(char *str);
int		dquote(void);
int		ft_echo(char **tab);

/* /src/builtins/export.c */
//static int	find_var(t_shell *shell, char *var);
//static int	ft_parse_var(char *str, unsigned int *i);
//static int	ft_change_val(t_shell *shell, unsigned int posi, char *val, unsigned int i);
//static int	ft_create_var(t_shell *shell, char *var);
int	ft_export_one_by_one(t_shell *shell, char *str);

/* /src/builtins/unset.c */
//static int	find_var(t_shell *shell, char *var);
//static int	ft_parse_var(char *str, unsigned int *i);
int	ft_unset_one_by_one(t_shell *shell, char *str);
int	ft_unset(t_shell *shell, char *str);

#endif