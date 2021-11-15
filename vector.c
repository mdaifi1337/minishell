/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:18:01 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/15 10:30:44 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	vector_init(t_vector *v)
{
	v->size = 1;
	v->used_size = 0;
	v->args = (char **)malloc(sizeof(char *) * v->size);
	v->args[0] = NULL;
}

void	vector_resize(t_vector *v, int size)
{
	int		i;
	char	**tmp;

	tmp = (char **)malloc(sizeof(char *) * v->used_size + 1);
	i = -1;
	while (++i < v->used_size)
		tmp[i] = ft_strdup(v->args[i]);
	tmp[i] = NULL;
	free_array_of_strings(v->args, v->size);
	v->args = (char **)malloc(sizeof(char *) * size);
	i = -1;
	while (++i < v->used_size)
		v->args[i] = ft_strdup(tmp[i]);
	while (i < size)
	{
		v->args[i] = NULL;
		i++;
	}
	v->size = size;
	free_array(tmp);
}

void	vector_add(t_vector *v, char *item)
{
	if (v->size - 1 == v->used_size)
		vector_resize(v, v->size * 2);
	v->args[v->used_size++] = ft_strdup(item);
}

void	vector_add_at_index(t_vector *v, char *item)
{
	free(v->args[v->i]);
	v->args[v->i] = ft_strdup(item);
	if (v->used_size + 1 <= v->size)
		v->used_size++;
}

void	vector_delete(t_vector *v, int index)
{
	int	i;

	if (index < 0 || index >= v->used_size)
		return ;
	free(v->args[index]);
	i = index;
	while (i < v->used_size - 1)
	{
		v->args[i] = ft_strdup(v->args[i + 1]);
		free(v->args[i + 1]);
		i++;
	}
	v->used_size--;
	if (v->used_size > 0 && v->used_size == v->size / 4)
		vector_resize(v, v->size / 2);
}
