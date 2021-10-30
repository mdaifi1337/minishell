/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:57:05 by mdaifi            #+#    #+#             */
/*   Updated: 2021/10/27 15:04:07 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	skip_quotes(char c, int *j, int *dquote, int *squote)
{

	if (c == '\'' && !(*dquote))
	{
		*squote = 1 - *squote;
		(*j)++;
	}
	if (c == '\"' && !(*squote))
	{
		*dquote = 1 - *dquote;
		(*j)++;
	}
}
void	remove_quotes(t_vector *v)
{
	int			i;
	int			j;
	int			squote;
	int			dquote;
	t_char_vec	new_char_vec;

	i = -1;
	squote = 0;
	dquote = 0;
	while (++i < v->used_size)
	{
		init_char_vec(&new_char_vec);
		j = -1;
		while (v->args[i][++j])
		{
			skip_quotes(v->args[i][j], &j, &dquote, &squote);
			char_vec_add(&new_char_vec, v->args[i][j]);
		}
		free(v->args[i]);
		v->args[i] = ft_strdup(new_char_vec.arg);
		free(new_char_vec.arg);
	}
}
