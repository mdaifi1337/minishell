/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:02:11 by mdaifi            #+#    #+#             */
/*   Updated: 2021/10/26 16:01:03 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	iterate_token_list(t_token *current, t_token *prev)
{
	while (current)
	{
		if (current->type == e_end && prev->type == e_pipe)
		{
			printf("\033[1;31mminishell >\033[0m");
			printf(" Multiple line commands are not treated...\n");
			return (0);
		}
		else if (current->type != e_word && prev->type != e_word
			&& prev->type != e_pipe)
		{
			printf("\033[1;31mminishell >\033[0m syntax error near ");
			printf("unexpected token `%s'\n", current->token);
			return (0);
		}
		current = current->next;
		if (current)
			prev = current->prev;
	}
	return (1);
}

int	check_token_syntax(t_token *token_list)
{
	t_token	*prev;
	t_token	*current;

	prev = token_list;
	current = token_list->next;
	if (current->type != e_word && prev->type == e_start)
	{
		printf("\033[1;31mminishell :\033[0m syntax error ");
		if (current->type != e_pipe)
			printf("unexpected token `%s'\n", current->next->token);
		else
			printf("unexpected token `%s'\n", current->token);
		return (0);
	}
	else
	{
		current = current->next;
		prev = current->prev;
		if (!iterate_token_list(current, prev))
			return (0);
	}
	return (1);
}
