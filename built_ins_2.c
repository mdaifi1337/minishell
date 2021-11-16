/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:15:21 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/16 09:32:43 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_with_args(t_cmd_line *cmd)
{
	int	i;

	i = 1;
	while (i < cmd->args.used_size)
	{
		if (!ft_strcmp(cmd->args.args[i], "-n"))
			i++;
		if (!ft_strcmp(cmd->args.args[i], "$?"))
			printf("%d", g_var.stat);
		else
			printf("%s", cmd->args.args[i]);
		if (i + 1 < cmd->args.used_size)
			printf(" ");
		i++;
	}
	g_var.stat = 0;
}

void	cmd_echo(t_cmd_line *cmd)
{
	if (!cmd->args.args[1])
	{
		g_var.stat = 0;
		printf("\n");
	}
	else
		echo_with_args(cmd);
	if (cmd->args.args[1] && ft_strcmp(cmd->args.args[1], "-n"))
		printf("\n");
}

void	cmd_pwd(t_cmd_line *cmd_line)
{
	char		path[256];

	if (getcwd(path, sizeof(path)) == NULL)
	{
		g_var.stat = 1;
		perror("");
	}
	else
		printf("%s\n", path);
	g_var.stat = 0;
}

static void	exit_err(t_cmd_line *cmd)
{
	int	i;

	i = 0;
	while (cmd->args.args[1][i] != '\0')
	{
		if (!ft_isdigit(cmd->args.args[1][i]))
		{
			printf("minishell: %s: %s: numeric argument required\n", \
				cmd->args.args[0], cmd->args.args[1]);
			g_var.stat = 255;
			exit(g_var.stat);
		}
		i++;
	}
}

void	cmd_exit(t_cmd_line *cmd_line)
{
	if (g_var.size == 1)
		printf("exit\n");
	if (cmd_line->args.args[1])
		exit_err(cmd_line);
	if (cmd_line->args.args[1])
		g_var.stat = ft_atoi(cmd_line->args.args[1]);
	exit(g_var.stat);
}
