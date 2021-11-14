/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:09:59 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/14 12:20:03 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_pipe(t_cmd_line *cmd, t_vector *path)
{
	char			**tmp2;
	int				p[2];

	fd_error(pipe(p));
	execute_second_cmd(cmd, path);
}

void	check_cmd(t_cmd_line *cmd, t_vector *path)
{
	int	ret;

	g_var.size = ft_lst_size(cmd);
	if ((check_built_ins(cmd) && g_var.size == 1 && !cmd->redir)
		&& cmd->args.args[0][0] != '.')
		built_ins(cmd, path);
	else
		ft_pipe(cmd, path);
}

int	check_built_ins(t_cmd_line *cmd)
{
	if (!ft_strcmp(cmd->args.args[0], "echo"))
		return (1);
	if (!ft_strcmp(cmd->args.args[0], "pwd"))
		return (1);
	else if (!ft_strcmp(cmd->args.args[0], "cd"))
		return (1);
	else if (!ft_strcmp(cmd->args.args[0], "env"))
		return (1);
	else if (!ft_strcmp(cmd->args.args[0], "export"))
		return (1);
	else if (!ft_strcmp(cmd->args.args[0], "."))
		return (1);
	else if (!ft_strcmp(cmd->args.args[0], "unset"))
		return (1);
	else if (!ft_strcmp(cmd->args.args[0], "exit"))
		return (1);
	return (0);
}