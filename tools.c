#include "minishell.h"

void	ft_free_list(t_list *head)
{
	t_list	*tmp;

	tmp = head;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}