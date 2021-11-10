/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_var_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:13:56 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/10 16:41:53 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_dollar_vars_in_vector(t_vector *v, int size)
{
	int	i;
	int	j;
	int	curr_pos;

	curr_pos = v->i;
	if (v->used_size + size > v->size)
		vector_resize(v, v->used_size + size);
	if (size > 1)
	{
		i = (v->used_size + size) - 1;
		j = v->used_size - 1;
		while (j > curr_pos && v->args[j])
		{
			v->args[i] = ft_strdup(v->args[j]);
			free(v->args[j]);
			v->args[j] = NULL;
			j--;
			i--;
		}
	}
}

void	ignore_dollar_var(t_vector *v)
{
	int			i;
	int			j;
	t_char_vec	res;

	i = v->i;
	res = new_char_vec(v);
	if (res.arg[0] != '\0')
	{
		free(v->args[i]);
		v->args[i] = ft_strdup(res.arg);
	}
	else
		v->used_size--;
}

void	resize_vec_when_dollar_var_empty(t_vector *v)
{
	int			i;
	int			j;
	t_char_vec	res;

	i = v->i;
	res = new_char_vec(v);
	if (res.arg[0] != '\0')
	{
		free(v->args[i]);
		v->args[i++] = ft_strdup(res.arg);
	}
	else
	{
		while (i < v->used_size - 1)
		{
			free(v->args[i]);
			v->args[i] = ft_strdup(v->args[i + 1]);
			i++;
		}
		free(v->args[v->used_size - 1]);
		v->args[v->used_size - 1] = NULL;
		v->used_size--;
	}
}

void	dollar_var_not_found(t_vector *v)
{
	int			i;
	int			j;
	t_char_vec	res;

	i = v->i;
	res = new_char_vec(v);
	if (res.arg[0] != '\0' || (res.arg[0] == '\"' && ft_strlen(res.arg) > 1))
	{
		free(v->args[i]);
		v->args[i] = ft_strdup(res.arg);
	}
	else
	{
		while (i < v->used_size - 1)
		{
			free(v->args[i]);
			v->args[i] = ft_strdup(v->args[i + 1]);
			i++;
		}
		v->used_size--;
	}
}

void	replace_dollar_var(t_vector *v, char *name, char *value)
{
	int			i;
	int			j;
	char		*tmp;
	t_char_vec	new_char_vec;

	tmp = ft_strdup(v->args[v->i]);
	init_char_vec(&new_char_vec);
	i = -1;
	while (tmp[++i] != '$')
		char_vec_add(&new_char_vec, tmp[i]);
	j = -1;
	while (value[++j])
		char_vec_add(&new_char_vec, value[j]);
	j = -1;
	while (name[++j])
		i++;
	while (tmp[++i])
		char_vec_add(&new_char_vec, tmp[i]);
	free(v->args[v->i]);
	v->args[v->i] = ft_strdup(new_char_vec.arg);
	free(tmp);
}
