#include "../../include/minishell.h"

static int	ft_all_history(t_shell *shell)
{
	t_lines			*tmp;
	unsigned int	i;

	tmp = shell->lines;
	if (!tmp)
		return (0);
	while (tmp->next != NULL)
	{
		i = tmp->index;
		tmp = tmp->next;
	}
	if (tmp->index == 1)
		return (0);
	tmp = tmp->prev;
	printf("index max = %d\n", i);
	printf("index tmp = %d\n", tmp->index);
	while (tmp->index > 1 && (i <= 16 || i - tmp->index < 15))
		tmp = tmp->prev;
	printf("blabla\n");
	while (tmp->next != NULL)
	{
		printf("   %d  ", tmp->index);
		printf("%s\n", tmp->line);
		tmp = tmp->next;
	}
	return (0);
}

int	ft_history(t_shell *shell, char *str)
{
	// t_lines			*tmp;
	// unsigned int	i;

	if (!str || str[0] == '\0')
		ft_all_history(shell);
	// tmp = shell->lines;
	// i = 1;
	// while (tmp)
	// {
	// 	printf("\t%d  ", i);
	// 	printf("%s\n", tmp->line);
	// 	tmp = tmp->next;
	// 	i++;
	// }
	return (0);
}