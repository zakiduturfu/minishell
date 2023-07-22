/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlemery <zlemery@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:31:19 by zlemery           #+#    #+#             */
/*   Updated: 2023/07/22 01:45:19 by zlemery          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
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
	shell->token = split_token(line, '|');
	if (!shell->token)
		return (-1);
	shell->nb_cmd = count_cmd(shell->token);
	if (shell->nb_cmd)
		shell->pid = malloc(sizeof(int) * shell->nb_cmd);
	if (!shell->pid)
		return (-1);
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

char	**delete_redir(char **line)
{
	int		i;
	char	**ret;
	int		size;

	i = 0;
	size = find_redir(line);
	if (!size)
		return (line);
	ret = malloc(sizeof(char *) * (size + 1));
	while (line[i])
	{
		if (line[i][0] == '<' || line[i][0] == '>')
			i++;
		else
			ret[i] = ft_strdup(line[i]);
		i++;
	}
	ret[i] = 0;
	return (ret);
}

void	open_redir(t_shell *shell, char *cmd)
{
	int	redir;

	redir = is_redir(cmd);
	if (redir == 1 || redir == 3)
		open_fdout(shell);
	if (redir == 2)
		open_fdin(shell);
	if (redir == 4)
		here_doc ;
	if (redir == 1 || redir == 3)
		dup_and_close(shell->fdout, STDOUT_FILENO);
	if (redir == 2)
		dup_and_close(shell->fdin, STDIN_FILENO);
}

void	find_redir(t_shell *shell, char **cmd)
{
	int	i;

	i = 0;
	if (index != 0)
		dup_and_close(pipefd[0], STDIN_FILENO);
	if (index != shell->nb_cmd - 1)
		dup_and_close(pipefd[1], STDOUT_FILENO);
	while (cmd[i])
	{
		open_redir(shell, cmd[i]);
		i++;
	}
	i = -1;
	while (++i < shell->here)
		//close les here_doc
	//s'occuper des redirections du here_doc;
}

char	**init_start_cmd(t_shell *shell, char *cmd_line, int index)
{
	int		i;
	char	**tab;

	i = 0;
	tab = split_token(cmd_line, ' ');
	if (!tab)
		return (NULL);
	if (index)
	{
		if (check_redir(tab) == -1)
		{
			/* close les pipes pour cause d'erreur*/
			return (NULL);
		}
		find_redir(tab);
	}
	tab = delete_redir(tab);
/*	while (tab[i])
		tab[i++] = delete_quote(tab[i]);*/
	return (tab);
}
