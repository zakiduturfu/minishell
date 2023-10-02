/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:57:08 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/02 11:37:27 by hstephan         ###   ########.fr       */
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

typedef struct s_here
{
	char	*lim;
	int		here_pipe[2];
}	t_here;

typedef	struct s_shell
{
	char	**token;
	char	**env;
	char	*av;
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
	int		c_here;
	t_here	*here;
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
int		init_struct(t_shell *shell, char *av);
int		pars_line(char *line, char ***env);

/* /src/parsing/split_token.c */
char	**split_token(char *line, char c, char *av);
char	*recup_token(char *line, int *i, char c, char *av);
int		token_alloc(char *line, int *i, char c, char *av);
int		t_ignore_sep(char *line, int i, char c, char *av);

/* /src/parsing/token.c */
int		is_token(char *line, int *i, char c, char *av);
int		find_built(t_shell *shell);
int		check_redirections(char **tab);
void	fix_quote(signed char **line);
char	**init_start_cmd(t_shell *shell, char *cmd_line, int index);

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
char	*quote_line(char c, char *s, int count);
char	*delete_quote(char *s);

/* /src/tools/file/redirections_utiles.c*/
char	**delete_redir(char **line);
int		count_redir(char **line);
int		is_redir(char *redir);
void	close_in_here(t_shell *shell);
void	wait_bin(t_shell *shell);

/* /src/pipex/process.c */
void	child_err(t_shell *shell, char **cmd, char **env);
char	**get_cmd_path(char **env);
char	*recup_path(char *cmd, char **env);
void	child_process(t_shell *shell, int i, char ***env);
void	parent_process(t_shell *shell);

/* /src/pipex/here_doc.c */
int		nb_heredoc(char *line);
int		create_here(t_shell *shell, char *av);
int		recup_delim1(t_shell *shell);
int		recup_delim2(t_shell *shell, char **tmp, int j);
void	file_here(int i, t_here *here);
void	child_here(t_shell *shell);
int		exec_here(t_shell *shell);
int		init_here(t_shell *shell, char *av);

/* /src/pipex/pipex.c */
int		pipex(t_shell *shell, char *av, char ***env);
void	dup_and_close(int oldfd, int newfd);
t_shell	*create_data(void);
void	loop_shell(char **env);
void	free_shell(t_shell *shell, char *av);
void	close_all_pipe(t_shell *shell);

/* /src/builtins/exec.c */
int		ft_pwd(char **env, char *str);
int		ft_env(char **env);
int		ft_exit(char **env);
int		exec_only_built(t_shell	*shell, char ***env);

/* /src/builtins/echo.c */
/*void		print(char *str, int newline)*/
/*static int	n_param(char *str, int *i)*/
int		open_quote(char *str);
int		dquote(void);
int		ft_echo(char **tab);

/* /src/builtins/export.c */
int		ft_export_one_by_one(char ***env, char *str);
int		ft_export(char ***env, char *str);

/* /src/builtins/unset.c */
/*static int	ft_parse(char *str, unsigned int i);*/
/*static int	ft_erase_var(t_shell *shell, int posi);*/
/*static int	ft_unset_one_by_one(t_shell *shell, char *str);*/
int		ft_unset(char ***env, char *str);

/* /src/builtins/utils.c */
int		print_and_return(char *str, int i);
int		find_var(char **env, char *var);
char	**ft_split_cmd(char *token, char **tab, unsigned int i);
void	ft_free_tab(char **tab);
int		ft_ordonned_env(char **env);

/* /src/builtins/cd.c */
int		ft_cd(char **env, char *str);

#endif