/* ******************************************************************************* */
/*                                                                                  */
/*                                                        :::      ::::::::         */
/*   here_doc.c                                         :+:      :+:    :+:         */
/*                                                    +:+ +:+         +:+      		*/
/*   By: zlemery <zlemery@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           		*/
/*   Created: 2023/09/11 13:22:03 by zlemery              #+#    #+#             	*/
/*   Updated: 2023/09/11 13:28:05 by zlemery             ###   ########.fr       	*/
/*                                                                            		*/
/* ******************************************************************************** */

#include "../../include/minishell.h"

int	nb_heredoc(char *line)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (line[++i])
	{
		if ((line[i] == '<' && line[i - 1] != '\\')
			&& line[i + 1] == '<')
		{
			count++;
			i++;
		}
	}
	return (count);
}

int	create_here(t_shell *shell)
{
	if (shell->nb_here == 0)
		return (0);
	shell->here = malloc(sizeof(t_here) * shell->nb_here);
	if(!shell->here)
		return (-1);
	return (0);
}

int	recup_delim2(t_shell *shell, char **tmp, int j)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		printf("%s\n", tmp[i]);
		if (!ft_strcmp(tmp[i], "<<"))
		{
			shell->here[j].lim = delete_quote(tmp[i + 1]);
			free(tmp[i]);
			i++;
			pipe(shell->here[j].here_pipe);
			j++;
		}
		else
			free(tmp[i]);
		i++;
	}
	return (j);
}

int	recup_delim1(t_shell *shell)
{
	int		i;
	int		j;
	char	**tmp;

	i = -1;
	j = 0;
	while (shell->token[++i])
	{
		tmp = ft_split(shell->token[i], ' ');
		if (!tmp)
			return (-1);
		fix_quote((signed char **)tmp);
		tmp = find_expansion(tmp);
		if (check_redirections(tmp) == -1)
		{
			printf("ganged here");
			return (-1);
		}
		j = recup_delim2(shell, tmp, j);
	}
	return (1);
}

void	file_here(int i, t_here *here)
{
	char	*s;

	while(1)
	{
		s = readline("here_doc>");
		if (!s)
		{
			printf("oulala la catastrophe\n");
			break ;
		}
		else if (!ft_strcmp(s, here[i].lim))
		{
			free(s);
			break ;
		}
		else
		{
			ft_putendl_fd(s, here[i].here_pipe[1]);
			free(s);
		}
	}	close(here[i].here_pipe[0]);
}

void	child_here(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->nb_here)
	{
		file_here(i, shell->here);
		i++;
	}
	i = -1;
	while (++i < shell->nb_here)
		free(shell->here[i].lim);
	free(shell->pid);
	free_all(shell->token);
	free(shell);
	exit(0);
}

int	exec_here(t_shell *shell)
{
	int		i;
	pid_t	pid;

	i = -1;
	if (recup_delim1(shell) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
		child_here(shell);
	else if (pid > 0)
	{
		while (++i < shell->nb_here)
		{
			free(shell->here[i].lim);
			close(shell->here[i].here_pipe[1]);
		}
	}
	waitpid(pid, NULL, 0);
	return (1);
}

int	init_here(t_shell *shell)
{
	printf("shell->nb %d\n", shell->nb_here);
	if (shell->nb_here)
	{
		if (exec_here(shell) == -1)
		{
			return (-1);
		}
	}
	return (1);
}
