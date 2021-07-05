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
	if (!ft_strncmp(str + i, "< ", 2))
		return (e_less);
	if (!ft_strncmp(str + i, "<< ", 3))
		return (e_dless);
	if (!ft_strncmp(str + i, "> ", 2))
		return (e_great);
	if (!ft_strncmp(str + i, ">> ", 3))
		return (e_dgreat);
	if (!ft_strncmp(str + i, "| ", 2))
		return (e_pipe);
	return (0);
}

char	*get_token(char *str, int *i, t_type *type)
{
	char	*res;
	int		j;
	int		count;

	j = *i;
	count = 0;
	*type = special_characters(str, *i);
	if (*type)
	{
		printf("---------------------------type\n");
		count = 1;
		if (*type == e_dless || *type == e_dgreat)
			count = 2;
	}
	else
	{
		while (str[j] && !ft_strchr(" |<>", str[j]))
		{
			j++;
			count++;
		}
		*type = e_word;
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

void	tokenize_command_line(char *str)
{
	t_type	type;
	t_token	*token_node;
	t_list	*tmp;
	t_list	*token_list;
	t_list	*it_list;
	char	*token;
	int		i;

	i = 0;
	token_list = ft_lstnew("start");
	printf("%s\n", str);
	while (str[i])
	{
		if (str[i] == ' '){
			i++;
			continue;
		}
		else
		{
			token = get_token(str, &i, &type);
			token_node = create_new_token(token, type);
			printf("token : |%s|\n", token_node->token);
			tmp = ft_lstnew(token_node);
			ft_lstadd_back(&token_list, tmp);
		}
		if (str[i + 1] == '\0') {
			break;
		}
		i++;
		printf("%d\n", i);
		printf("%c\n", str[i]);
	}
	/* it_list = token_list;
	while (it_list)
	{
		token_node = (t_token *)it_list->content;
		printf("OK\n");
		it_list = it_list->next;
	} */
}

int	main(int argc, char *argv[])
{
	tokenize_command_line(argv[1]);
	return (0);
}