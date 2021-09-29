/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:02:58 by mdaifi            #+#    #+#             */
/*   Updated: 2021/09/29 15:34:47 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_char_vec(t_char_vec *char_vec)
{
	char_vec->size = 2;
	char_vec->used_size = 0;
	char_vec->arg = (char *)malloc(sizeof(char) * char_vec->size);
	char_vec->arg[0] = '\0';
}

static char	*ft_realloc(t_char_vec *char_vec, int size)
{
	char	*new;
	char	*tmp;
	int		i;
	int		length;

	length = 0;
	while (length < char_vec->used_size)
		length++;
	tmp = (char *)malloc(sizeof(char) * length + 1);
	i = -1;
	while (++i < char_vec->used_size)
		tmp[i] = char_vec->arg[i];
	tmp[i] = '\0';
	new = (char *)malloc(sizeof(char) * size + 1);
	i = -1;
	while (++i < char_vec->used_size)
		new[i] = char_vec->arg[i];
	while (i < char_vec->size)
	{
		new[i] = '\0';
		i++;
	}
	return (new);
}

static void	char_vec_resize(t_char_vec *char_vec, int size)
{
    char	*item;

	item = ft_realloc(char_vec, size);
    if (item)
	{
        char_vec->arg = item;
        char_vec->size = size;
    }
}

void	char_vec_add(t_char_vec *char_vec, char c)
{
	if (char_vec->size == char_vec->used_size)
    	char_vec_resize(char_vec, (char_vec->size * 2) + 1);
    char_vec->arg[char_vec->used_size++] = c;
    char_vec->arg[char_vec->used_size] = '\0';
}
