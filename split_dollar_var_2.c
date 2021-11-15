/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_dollar_var_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 10:45:14 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/15 10:49:34 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_dollar_var_values_to_vec(char **tab, t_vector *v,
	t_char_vec *new_char_vec)
{
	int	i;
	int	j;

	i = 0;
	while (tab[++i])
	{
		vector_add_at_index(v, new_char_vec->arg);
		free(new_char_vec->arg);
		init_char_vec(new_char_vec);
		j = -1;
		while (tab[i][++j])
			char_vec_add(new_char_vec, tab[i][j]);
		v->i++;
	}
}

static void	apped_last_tab_value_to_char_vec(t_char_vec *char_vec,
	char**tab, int size)
{
	int	j;

	free(char_vec->arg);
	init_char_vec(char_vec);
	j = -1;
	while (tab[size - 1][++j])
		char_vec_add(char_vec, tab[size - 1][j]);
}

void	dollar_var_has_multiple_values(t_vector *v, t_char_vec *new,
	char **tab, int curr_pos)
{
	int		j;
	int		size;
	char	*tmp;

	tmp = ft_strdup(v->args[v->i]);
	size = 0;
	while (tab[size])
		size++;
	insert_dollar_vars_in_vector(v, size - 1);
	add_dollar_var_values_to_vec(tab, v, new);
	if (tmp[curr_pos] != '\0')
	{
		apped_last_tab_value_to_char_vec(new, tab, size);
		curr_pos--;
		while (tmp[++curr_pos])
			char_vec_add(new, tmp[curr_pos]);
		vector_add_at_index(v, new->arg);
	}
	else
	{
		free(v->args[v->i]);
		v->args[v->i] = ft_strdup(tab[size - 1]);
	}
	free(tmp);
}
