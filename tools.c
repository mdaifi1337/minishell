#include "minishell.h"

void	ft_free_list(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->token);
		free(tmp);
	}
}

void	ft_free_redirect_list(t_redirect *head)
{
	t_redirect	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->file);
		free(tmp);
	}
}

char	**copy_table(char **tab, int size)
{
	char	**args;
	int		i;

	args = (char **)malloc(sizeof(char *) * size + 1);
	i = -1;
	while (++i < size)
		args[i] = ft_strdup(tab[i]);
	args[i] = NULL;
	return (args);
}