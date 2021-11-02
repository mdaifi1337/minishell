/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 18:33:17 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/01 08:25:50 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vector	copy_vector(t_vector v)
{
	t_vector	res;
	int			i;

	res.args = (char **)malloc(sizeof(char *) * v.size);
	if (!res.args)
		exit (1); //allocation error
	i = -1;
	while (++i < v.used_size)
		res.args[i] = ft_strdup(v.args[i]);
	res.used_size = v.used_size;
	res.size = v.size;
	return (res);
}

static void	add_chars_after_dollar_var_name(t_vector *v, t_char_vec *char_vec,
	int j)
{
	int	i;

	i = v->i;
	while (v->args[i][j])
	{
		if (v->args[i][j] == '\"' && v->args[i][j + 1] == '\0')
			j++;
		else
		{
			char_vec_add(char_vec, v->args[i][j]);
			j++;
		}
	}
}

t_char_vec	new_char_vec(t_vector *v)
{
	int			i;
	int			j;
	t_char_vec	res;

	init_char_vec(&res);
	i = v->i;
	j = -1;
	if (v->args[i][0] == '\"')
		j++;
	while (v->args[i][++j] && v->args[i][j] != '$')
		char_vec_add(&res, v->args[i][j]);
	j++;
	while ((ft_isalnum(v->args[i][j]) || v->args[i][j] == '_')
		&& v->args[i][j])
		j++;
	if (v->args[i][j] != '?')
		j++;
	j--;
	add_chars_after_dollar_var_name(v, &res, j);
	printf("char vec : %s\n", res.arg);
	return (res);
}
