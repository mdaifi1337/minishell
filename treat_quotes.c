/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:57:05 by mdaifi            #+#    #+#             */
/*   Updated: 2021/10/30 18:41:14 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_quotes(char *str, int *j, int *dquote, int *squote)
{
	while (str[*j] == '\'' && !(*dquote))
	{
		*squote = 1 - *squote;
		(*j)++;
	}
	while (str[*j] == '\"' && !(*squote))
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
		while (++j < ft_strlen(v->args[i]))
		{
			skip_quotes(v->args[i], &j, &dquote, &squote);
			char_vec_add(&new_char_vec, v->args[i][j]);
		}
		free(v->args[i]);
		v->args[i] = ft_strdup(new_char_vec.arg);
		free(new_char_vec.arg);
	}
}
