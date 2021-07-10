#include "minishell.h"

int	check_token_syntax(t_list *token_list)
{
	int		ok;
	t_list	*it_token;
	t_token *previous;
	t_token *current;

	it_token = token_list->next;
	current = (t_token *)token_list->next->content;
	previous = (t_token *)token_list->content;
	ok = 1;
	if (current->type != e_word && previous->type == e_start)
	{
		printf("\033[1;31mminishell :\033[0m syntax error near unexpected token `%s'\n", current->token);
		return (0);
	}
	else
	{
		while (it_token && ok)
		{
			if (current->type != e_word && previous->type != e_word)
			{
				ok = 0;
				printf("\033[1;31mminishell :\033[0m syntax error near unexpected token `%s'\n", current->token);
				return (0);
			}
			free(previous);
			previous = current;
			it_token = it_token->next;
			if (it_token)
				current = (t_token *)it_token->content;
		}
	}
	return (1);
}