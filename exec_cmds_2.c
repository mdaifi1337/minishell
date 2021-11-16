/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:04:27 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/16 09:27:09 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(char **env, t_cmd_line *cmd)
{
	if (execve(cmd->args.args[0], cmd->args.args, env) < 0)
	{
		write(1, "minishell: ", 12);
		ft_putstr_fd(cmd->args.args[0], 1);
		write(1, ": ", 3);
		perror("");
		free_array_of_strings(cmd->args.args, cmd->args.used_size);
		waitpid(g_var.pid, &g_var.stat, 0);
		if (WIFEXITED(g_var.stat))
			g_var.stat = WEXITSTATUS(g_var.stat);
		exit(g_var.stat);
	}
}

void	exe_first_cmd(t_cmd_line *cmd, t_vector *path)
{
	int		i;
	char	*cmd_path;

	if ((check_built_ins(cmd) && (g_var.size != 1 || cmd->redir))
		|| cmd->args.args[0][0] == '.')
		built_ins(cmd, path);
	else
	{
		i = 0;
		cmd_path = search_for_path_in_env(path->args);
		path_not_found(cmd_path);
		look_for_backslash(cmd->args.args[0], &i);
		if (i != -1)
			cmd->args.args[0] = search_path_of_cmd(cmd->args.args[0], cmd_path);
		if (cmd->args.args[0][0] == '/')
			execute_cmd(path->args, cmd);
		else
			printf("minishell: %s: No such file or directory\n", \
				cmd->args.args[0]);
	}
}
