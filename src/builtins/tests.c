#include <stdlib.h>
#include <stdio.h>

int	ft_echo(char **tab);

static char	**ft_split_cmd(char *token, char **tab)
{
	int		i;

	i = 0;
	while (token[i] != ' ' && token[i] != '\0')
		i++;
	tab = malloc (sizeof(char *) * 2);
	if (!tab)
		return (NULL);
	tab[0] = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (token[i] != ' ' && token[i] != '\0')
	{
		tab[0][i] = token[i];
		i++;
	}
	tab[0][i] = '\0';
	if (!(tab[0]))
	{
		free(tab);
		return (NULL);
	}
	while (token[i] == ' ')
		i++;
	tab[1] = &(token[i]);
	return (tab);
}

int main(int ac, char **av)
{
	char **tab;
	
	tab = NULL;
	if (ac < 2)
		return (1);
	tab = ft_split_cmd(av[1], tab);
	if (!tab)
		return (1);
	ft_echo(tab);
	return (0);
}