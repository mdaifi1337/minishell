// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   expand_dollar_var.c                                :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/10/30 13:15:06 by mdaifi            #+#    #+#             */
// /*   Updated: 2021/10/30 13:48:51 by mdaifi           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// static void	expand_dollar_var(t_vector *v, int i)
// {
// 	int			dquote;
// 	int			squote;
// 	char		*value;
// 	int			j;
// 	t_char_vec	name;

// 	name.arg = NULL;
// 	value = NULL;
// 	j = -1;
// 	dquote = 0;
// 	squote = 0;
// 	printf("arg : %s\n", v->args[i]);
// 	printf("arg[i, j] : %c\n", v->args[i][++j]);
// 	while (v->args[v->i][++j])
// 	{
// 			debug;
// 		if (v->args[v->i][j] == '\"')
// 			dquote = 1 - dquote;
// 		if (v->args[v->i][j] == '\'')
// 			squote = 1 - squote;
// 		if (v->args[v->i][j] == '$')
// 		{
// 			init_char_vec(&name);
// 			while (v->args[v->i][++j] && (ft_isalnum(v->args[v->i][j]) || v->args[v->i][j] == '_') && v->args[v->i][j] != '?')
// 				char_vec_add(&name, v->args[v->i][j]);
// 			value = getenv(name.arg);
// 			if (!squote && !dquote && value)
// 				split_dollar_var(v, j,value);
// 			else if (!squote && dquote && value)
// 				replace_dollar_var(v, name.arg, value);
// 			else if (!value)
// 				dollar_var_not_found(v);
// 			free(name.arg);
// 		}
// 	}
// }

// void	look_for_expandable_vars(t_cmd_line *cmd_line)
// {
// 	int	i;
// 	t_cmd_line	*tmp;

// 	tmp = cmd_line;
// 	while (tmp)
// 	{
// 		i = -1;
// 			printf("arg ==== %s\n", tmp->args.args[0]);
// 		while (++i < tmp->args.used_size)
// 		{
// 			expand_dollar_var(&tmp->args, i);
// 		}
// 		remove_quotes(&tmp->args);
// 		tmp = tmp->next;
// 	}
// }
