#include "minishell.h"

t_type	redirections(char *str, int i)
{
	if (!ft_strncmp(str + i, "<<", 2))
		return (e_dless);
	if (!ft_strncmp(str + i, ">>", 2))
		return (e_dgreat);
	if (!ft_strncmp(str + i, "<", 1))
		return (e_less);
	if (!ft_strncmp(str + i, ">", 1))
		return (e_great);
	if (!ft_strncmp(str + i, "|", 1))
		return (e_pipe);
	return (e_word);
}

void	lst_add_back_token(t_token **token_list, t_type type, char *str)
{
	t_token	*new;
	t_token	*tmp;

	new = (t_token *)malloc(sizeof(t_token));
	new->token = ft_strdup(str);
	new->type = type;
	new->next = NULL;
	tmp = *token_list;
	if (*token_list == NULL)
		*token_list = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	*get_token(char *str, int *i, t_type *type)
{
	int		double_quote;
	int		single_quote;
	char	*res;
	int		j;
	int		count;

	j = *i;
	count = 0;
	double_quote = 0;
	single_quote = 0;
	*type = redirections(str, *i);
	if (*type)
	{
		count = 1;
		if (*type == e_dless || *type == e_dgreat)
			count = 2;
	}
	else
	{
		while (str[j] && (!ft_strchr(" |<>", str[j]) || (double_quote || single_quote)))
		{
			if (str[j] == '\"')
				double_quote = 1 - double_quote;
			if (str[j] == '\'')
				single_quote = 1 - single_quote;
			j++;
			count++;
		}
	}
	res = (char *)malloc(sizeof(char) * count + 1);
	j = -1;
	while (count > 0)
	{
		res[++j] = str[*i];
		(*i)++;
		count--;
	}
	res[++j] = '\0';
	return (res);
}

t_token	*tokenize_command_line(char *str)
{
	t_type	type;
	t_token	*token_list;
	t_token	*tmp;
	char	*token;
	int		i;

	i = 0;
	token_list = NULL;
	lst_add_back_token(&token_list, e_start, "start");
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
		{
			token = get_token(str, &i, &type);
			lst_add_back_token(&token_list, type, token);
		}
	}
	lst_add_back_token(&token_list, e_end, "newline");
	return (token_list);
}

void	insert_dollar_vars_in_vector(t_vector *v, int size, int curr_pos)
{
	int	i;
	int	j;

	if (v->used_size + size > v->size)
		vector_resize(v, v->size + size);
	i = (v->used_size + size) - 1;
	j = v->used_size - 1;
	while (j > curr_pos && v->args[j])
	{
		v->args[i] = ft_strdup(v->args[j]);
		free(v->args[j]);
		v->args[j] = NULL;
		j--;
		i--;
	}
}

void	split_dollar_var(t_vector *v, int i, int curr_pos, char *value)
{
	char	*tmp;
	char	**tab;
	int		size;
	int		j;
	t_char_vec	new_char_vec;

	tmp = ft_strdup(v->args[i]);
	init_char_vec(&new_char_vec);
	tab = ft_split(value, ' ');
	j = -1;
	while (tmp[++j] != '$')
		char_vec_add(&new_char_vec, tmp[j]);
	if (tmp[curr_pos] != ' ')
	{
		j = -1;
		while (tab[0][++j])
			char_vec_add(&new_char_vec, tab[0][j]);
	}
	size = 0;
	while (tab[size])
		size++;
	insert_dollar_vars_in_vector(v, size - 1, i);
	j = 0;
	while (tab[++j])
	{
		vector_add_at_index(v, i, new_char_vec.arg);
		free(new_char_vec.arg);
		init_char_vec(&new_char_vec);
		size = -1;
		while (tab[j][++size])
			char_vec_add(&new_char_vec, tab[j][size]);
		i++;
	}
	if (tmp[curr_pos] != '\0')
	{
		free(new_char_vec.arg);
		init_char_vec(&new_char_vec);
		size = -1;
		while (tab[j - 1][++size])
			char_vec_add(&new_char_vec, tab[j - 1][size]);
		while (tmp[curr_pos])
		{
			char_vec_add(&new_char_vec, tmp[curr_pos]);
			curr_pos++;
		}
		vector_add_at_index(v, i, new_char_vec.arg);
	}
	else
		v->args[i] = ft_strdup(tab[j - 1]);
	free(tmp);
}

void	remove_quotes(t_vector *v)
{
	int	i;
	int	j;
	int	squote;
	t_char_vec	new_char_vec;

	i = -1;
	squote = 0;
	while (++i < v->used_size)
	{
		init_char_vec(&new_char_vec);
		j = -1;
		while (v->args[i][++j])
		{
			if (v->args[i][j] == '\'')
			{
				squote = 1 - squote;
				j++;
			}
			if (v->args[i][j] == '\"' && !squote)
				j++;
			char_vec_add(&new_char_vec, v->args[i][j]);
		}
		free(v->args[i]);
		v->args[i] = ft_strdup(new_char_vec.arg);
		free(new_char_vec.arg);
	}
}

void	replace_dollar_var_by_value(t_vector *v, int curr_pos, char *name, char *value)
{
	int			i;
	int			j;
	char		*tmp;
	t_char_vec	new_char_vec;

	tmp = ft_strdup(v->args[curr_pos]);
	init_char_vec(&new_char_vec);
	i = -1;
	while (tmp[++i] != '$')
		char_vec_add(&new_char_vec, tmp[i]);
	j = -1;
	while (value[++j])
		char_vec_add(&new_char_vec, value[j]);
	j = -1;
	while (name[++j])
		i++;
	while (tmp[++i])
	{
		char_vec_add(&new_char_vec, tmp[i]);
	}
	free(v->args[curr_pos]);
	v->args[curr_pos] = ft_strdup(new_char_vec.arg);
	free(tmp);
}

void	expand_dollar_var(t_vector *v, int i)
{
	int			dquote;
	int			squote;
	char		*value;
	int			j;
	t_char_vec	name;

	name.arg = NULL;
	value = NULL;
	j = -1;
	dquote = 0;
	squote = 0;
	while (v->args[i][++j])
	{
		if (v->args[i][j] == '\"')
			dquote = 1 - dquote;
		if (v->args[i][j] == '\'')
			squote = 1 - squote;
		if (v->args[i][j] == '$' && !squote)
		{
			init_char_vec(&name);
			while (v->args[i][++j] && (ft_isalnum(v->args[i][j]) || v->args[i][j] == '_') && v->args[i][j] != '?')
				char_vec_add(&name, v->args[i][j]);
			value = getenv(name.arg);
			if (!dquote && value)
				split_dollar_var(v, i, j,value);
			else
				replace_dollar_var_by_value(v, i, name.arg, value);
		}
	}
}

void	look_for_expandable_vars(t_cmd_line *cmd_line)
{
	int			i;
	t_cmd_line	*tmp;

	tmp = cmd_line;
	// If you have $ inside a dollar variable, ignore the whole world
	while (tmp)
	{
		i = -1;
		while (++i < tmp->args.used_size)
			expand_dollar_var(&tmp->args, i);
		remove_quotes(&tmp->args);
		tmp = tmp->next;
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_cmd_line	*cmd_line;
	t_cmd_line	*tmp;
	t_redirect	*tmp_redir;
	t_token		*token_list;
	char		*str;
	int			true;
	int			i;

	true = 1;
	cmd_line = NULL;
	while (true)
	{
		str = readline("minishell > ");
		if (ft_strlen(str))
		{
			if (!ft_strncmp(str, "exit", 5))
				true = 0;
			else
			{
				token_list = tokenize_command_line(str);
				if (!check_token_syntax(token_list))
					ft_free_list(token_list);
				else
				{
					cmd_line = treat_pipe_sequence(token_list);
					look_for_expandable_vars(cmd_line);
					tmp = cmd_line;
					while (tmp)
					{
						i = -1;
						while (++i < tmp->args.used_size)
							printf("---- |%s|\n", tmp->args.args[i]);
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
					
				}
				free(str);
				free_cmd_line_list(cmd_line);
				cmd_line = NULL;
			}
		}
	}
	return (0);
}