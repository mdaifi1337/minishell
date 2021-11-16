/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:33:30 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/16 09:01:29 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (arg->args[i][0] == '~' && arg->args[i][1] != '/'
		&& arg->args[i][3])
	{
		printf("minishell: %s: No such file or directory\n", arg->args[i]);
		g_var.stat = 127;
	}
}

void	init_global_struct(void)
{
	g_var.pid = 0;
	g_var.original_stdin = 0;
	g_var.stat = 0;
	g_var.heredoc = 0;
}

void	write_heredocs_in_stdin(char *str)
{
	int	p[2];

	pipe(p);
	write(p[1], str, ft_strlen(str));
	dup2(p[0], g_var.original_stdin);
	close(p[1]);
	close(p[0]);
}

void	look_for_backslash(char *arg, int *i)
{
	while (arg[*i])
	{
		if (arg[*i] == '/')
		{
			*i = -1;
			break ;
		}
		(*i)++;
	}
}
