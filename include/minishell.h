/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstephan <hstephan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:57:08 by zlemery           #+#    #+#             */
/*   Updated: 2023/10/20 21:41:43 by hstephan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include <stdbool.h>
# include <sys/stat.h>
# include <errno.h>

typedef struct s_here
{
	char	*lim;
	int		here_pipe[2];
}	t_here;

typedef struct s_env
{
	char	**env;
}t_env;

typedef struct s_shell
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
	int		builtin;
	int		builtout;
	int		status;
	t_here	*here;
}	t_shell;

typedef struct s_quotes
{
	int		singles;
	int		doubles;
	bool	single_open;
	bool	double_open;
	int		this_s;
	int		this_d;
}	t_quotes;

/* /SRCBUILTINS*/

/* /src/builtins/builtins.c */
int			ft_cd(char ***env, char **tab, t_shell *shell);
int			is_builtin(char *cmd);
int			ft_pwd(t_shell *shell);
int			exec_only_built(t_shell	*shell, char ***env, int i, char **tab);

/* /src/builtins/cd_utils.c */
int			old_pwd(char ***env, int pwdposi);
int			cd_home(char ***env, t_shell *shell);
int			starting_directory(char **pwd, bool test);
int			previous_directory(char **pwd, bool test);
char		*start_directory(char *directory);

/* /src/builtins/cd.c */
//static int	is_directory(char **pwd, char *dir, char *initialpath)
//static int	this_directory(char **pwd, char *dir, bool test)
//static int	exec_cd(char **env, char **tab, int posi, char *start)
//static int	ft_verif_path(char **tab, char *test, char *initialpath)
int			try_exec_cd(char ***env, char *directory, int posi, char *start);

/* /src/builtins/echo.c */
//static void	print(char *str, int newline)
//static int	n_param(char *str, int *i)
int			ft_echo(char **tab, t_shell *shell);

/* /src/builtins/env.c */
int			ft_env(char **env, char **tab, t_shell *shell);
int			ft_ordonned_env(char **env, char *tmp, int i, char	**env_cop);

/* /src/builtins/exit.c */
//static int	ft_str_isdigit(char *s)
//static int	exit_mini(char **tab, char **env, t_shell *shell, int n)
void		ft_exit(char **tab, t_shell *shell, char **env);

/* /src/builtins/export.c */
//static int	ft_parse_var(char *str, unsigned int *i)
//static int	ft_change_val(char **env,
//		unsigned int posi, char *val, unsigned int i)
//static int	ft_create_var(char ***env, char *var, unsigned int i)
int			ft_export_one_by_one(char ***env, char *str);
int			ft_export(char ***env, char **tab, t_shell *shell);

/* /src/builtins/str_utils.c */
int			is_space(char c);
int			is_end(char c);

/* /src/builtins/unset.c */
//static int	ft_erase_var(t_shell *shell, int posi);
//static int	ft_unset_one_by_one(t_shell *shell, char *str);
int			ft_unset(char ***env, char **tab, t_shell *shell);

/* /src/builtins/utils.c */
int			print_and_return(char *str, int i);
int			find_var(char **env, char *var);
void		ft_free_tab(char **tab);

/* SRC/ENV */

/* /src/env/env.c */
t_env		*create_env(void);
//static char		*dup_var_name(char *str, int index);
//static char		*find_var_name(char *env);
//static char		*recup_env_ligne(char *str);
char		**recup_env(char **env);

/* /src/env/expansions.c */
char		*ft_avengers(char *before, char *after, char *expand, char **env);
char		*get_expand_val(char *str, int i);
char		*get_after_expand(char *str);
char		*get_before_expand(char *str, int i);
char		*ft_expansions(t_shell *shell, char *str, char **env);

/* /src/env/shlvl.c */
// char		*modify_var_env(char *name, char **env, char *var);
// char		*recup_val_shlvl(char **env);
int			increment_shlvl(char **env);

/* /SRC/FILE */

/* /src/file/redirections.c */
// void		file_error(char *file, char **cmd, t_shell *shell, char **env);
int			open_fdin(t_shell *shell, char **cmd, int i, char **env);
int			open_fdout(t_shell *shell, char **cmd, int i, char **env);
int			open_redir(t_shell *shell, char **cmd, int i, char **env);
int			find_redir(t_shell *shell, char **cmd, int j, char **env);

/* src/file/signaux.c*/
void		handler_sig(int sig);
void		handler_cmd(int sig);
void		handler_here(int sig);
void		child_here(t_shell *shell, char **env);

/* /SRC/PARSING */

/* /src/parsing/init.c */
t_shell		*create_data(void);
int			init_struct(t_shell *shell, char *av);

/* /src/parsing/pars_cmd_line.c */
//static void	exec_line(char *line, char **env)
void		wait_bin(t_shell *shell);
void		loop_shell(char **env, char *line);
int			process_one_built(t_shell *shell, char *line, char ***env);
int			pars_line(char *line, char ***env);

/* /src/parsing/split_token.c */
int			t_ignore_sep(char *line, int i, char c, char *av);
int			token_alloc(char *line, int *i, char c, char *av);
char		*recup_token(char *line, int *i, char c, char *av);
char		**split_token(char *line, char c, char *av);

/* /src/parsing/syntax.c */
char		*space_sep(char *line);
char		*syntax_line(char *line, int i, int j);
int			is_empty_line(char *line);
//int	pipe_error(t_shell *shell)
int			check_pipe(char *line, t_shell *shell, int i);

/* /src/parsing/token.c */
int			is_token(char *line, int *i, char c, char *av);
int			find_built(t_shell *shell, char **env, int i);
void		fix_quote(signed char **line);
int			check_redirections(char **tab, int i);
char		**init_start_cmd(t_shell *shell,
				char *cmd_line, int index, char **env);

/* SRC/PIPEX */

/* /src/pipex/here_doc_utils.c */
int			nb_heredoc(char *line);
int			recup_delim2(t_shell *shell, char **tmp, int j);
int			recup_delim1(t_shell *shell, char **env);

/* /src/pipex/here_doc.c */
int			create_here(t_shell *shell);
void		file_here(int i, t_here *here);
int			exec_here(t_shell *shell, char **env);
int			init_here(t_shell *shell, char **env);

/* /src/pipex/pipex.c */
int			exec_process(t_shell *shell, int i, char ***env);
int			exec_pipex(t_shell *shell, char ***env);
int			pipex(t_shell *shell, char *av, char ***env);
void		parent_process(t_shell *shell);
void		ft_exec(t_shell *shell, char **cmd, int i, char ***env);

/* /src/pipex/process_utils.c */
int			empty_cmd(char **cmd);
int			cmd_exist(char **cmd);
char		*find_path(char *tab, char **path);
void		ft_good_bye(t_shell *shell, char ***env);
int			process_built(t_shell *shell, char ***env, int i);

/* /src/pipex/process.c */
void		child_err(t_shell *shell, char **cmd, char **env, int i);
char		**get_cmd_path(char *cmd, char **env);
char		*recup_path(char *cmd, char **env);
void		child_process(t_shell *shell, int i, char ***env);

/* SRC/TOOLS/ENV */

/* /src/tools/env/env_utils */
int			size_env(char **env);
void		free_env_tab(char **env);
char		*ret_status(char *before, char *after, char *status);
void		stat_expand(char **tab, char *str, int i, t_shell *shell);
char		*ft_getenv(char *name, char **env);

/* /src/tools/env/expansions_utils.c */
char		*get_val_env(char *name);
int			search_expand(char *str);
char		**find_expansion(t_shell *shell, char **tab, char **env);
int			free_expand(char **tab, int index);
void		tab_value(char **tab, char *str, int i, char **env);

/* SRC/TOOLS/FILE */

/* /src/tools/file/free_close.c*/
void		dup_and_close(int oldfd, int newfd);
void		free_shell(t_shell *shell, char *av, int index);
void		close_all_pipe(t_shell *shell);
void		safe_close(int fd);

/* /src/tools/file/redirections_utils.c*/
int			count_redir(char **line);
int			is_redir(char *redir);
char		**delete_redir(char **line, int i, int j);
void		close_in_here(t_shell *shell);

/* SRC/TOOLS/PARSING */

/* /src/tools/parsing/pars_cmd_line_utils.c */
int			is_sep(char *line, int i);
int			is_quote(char *line, int i);
int			count_quote(char *s);
char		*delete_quote(char *s, int i, int j);
int			check_line(t_shell *shell, char *line);

/* /src/tools/parsing/pars_cmd_line_utils2.c */
int			ignore_sep(char *line, int i);
int			del_quote(char *s);
int			del_slash(char *str);
int			is_slash(char *s, int i);
char		*ft_strstr(char *s, char *to_find);

/* /src/tools/parsing/token_utils.c*/
int			count_cmd(char **tab);
int			size_token(char *line, char c, char *av);
int			ft_strcmp(const char *str1, const char *str2);
int			is_in_quote(char *line, int i, char c);
char		**err_cmd(t_shell *shell, char **tab);

#endif