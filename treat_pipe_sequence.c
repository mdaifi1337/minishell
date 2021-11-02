/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_pipe_sequence.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 15:44:23 by mdaifi            #+#    #+#             */
/*   Updated: 2021/10/30 17:50:23 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_nbr_of_quotes(char *str)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = -1;
	single_quote = 0;
	double_quote = 0;
	while (str[++i])
	{
		if (str[i] == '\"')
			double_quote = 1 - double_quote;
		if (str[i] == '\'' && !double_quote)
			single_quote = 1 - single_quote;
	}
	if (double_quote || (!double_quote && single_quote))
	{
		write(2, "Error, unclosed quotes!\n", 25);
		return (0);
	}
	return (1);
}

static void	save_redir(t_token **it_list, t_token *token, t_redir **redir)
{
	token->type = (*it_list)->type;
	*it_list = (*it_list)->next;
	token->token = (*it_list)->token;
	lst_add_back_redir(redir, token->type, token->token);
	free(token->token);
	token->token = NULL;
}

static void	save_pipe_sequence(t_cmd_line **cmd_line, t_vector *v,
	t_token *token, t_redir **redir)
{
	lst_add_back_cmd(cmd_line, *v, *redir);
	token->type = e_word;
	free(token->token);
	token->token = ft_strdup("");
	free_array_of_strings(v->args, v->size);
	vector_init(v);
	ft_free_redir_list(*redir);
	*redir = NULL;
}

t_cmd_line	*treat_pipe_sequence(t_token *token_list)
{
	t_vector	v;
	t_cmd_line	*cmd_line;
	t_token		*it_list;
	t_redir		*redir;
	t_token		token;

	it_list = token_list->next;
	vector_init(&v);
	cmd_line = NULL;
	redir = NULL;
	token.type = e_word;
	token.token = ft_strdup("");
	while (it_list)
	{
		if (it_list->type == e_pipe || it_list->type == e_end)
			save_pipe_sequence(&cmd_line, &v, &token, &redir);
		else if (it_list->type != e_word)
			save_redir(&it_list, &token, &redir);
		else if (it_list->type == e_word)
			vector_add(&v, it_list->token);
		it_list = it_list->next;
	}
	return (cmd_line);
}
