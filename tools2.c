/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:33:30 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/14 15:59:49 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_array(char **tab, int size)
{
	int		i;
	char	**args;

	args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL); //allocation error
	i = -1;
	while (++i < size)
		args[i] = tab[i];
	args[i] = NULL;
	return (args);
}

static void	search_for_home_var(t_vector *env, t_char_vec *char_vec)
{
	int	i;
	int	j;

	i = -1;
	while (++i < env->used_size)
	{
		if (!ft_strncmp(env->args[i], "HOME=", 5))
		{
			init_char_vec(char_vec);
			j = 4;
			while (env->args[i][++j])
				char_vec_add(char_vec, env->args[i][j]);
		}
	}
}

void	replace_path(t_vector *arg, t_vector *env, int i)
{
	int			j;
	int			k;
	t_char_vec	new;

	if (arg->args[i][0] == '~' && arg->args[i][1] == '/')
	{
		search_for_home_var(env, &new);
		char_vec_add(&new, '/');
		j = 1;
		while (arg->args[i][++j])
			char_vec_add(&new, arg->args[i][j]);
		free(arg->args[i]);
		arg->args[i] = ft_strdup(new.arg);
		free(new.arg);
	}
	else if (arg->args[i][0] == '~' && arg->args[i][1] != '/' && arg->args[i][3])
	{
		printf("minishell: %s: No such file or directory\n", arg->args[i]);
		g_var.stat = 127;
	}
}