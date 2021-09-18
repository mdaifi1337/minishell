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
			// printf("token : %s\n", token);
			lst_add_back_token(&token_list, type, token);
		}
	}
	lst_add_back_token(&token_list, e_end, "newline");
	return (token_list);
}

int	main(int argc, char *argv[], char *env[])
{
	t_cmd_line	*cmd_line;
	t_token		*tmp;
	t_token		*token_list;
	char		*str;
	int			true;
	int			i;

	true = 1;
	cmd_line = NULL;
	while (true)
	{
		str = readline("\033[1;36mminishell > \033[0m");
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
					// if (!cmds_list)
					// 	printf("cmds list is empty\n");
					// else
					// 	printf("cmds list is not empty\n");
					// printf("OK\n");
					// tmp = cmd_line;
					// while (tmp)
					// {
					// 	i = -1;
					// 	printf("tmp->args[0] : %s\n", tmp->args[0]);
					// 	while (tmp->args[++i])
					// 	{
					// 		printf("---- %s\n", tmp->args[i]);
					// 		// if (cmd_line->redirect.file)
					// 		// 	printf("+++ %s\n", cmd_line->redirect.file);
					// 		// sleep(1);
					// 	}
					// 	printf("~~~~~~~~~~~~~~~~~~~~~~\n");
					// 	tmp = tmp->next;
					// }
				}
				free(str);
			}
		}
	}
	return (0);
}