/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_cmd_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:00:50 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/15 11:08:42 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_nbr_of_chars(char *str, int *i)
{
	int		j;
	int		count;
	int		double_quote;
	int		single_quote;

	j = *i;
	count = 0;
	double_quote = 0;
	single_quote = 0;
	while (str[j] && (!ft_strchr(" |<>", str[j])
			|| (double_quote || single_quote)))
	{
		if (str[j] == '\"')
			double_quote = 1 - double_quote;
		if (str[j] == '\'')
			single_quote = 1 - single_quote;
		j++;
		count++;
	}
	return (count);
}

static char	*get_token(char *str, int *i, t_type *type)
{
	int		j;
	char	*res;
	int		count;

	count = 0;
	*type = redirections(str, *i);
	if (*type)
	{
		count = 1;
		if (*type == e_dless || *type == e_dgreat)
			count = 2;
	}
	else
		count = count_nbr_of_chars(str, i);
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

static int	unclosed_quotes(t_token *token_list, char **token)
{
	if (!check_nbr_of_quotes(*token))
	{
		free(*token);
		free_token_list(token_list);
		return (1);
	}
	return (0);
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
			if (unclosed_quotes(token_list, &token))
				return (NULL);
			lst_add_back_token(&token_list, type, token);
			free(token);
		}
	}
	lst_add_back_token(&token_list, e_end, "newline");
	return (token_list);
}
