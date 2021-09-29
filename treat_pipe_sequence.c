#include "minishell.h"

static int	check_nbr_of_quotes(char *str)
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

t_cmd_line	*treat_pipe_sequence(t_token *token_list)
{
	t_vector	v;
	t_cmd_line	*cmd_line;
	t_cmd_line	*tmp;
	t_token		*it_list;
	t_redirect	*redirect;
	t_redirect	*tmp_redir;
	t_token		token;
	int i;

	i = 0;
	it_list = token_list->next;
	vector_init(&v);
	cmd_line = NULL;
	redirect = NULL;
	token.type = e_word;
	token.token = ft_strdup("");
	while (it_list)
	{
		if (it_list->type == e_pipe || it_list->type == e_end)
		{
			lst_add_back_cmd(&cmd_line, v, redirect);
			token.type = e_word;
			free(token.token);
			token.token = ft_strdup("");
			vector_init(&v);
			// printf("OK\n");
			ft_free_redirect_list(redirect);
			redirect = NULL;
		}
		else if (it_list->type != e_word)
		{
			token.type = it_list->type;
			it_list = it_list->next;
			token.token = it_list->token;
			lst_add_back_redirect(&redirect, token.type, token.token);
			free(token.token);
			token.token = NULL;
		}
		else
			vector_add(&v, it_list->token);
		it_list = it_list->next;
	}
	return (cmd_line);
}