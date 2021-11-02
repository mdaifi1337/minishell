/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 13:15:06 by mdaifi            #+#    #+#             */
/*   Updated: 2021/10/30 18:21:27 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	found_dollar_sign(t_vector *v, int j, int squote, int dquote)
{
	char		*value;
	t_char_vec	name;

	value = NULL;
	init_char_vec(&name);
	while (v->args[v->i][++j] && (ft_isalnum(v->args[v->i][j])
		|| v->args[v->i][j] == '_') && v->args[v->i][j] != '?')
		char_vec_add(&name, v->args[v->i][j]);
	value = getenv(name.arg);
	if (!squote && !dquote && value)
		split_dollar_var(v, j, value);
	else if (!squote && dquote && value)
		replace_dollar_var(v, name.arg, value);
	else if (!squote && !value)
		dollar_var_not_found(v);
	free(name.arg);
}

static void	expand_dollar_var(t_vector *v)
{
	int			dquote;
	int			squote;
	int			j;

	j = -1;
	dquote = 0;
	squote = 0;
	while (v->args[v->i][++j])
	{
		if (v->args[v->i][j] == '\"' && !squote)
			dquote = 1 - dquote;
		if (v->args[v->i][j] == '\'' && !dquote)
			squote = 1 - squote;
		if (v->args[v->i][j] == '$')
			found_dollar_sign(v, j, squote, dquote);
	}
}

void	look_for_expandable_vars(t_cmd_line *cmd_line)
{
	int			i;
	t_cmd_line	*tmp;

	tmp = cmd_line;
	while (tmp)
	{
		tmp->args.i = -1;
		while (++tmp->args.i < tmp->args.used_size)
			expand_dollar_var(&tmp->args);
		remove_quotes(&tmp->args);
		tmp = tmp->next;
	}
}
