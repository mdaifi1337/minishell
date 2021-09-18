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

char	*allocate_word(char *str)
{
	char	*res;
	int		size;
	int		j;
	int		i;
	int		double_quote;
	int		single_quote;

	size = 0;
	double_quote = 0;
	single_quote = 0;
	if (str[i] == ' ')
		i++;
	i = 0;
	while (str[i] && (str[i] != ' ' || (double_quote || single_quote)))
	{
		if (str[i] == '\"')
			double_quote = 1 - double_quote;
		if (str[(i)] == '\'')
			single_quote = 1 - single_quote;
		size++;
		i++;
	}
	res = (char *)malloc(sizeof(char) * size + 1);
	i = 0;
	j = 0;
	while (i < size)
	{
		// while (str[(j)] == '\"' || str[(j)] == '\'')
		// 	j++;
		res[i++] = str[j++];
	}
	res[i] = '\0';
	return (res);
}

t_cmd_line	*treat_pipe_sequence(t_token *token_list)
{
	t_vector	*v;
	t_cmd_line	*cmd_line;
	t_cmd_line	*tmp;
	t_token		*it_list;
	t_redirect	*redirect;
	t_redirect	*tmp_redir;
	t_type		type;
	char		*infile;
	int i;

	i = 0;

	it_list = token_list->next;
	v = (t_vector *)malloc(sizeof(t_vector));
	vector_init(v);
	cmd_line = NULL;
	redirect = NULL;
	type = e_word;
	infile = ft_strdup("");
	while (it_list)
	{
		if (it_list->type == e_pipe || it_list->type == e_end)
		{
			lst_add_back_cmd(&cmd_line, v, redirect);
			type = e_word;
			free(infile);
			infile = ft_strdup("");
			free_vector(v);
			vector_init(v);
			// printf("OK\n");
			ft_free_redirect_list(redirect);
			redirect = NULL;
		}
		else if (it_list->type != e_word)
		{
			type = it_list->type;
			it_list = it_list->next;
			infile = allocate_word(it_list->token);
			lst_add_back_redirect(&redirect, type, infile);
			free(infile);
			infile = NULL;
		}
		else
			vector_add(v, allocate_word(it_list->token));
		it_list = it_list->next;
	}
		tmp = cmd_line;
		while (tmp)
		{
			i = -1;
			while (tmp->args[++i])
				printf("---- |%s|\n", tmp->args[i]);
			tmp_redir = tmp->redirect;
			while (tmp_redir)
			{
				printf("+++ %s\n", tmp_redir->file);
				printf("+++ %d\n", tmp_redir->type);
				tmp_redir = tmp_redir->next;
			}
			printf("~~~~~~~~~~~~~~~~~~~~~~\n");
			tmp = tmp->next;
		}
	return (cmd_line);
}