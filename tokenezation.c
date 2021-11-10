/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenezation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 18:20:53 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/10 16:44:55 by mdaifi           ###   ########.fr       */
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

char	*get_token(char *str, int *i, t_type *type)
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

void	print_cmd_lines(t_cmd_line *cmd_line)
{
	int			i;
	t_cmd_line	*tmp;
	t_redir		*tmp_redir;

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
}

void	init_gloval_struct(void)
{
	g_var.pid = 0;
	g_var.original_stdin = 0;
	g_var.stat = 0;
}

int	main(int argc, char *argv[], char *env[])
{
	t_cmd_line	*cmd_line;
	t_token		*token_list;
	t_vector	*path;
	char		*str;
	int			true;

	true = 1;
	cmd_line = NULL;
	init_gloval_struct();
	path = env_copy(env);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, parent_sig);
	while (true)
	{
		str = readline("minishell > ");
		if (!str)
			exit(1);
		else if (ft_strlen(str))
		{
			add_history(str);
			if (!ft_strncmp(str, "exit", 5))
				true = 0;
			else
			{
				token_list = tokenize_command_line(str);
				if (token_list && !check_token_syntax(token_list))
					free_token_list(token_list);
				else if (token_list)
				{
					cmd_line = treat_pipe_sequence(token_list);
					look_for_expandable_vars(cmd_line);
					check_cmd(cmd_line, path);
					// print_cmd_lines(cmd_line);
					free(str);
					free_cmd_line_list(cmd_line);
				}
			}
		}
	}
	return (0);
}
