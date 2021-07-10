#include "minishell.h"

static int	calc_nbr_of_words_in_quotes(char *str, int *size)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	printf("hi %s\n", str);
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			quote = 1 - quote;
		if (str[i] == ' ')
			(*size)++;
	}
	if (quote)
		write(2, "Error, unclosed quotes!\n", 25);
	else
		return (1);
	return (0);
}

char	*allocate_word(char *str, int *i)
{
	char	*res;
	int		size;
	int		j;
	int		k;

	j = *i;
	size = 0;
	if (str[*i] == ' ')
		(*i)++;
	while (str[++(*i)] && str[(*i)] != ' ')
	{
		if (str[(*i)] == '\'' || str[(*i)] == '\"')
			(*i)++;
		size++;
	}
	res = (char *)malloc(sizeof(char) * size + 1);
	while (k < size)
		res[k++] = str[j++];
	res[k] = '\0';
	return (res);
}

void	treat_quotes(t_list **cmds_list, t_list *token_list)
{
	t_list			*it_list;
	t_token			*token;
	t_command_line	*cmd_line;
	int				size;
	int				i;
	int				j;

	size = 1;
	it_list = token_list->next;
	while (it_list)
	{
		token = (t_token *)it_list->content;
		printf("OK 2\n");
		printf("token->token : %s\n", token->token);
		if (!calc_nbr_of_words_in_quotes(token->token, &size))
			return ;
		else
		{
			printf("OK\n");
			i = 0;
			j = 0;
			cmd_line->args = (char **)malloc(sizeof(char *) * size + 1);
			while (j < size)
			{
				cmd_line->args[j] = allocate_word(token->token, &i);
				j++;
			}
			cmd_line->args[j] = NULL;
			ft_lstadd_back(cmds_list, ft_lstnew(cmd_line));
		}
		it_list = it_list->next;
	}
}