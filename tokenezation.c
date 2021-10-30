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
			if (!check_nbr_of_quotes(token))
			{
				free_token_list(token_list);
				return (NULL);
			}
			lst_add_back_token(&token_list, type, token);
		}
	}
	lst_add_back_token(&token_list, e_end, "newline");
	return (token_list);
}

void	split_dollar_var(t_vector *v, int i, int curr_pos, char *value)
{
	char	*tmp;
	char	**tab;
	int		size;
	int		j;
	t_char_vec	new_char_vec;

	printf("split\n");
	tmp = ft_strdup(v->args[i]);
	init_char_vec(&new_char_vec);
	tab = ft_split(value, ' ');
	size = 0;
	while (tab[size])
		size++;
	if (tab[0])
	{
		j = -1;
		while (tmp[++j] != '$')
			char_vec_add(&new_char_vec, tmp[j]);
		if (tmp[curr_pos] != ' ')
		{
			j = -1;
			while (tab[0][++j])
				char_vec_add(&new_char_vec, tab[0][j]);
		}
		j = 0;
		if (size > 1)
		{
			insert_dollar_vars_in_vector(v, size - 1, i);
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
		}
		else
		{
			if (tmp[curr_pos] != '\0')
			{
				while (tmp[curr_pos])
				{
					char_vec_add(&new_char_vec, tmp[curr_pos]);
					curr_pos++;
				}
			}
			free(v->args[i]);
			v->args[i] = ft_strdup(new_char_vec.arg);
		}
	}
	else
	{
		if (v->args[i + 1] == NULL || v->used_size == i + 1)
			ignore_dollar_var(v, i);
		else
		
			resize_vec_when_dollar_var_empty(v, i);
	}
	free(tmp);
	free(new_char_vec.arg);
	free_array(tab);
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
		if (v->args[i][j] == '$')
		{
			init_char_vec(&name);
			while (v->args[i][++j] && (ft_isalnum(v->args[i][j]) || v->args[i][j] == '_') && v->args[i][j] != '?')
				char_vec_add(&name, v->args[i][j]);
			value = getenv(name.arg);
			if (!squote && !dquote && value)
				split_dollar_var(v, i, j,value);
			else if (!squote && dquote && value)
				replace_dollar_var(v, i, name.arg, value);
			else if (!value)
				dollar_var_not_found(v, i);
			free(name.arg);
		}
	}
}

void	look_for_expandable_vars(t_cmd_line *cmd_line)
{
	int			i;
	t_cmd_line	*tmp;

	tmp = cmd_line;
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
	t_redir		*tmp_redir;
	t_token		*token_list;
	t_token		*token_tmp;
	char		*str;
	int			ok;
	int			i;

	ok = 1;
	cmd_line = NULL;
	while (ok)
	{
		str = readline("minishell > ");
		if (ft_strlen(str))
		{
			add_history(str);
			if (!ft_strncmp(str, "exit", 5))
				ok = 0;
			else
			{
				token_list = tokenize_command_line(str);
				if (token_list && !check_token_syntax(token_list))
					free_token_list(token_list);
				else if (token_list)
				{
					cmd_line = treat_pipe_sequence(token_list);
					look_for_expandable_vars(cmd_line);
					tmp = cmd_line;
					while (tmp)
					{
						i = -1;
						while (++i < tmp->args.used_size)
							printf("---- |%s|\n", tmp->args.args[i]);
						tmp_redir = tmp->redir;
						while (tmp_redir)
						{
							printf("+++ %s\n", tmp_redir->file);
							printf("+++ %d\n", tmp_redir->type);
							tmp_redir = tmp_redir->next;
						}
						printf("~~~~~~~~~~~~~~~~~~~~~~\n");
						tmp = tmp->next;
					}
					free(str);
					free_cmd_line_list(cmd_line);
				}
			}
		}
	}
	return (0);
}