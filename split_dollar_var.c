// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   split_dollar_var.c                                 :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/10/30 13:17:09 by mdaifi            #+#    #+#             */
// /*   Updated: 2021/10/30 14:05:49 by mdaifi           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// // static void	add_dollar_var_values_to_vec(char **tab, t_vector *v, t_char_vec *new_char_vec)
// // {
// // 	int	j;
// // 	int	size;

// // 	j = 0;
	
// // }

// void	split_dollar_var(t_vector *v, int curr_pos, char *value)
// {
// 	char	*tmp;
// 	char	**tab;
// 	int		size;
// 	int		j;
// 	t_char_vec	new_char_vec;

// 	printf("split\n");
// 	tmp = ft_strdup(v->args[v->i]);
// 	init_char_vec(&new_char_vec);
// 	tab = ft_split(value, ' ');
// 	size = 0;
// 	while (tab[size])
// 		size++;
// 	if (tab[0])
// 	{
// 		j = -1;
// 		while (tmp[++j] != '$')
// 			char_vec_add(&new_char_vec, tmp[j]);
// 		if (tmp[curr_pos] != ' ')
// 		{
// 			j = -1;
// 			while (tab[0][++j])
// 				char_vec_add(&new_char_vec, tab[0][j]);
// 		}
// 		j = 0;
// 		if (size > 1)
// 		{
// 			insert_dollar_vars_in_vector(v, size - 1);
// 			while (tab[++j])
// 			{
// 				vector_add_at_index(v, new_char_vec.arg);
// 				free(new_char_vec.arg);
// 				init_char_vec(&new_char_vec);
// 				size = -1;
// 				while (tab[j][++size])
// 					char_vec_add(&new_char_vec, tab[j][size]);
// 				i++;
// 			}
// 			if (tmp[curr_pos] != '\0')
// 			{
// 				free(new_char_vec.arg);
// 				init_char_vec(&new_char_vec);
// 				size = -1;
// 				while (tab[j - 1][++size])
// 					char_vec_add(&new_char_vec, tab[j - 1][size]);
// 				while (tmp[curr_pos])
// 				{
// 					char_vec_add(&new_char_vec, tmp[curr_pos]);
// 					curr_pos++;
// 				}
// 				vector_add_at_index(v, new_char_vec.arg);
// 			}
// 			else
// 				v->args[v->i] = ft_strdup(tab[j - 1]);
// 		}
// 		else
// 		{
// 			if (tmp[curr_pos] != '\0')
// 			{
// 				while (tmp[curr_pos])
// 				{
// 					char_vec_add(&new_char_vec, tmp[curr_pos]);
// 					curr_pos++;
// 				}
// 			}
// 			free(v->args[v->i]);
// 			v->args[v->i] = ft_strdup(new_char_vec.arg);
// 		}
// 	}
// 	else
// 	{
// 		if (v->args[v->i + 1] == NULL || v->used_size == v->i + 1)
// 			ignore_dollar_var(v);
// 		else
		
// 			resize_vec_when_dollar_var_empty(v);
// 	}
// 	free(tmp);
// 	free(new_char_vec.arg);
// 	free_array(tab);
// }
