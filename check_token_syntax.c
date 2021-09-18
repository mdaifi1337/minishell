#include "minishell.h"

int	check_token_syntax(t_token *token_list)
{
	int		ok;
	t_token	*it_token;
	t_token *previous;
	t_token *current;

	it_token = token_list->next;
	previous = token_list;
	current = token_list->next;
	if (current->type != e_word && previous->type == e_start)
	{
		printf("\033[1;31mminishell :\033[0m syntax error near unexpected token `%s'\n", current->token);
		return (0);
	}
	else
	{
		ok = 1;
		while (it_token && ok)
		{
			if (current->type != e_word && previous->type != e_word && previous->type != e_pipe)
			{
				ok = 0;
				printf("\033[1;31mminishell :\033[0m syntax error near unexpected token `%s'\n", current->token);
				return (0);
			}
			previous = current;
			it_token = it_token->next;
			if (it_token)
				current = it_token;
		}
	}
	return (1);
}