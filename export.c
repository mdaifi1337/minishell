/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:12:33 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/06 11:21:53 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_norme(t_cmd_line *tmp, t_vector *path, int status)
{
	if (!ft_isdigit(tmp->args.args[2][0]))
		vector_add(path, tmp->args.args[1]);
	else if (ft_isdigit(tmp->args.args[2][0]))
	{
		printf("%s: %s: not a valid identifier\n",
			   tmp->args.args[0], tmp->args.args[2]);
		status = 1;
	}
}

static void ft_append_or_create_var(t_cmd_line *tmp, t_vector *path, int i)
{
	char *arg;
	int j;

	j = 0;
	arg = ft_substr(tmp->args.args[1], 0, i - 1);
	while (path->args[j])
	{
		if (!ft_strncmp(arg, path->args[j], ft_strlen(arg)))
			path->args[j] = ft_strjoin_new_line(path->args[j],
			ft_substr(tmp->args.args[1], i + 1,
			ft_strlen(tmp->args.args[1]) - i + 1));
		j++;
	}
	if (j != ft_strlen(*path->args))
	{
		path->args[j] = ft_strjoin_new_line(arg,
		ft_substr(tmp->args.args[1], i + 1,
		ft_strlen(tmp->args.args[1]) - i + 1));
	}
}

void cmd_export(t_cmd_line *cmd_line, t_vector *path, int status)
{
	t_cmd_line *tmp;
	int i;

	i = 0;
	tmp = cmd_line;
	while (tmp->args.args[1][i])
	{
		if (tmp->args.args[1][i] == '=')
		{
			if (tmp->args.args[1][i - 1] == '+')
				ft_append_or_create_var(tmp, path, i);
			else if (tmp->args.args[2])
				ft_norme(tmp, path, status);
			else
				vector_add(path, tmp->args.args[1]);
		}
		i++;
	}
	status = 0;
}
