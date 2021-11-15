/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:12:33 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/15 12:16:33 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_export_error(t_cmd_line *cmd, t_vector *path, int i)
{
	if (!ft_isdigit(cmd->args.args[i][0]))
		vector_add(path, cmd->args.args[i]);
	else
	{
		printf("%s: %s: not a valid identifier\n",
			cmd->args.args[0], cmd->args.args[i]);
		g_var.stat = 1;
	}
}

static void	ft_replace_path(t_vector *path, char *str, int k)
{
	char	*tmp;

	tmp = path->args[k];
	path->args[k] = ft_strjoin(path->args[k], str);
	free(tmp);
}

static void	ft_append_or_create_var(t_cmd_line *cmd, t_vector *path,
		int i, int j)
{
	char	*arg;
	char	*str;
	int		k;

	k = 0;
	arg = ft_substr(cmd->args.args[i], 0, j - 1);
	while (path->args[k])
	{
		if (!ft_strncmp(arg, path->args[k], ft_strlen(arg)))
		{
			str = ft_substr(cmd->args.args[i], j + 1,
					ft_strlen(cmd->args.args[i]) - j + 1);
			ft_replace_path(path, str, k);
			free(str);
		}
		k++;
	}
	if (j != ft_strlen(*path->args))
	{
		str = ft_substr(cmd->args.args[i], j + 1,
				ft_strlen(cmd->args.args[i]) - j + 1);
		ft_replace_path(path, str, k);
		free(str);
	}
	free(arg);
}

void	cmd_export(t_cmd_line *cmd, t_vector *path)
{
	int	i;
	int	j;

	i = 1;
	while (i < cmd->args.used_size)
	{
		j = 0;
		while (cmd->args.args[i][j])
		{
			if (cmd->args.args[i][j] == '=')
			{
				if (cmd->args.args[i][j - 1] == '+')
					ft_append_or_create_var(cmd, path, i, j);
				else if (cmd->args.args[i][j])
					ft_export_error(cmd, path, i);
				else
					vector_add(path, cmd->args.args[i]);
			}
			j++;
		}
		i++;
	}
}
