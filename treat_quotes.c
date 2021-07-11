#include "minishell.h"

static int	calc_nbr_of_words_in_quotes(char *str, int *size)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			quote = 1 - quote;
		if (str[i] == ' ')
			(*size)++;
	}
	if (*size == 1)
		(*size)++;
	else
		(*size)++;
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

	size = 0;
	if (str[*i] == ' ')
		(*i)++;
	j = *i;
	while (str[*i] && str[*i] != ' ')
	{
		if (str[(*i)] == '\'' || str[(*i)] == '\"')
			(*i)++;
		size++;
		(*i)++;
	}
	res = (char *)malloc(sizeof(char) * size + 1);
	k = 0;
	while (k < size)
	{
		if (str[(j)] == '\'' || str[(j)] == '\"')
			j++;
		res[k++] = str[j++];
	}
	res[k] = '\0';
	return (res);
}

t_list	*treat_quotes(t_list *token_list)
{
	t_list			*it_list;
	t_token			*token;
	// t_list			*tmp;
	t_command_line	*cmd_line;
	t_command_line	*tmp;
	char			**args;
	t_list 			*cmds_list;
	int				size;
	int				i;
	int				j;

	it_list = token_list->next;
	cmds_list = NULL;
	while (it_list->next)
	{
		cmd_line = (t_command_line *)malloc(sizeof(t_command_line));
		size = 1;
		token = (t_token *)it_list->content;
		printf("token->token : %s\n", token->token);
		calc_nbr_of_words_in_quotes(token->token, &size);
		i = 0;
		j = 0;
		printf("size : %d\n", size);
		cmd_line->args = (char **)malloc(sizeof(char *) * size);
		while (j < size - 1)
		{
			cmd_line->args[j] = allocate_word(token->token, &i);
			// printf("cmd_line->args[%d] : %s\n", j, cmd_line->args[j]);
			j++;
		}
		cmd_line->args[j] = NULL;

		
		ft_lstadd_back(&cmds_list, ft_lstnew(cmd_line));
		it_list = it_list->next;
		// free(tmp);
		//  free(cmd_line);
	}
	return (cmds_list);
}