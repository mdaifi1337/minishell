/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:29:21 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/13 12:45:23 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_ins(t_cmd_line *cmd_line, t_vector *path)
{
	if (!ft_strcmp(cmd_line->args.args[0], "echo"))
		cmd_echo(cmd_line);
	if (!ft_strcmp(cmd_line->args.args[0], "pwd"))
		cmd_pwd(cmd_line);
	else if (!ft_strcmp(cmd_line->args.args[0], "cd"))
		cmd_cd(cmd_line, path);
	else if (!ft_strcmp(cmd_line->args.args[0], "env"))
		cmd_env(cmd_line, path);
	else if (!ft_strcmp(cmd_line->args.args[0], "export"))
		cmd_export(cmd_line, path);
	else if (cmd_line->args.args[0][0] == '.')
		execute_cmd(path->args, cmd_line);
	else if (!ft_strcmp(cmd_line->args.args[0], "unset"))
		cmd_unset(cmd_line, path);
	else if (!ft_strcmp(cmd_line->args.args[0], "exit"))
		cmd_exit(cmd_line);
}

static void	env_err(t_cmd_line *cmd_line)
{
	if (!ft_strcmp(cmd_line->args.args[1], "."))
	{
		printf("%s: .: Permission denied\n", cmd_line->args.args[0]);
		exit(126);
	}
	// else if (!ft_strncmp(cmd_line->args[ft_strlen(cmd_line->args[1])],"/", 1))
	// {
	//     printf("hello\n");
	//     printf("%s: .: Permission denied\n", cmd_line->args[0]);
	//     exit(126);
	// }
	else
	{
		printf("%s: %s: No such file or directory\n", \
			cmd_line->args.args[0], cmd_line->args.args[1]);
		exit(127);
	}
}

void	cmd_env(t_cmd_line *cmd_line, t_vector *path)
{
	int	i;

	i = 0;
	while (i < path->used_size)
	{
		if (cmd_line->args.args[1])
		{
			if (!ft_strcmp(cmd_line->args.args[1], "env"))
				g_var.stat = 0;
			else
				env_err(cmd_line);
		}
		printf("%s\n", path->args[i]);
		i++;
	}
}

void	cmd_unset(t_cmd_line *cmd, t_vector *path)
{
	int			i;

	i = 0;
	while (i < path->used_size)
	{
		if (cmd->args.used_size == 1 || !ft_strncmp(cmd->args.args[1],
				path->args[i], ft_strlen(cmd->args.args[1])))
			break ;
		i++;
	}
	if (cmd->args.used_size > 1)
		vector_delete(path, i);
	g_var.stat = 0;
}
