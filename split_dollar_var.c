/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_dollar_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 13:17:09 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/15 10:46:28 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dollar_var_has_only_one_value(t_vector *v, t_char_vec *new,
	char *tmp, int curr_pos)
{
	if (tmp[curr_pos] != '\0')
	{
		while (tmp[curr_pos])
		{
			char_vec_add(new, tmp[curr_pos]);
			curr_pos++;
		}
	}
	free(v->args[v->i]);
	v->args[v->i] = ft_strdup(new->arg);
}

void	dollar_var_is_not_empty(t_vector *v, char **tab, int curr_pos)
{
	int			j;
	int			size;
	char		*tmp;
	t_char_vec	new_char_vec;

	tmp = ft_strdup(v->args[v->i]);
	init_char_vec(&new_char_vec);
	j = -1;
	while (tmp[++j] != '$')
		char_vec_add(&new_char_vec, tmp[j]);
	j = -1;
	while (tab[0][++j])
		char_vec_add(&new_char_vec, tab[0][j]);
	size = 0;
	while (tab[size])
		size++;
	if (size > 1)
		dollar_var_has_multiple_values(v, &new_char_vec, tab, curr_pos);
	else
		dollar_var_has_only_one_value(v, &new_char_vec, tmp, curr_pos);
	free(tmp);
	free(new_char_vec.arg);
}

void	split_dollar_var(t_vector *v, int curr_pos, char *value)
{
	char	**tab;

	tab = ft_split(value, ' ');
	if (tab[0])
		dollar_var_is_not_empty(v, tab, curr_pos);
	else
	{
		if (v->used_size == v->i + 1)
			ignore_dollar_var(v);
		else
			resize_vec_when_dollar_var_empty(v);
	}
	free_array(tab);
}
