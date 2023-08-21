/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:31:19 by zlemery           #+#    #+#             */
/*   Updated: 2023/08/21 19:47:19 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>
#include <unistd.h>

int	is_token(char *line, int *i, char c)
{
	char	quote;

	quote = c;
	while (line[*i] && (line[*i] != c || quote != c))
	{
		if (quote == c && (line[*i] == '\'' || line[*i] == '\"'))
			quote = line[(*i)++];
		else if (quote != c && line[*i] == quote)
		{
			quote = c;
			*i += 1;
		}
		else
			*i += 1;
		if (line[*i] == '\\' && line[(*i)++])
			*i += 1;
	}
	return (1);
}

int	split_built(t_shell *shell)
{
	int		ret;
	char	**tab;

	ret = 0;
	tab = init_start_cmd(shell, shell->token[0], 0);
	if (!tab)
		return (0);
	ret = is_builtin(tab);
	free_all(tab);
	return (ret);
}

int	init_struct(t_shell *shell, char *line)
{
	int	i;

	i = 0;
	shell->index = 0;
	shell->fdin = 0;
	shell->fdout = 0;
	shell->token = split_token(line, '|');
	if (!shell->token)
		return (-1);
	shell->nb_cmd = count_cmd(shell->token);
	if (shell->nb_cmd)
		shell->pid = malloc(sizeof(int) * shell->nb_cmd);
	if (!shell->pid)
		return (-1);
	while (shell->token[i])
	{
		printf("token[%d] = %s\n", i, shell->token[i]);
		i++;
	}
	printf("nb_cmd = %d\n", shell->nb_cmd);
	return (0);
}

int	is_redir(char *redir)
{
	int	i;

	i = 0;
	if (!ft_strcmp(">", redir))
		return (1);
	else if (!ft_strcmp(">>", redir))
		return (3);
	else if (!ft_strcmp("<", redir))
		return (2);
	else if (!ft_strcmp("<<", redir))
		return (2);
	return (0);
}

int	count_redir(char **line)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i][0] == '<' || line[i][0] == '>')
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	**delete_redir(char **line)
{
	int		i;
	int		j;
	char	**ret;
	int		size;

	i = 0;
	j = 0;
	size = count_redir(line);
	if (!size)
		return (line);
	printf("%d\n", size + 1);
	ret = malloc(sizeof(char *) * (size + 1));
	while (line[i])
	{
		if (line[i][0] == '<' || line[i][0] == '>')
			i++;
		else
		{
			ret[j] = ft_strdup(line[i]);
			i++;
			j++;
		}
	}
	ret[j] = 0;
	return (ret);
}

void	open_fdin(t_shell *shell, char **cmd, int i)
{
	shell->fdin = open(cmd[i + 1], O_RDONLY);
	if (shell->fdin == -1)
		printf("ERRREUR fdin");
}

void	open_fdout(t_shell *shell, char **cmd, int i)
{
	if (is_redir(cmd[i]) == 1)
		shell->fdout = open(cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (is_redir(cmd[i]) == 3)
		shell->fdout = open(cmd[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (shell->fdout == -1)
		printf("ERREUR fdout");
}

void	open_redir(t_shell *shell, char **cmd, int i)
{
	int	redir;

	redir = is_redir(cmd[i]);
	if (redir == 1 || redir == 3)
		open_fdout(shell, cmd, i);
	if (redir == 2)
		open_fdin(shell, cmd, i);
	if (redir == 4)
		printf("here_doc\n");
//		open_here_doc(shell);
/*	if (redir == 1 || redir == 3)
		dup_and_close(shell->fdout, STDOUT_FILENO);
	if (redir == 2)
		dup_and_close(shell->fdin, STDIN_FILENO);
		*/
}

void	find_redir(t_shell *shell, char **cmd, int j)
{
	int	i;

	i = 0;
	(void)j;
/*	if (shell->index != 0)
		dup_and_close(shell->prev_pipe, STDIN_FILENO);
	if (shell->index != shell->nb_cmd - 1)
		dup_and_close(shell->pipefd[1], STDOUT_FILENO);
	if (j > 0)
	{
		close(shell->pipefd[0]);
		close(shell->pipefd[1]);
	}*/
	while (cmd[i])
	{
		open_redir(shell, cmd, i);
		i++;
	}
/*	i = -1;
	while (++i < shell->nb_here)
		//close les here_doc
	//s'occuper des redirections du here_doc;
*/
}

char	**search_expansion(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		tab[i] = ft_expansions(tab[i]);
		if (!tab[i])
		{
			free_all(tab);
			return (NULL);
		}
		i++;
	}
	return (tab);
}

char	**init_start_cmd(t_shell *shell, char *cmd_line, int index)
{
	int		i;
	char	**tab;

	i = 0;
	(void)shell;
	tab = split_token(cmd_line, ' ');
	tab = search_expansion(tab);
	if (!tab)
		return (NULL);
	if (index)
	{
		/*if (check_redir(tab) == -1)
		{
			// close les pipes pour cause d'erreur
			return (NULL);
		}*/
		find_redir(shell, tab, index);
	}
	tab = delete_redir(tab);
//	while (tab[i])
//		tab[i++] = delete_quote(tab[i]);
	while (tab[i])
		printf("after expansion = %s\n", tab[i++]);
	return (tab);
}
