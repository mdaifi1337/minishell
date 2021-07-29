#include "minishell.h"

t_token	*create_new_token(char *str, t_type type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->token = str;
	token->type = type;
	return (token);
}

t_type	special_characters(char *str, int i)
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
	int		quote;
	char	*res;
	int		j;
	int		count;

	j = *i;
	count = 0;
	quote = 0;
	*type = special_characters(str, *i);
	if (*type)
	{
		count = 1;
		if (*type == e_dless || *type == e_dgreat)
			count = 2;
	}
	else
	{
		while (str[j] && ((!ft_strchr(" |<>", str[j]) && !quote) || quote))
		{
			if ((str[j] == '\"' || str[j] == '\''))
				quote = 1 - quote;
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

t_list	*tokenize_command_line(char *str)
{
	t_type	type;
	t_token	*token_node;
	t_list	*token_list;
	t_list	*tmp;
	char	*token;
	int		i;

	i = 0;
	token_list = ft_lstnew(create_new_token(NULL, e_start));
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
		{
			token = get_token(str, &i, &type);
			token_node = create_new_token(token, type);
			// printf("token : |%s|\n", token);
			// printf("type : |%d|\n", (int)type);
			tmp = ft_lstnew(token_node);
			ft_lstadd_back(&token_list, tmp);
		}
	}
	tmp = ft_lstnew(create_new_token("newline", e_end));
	ft_lstadd_back(&token_list, tmp);
	return (token_list);
}

int	main(int argc, char *argv[], char *env[])
{
	t_command_line	*cmd_line;
	t_token	*token_node;
	t_list	*tmp;
	t_list	*cmds_list;
	t_list	*token_list;
	char	*prompt;
	char	*str;
	int		true;
	int		i;

	true = 1;
	while (true)
	{
		printf("\033[1;36mminishell > \033[0m");
		str = readline(NULL);
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
					// tmp = token_list->next;
					// while(tmp)
					// {
					// 	token_node = (t_token *)tmp->content;
					// 	tmp = tmp->next;
					// }
					cmds_list = treat_quotes(token_list);
					tmp = cmds_list;
					while (tmp)
					{
						cmd_line = (t_command_line *)tmp->content;
						i = -1;
						while (cmd_line->args[++i])
						{
							printf("---- %s\n", cmd_line->args[i]);
							// sleep(1);
						}
						printf("~~~~~~~~~~~~~~~~~~~~~~\n");
						tmp = tmp->next;
					}
				}
				free(str);
			}
		} 
	}
	return (0);
}