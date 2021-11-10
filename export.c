/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:12:33 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/10 16:25:21 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_norme(t_cmd_line *cmd, t_vector *path, int i)
{
	if (!ft_isdigit(cmd->args.args[i][0]))
		vector_add(path, cmd->args.args[i]);
	else if (ft_isdigit(cmd->args.args[i][0]))
	{
		printf("%s: %s: not a valid identifier\n",
			cmd->args.args[0], cmd->args.args[i]);
		g_var.stat = 1;
	}
}

static void ft_append_or_create_var(t_cmd_line *cmd, t_vector *path, int i)
{
	char *arg;
	int j;

	j = 0;
	arg = ft_substr(cmd->args.args[1], 0, i - 1);
	while (path->args[j])
	{
		if (!ft_strcmp(arg, path->args[j]))
			path->args[j] = ft_strjoin_new_line(path->args[j],
			ft_substr(cmd->args.args[1], i + 1,
			ft_strlen(cmd->args.args[1]) - i + 1));
		j++;
	}
	if (j != ft_strlen(*path->args))
	{
		path->args[j] = ft_strjoin_new_line(arg,
		ft_substr(cmd->args.args[1], i + 1,
		ft_strlen(cmd->args.args[1]) - i + 1));
	}
}

void cmd_export(t_cmd_line *cmd, t_vector *path)
{
	int i;
	int j;

	i = 1;
	while (i < cmd->args.used_size)
	{
		j = 0;
		while (cmd->args.args[i][j])
		{
			if (cmd->args.args[i][j] == '=')
			{
				if (cmd->args.args[i][j - 1] == '+')
					ft_append_or_create_var(cmd, path, i);
				else if (cmd->args.args[i][j])
					ft_norme(cmd, path, i);
				else
					vector_add(path, cmd->args.args[i]);
			}
			j++;
		}
		i++;
	}
}
