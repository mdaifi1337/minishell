/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:15:21 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/10 16:43:03 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_echo(t_cmd_line *cmd)
{
	int			i;

	i = 1;
	if (!cmd->args.args[1])
	{
		g_var.stat = 0;
		printf("\n");
	}
	else
	{
		while (i < cmd->args.used_size)
		{
			if (!ft_strcmp(cmd->args.args[i], "-n"))
				i++;
			if (!ft_strcmp(cmd->args.args[i], "$?"))
				printf("%d", g_var.stat);
			else
				printf("%s", cmd->args.args[i]);
			if (cmd->args.args[i + 1] != NULL)
				printf(" ");
			i++;
		}
	}
	if (cmd->args.args[1] && ft_strcmp(cmd->args.args[1], "-n"))
		printf("\n");
}

void	cmd_pwd(t_cmd_line *cmd_line)
{
	t_cmd_line	*tmp;
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

static void	exit_err(t_cmd_line *tmp)
{
	int	i;

	i = 0;
	while (tmp->args.args[1][i] != '\0')
	{
		if (!ft_isdigit(tmp->args.args[1][i]))
		{
			printf("%s: %s: numeric argument required\n", \
				tmp->args.args[0], tmp->args.args[1]);
			g_var.stat = 255;
			exit(g_var.stat);
		}
		i++;
	}
}

void	cmd_exit(t_cmd_line *cmd_line)
{
	t_cmd_line	*tmp;
	t_cmd_line	*tmp2;
	char		path[256];
	int			i;

	i = 1;
	tmp = cmd_line;
	tmp2 = cmd_line;
	while (tmp2->args.args[i] != NULL)
		i++;
	if (i > 2)
	{
		printf("%s: too many arguments", tmp->args.args[0]);
		exit(1);
	}
	if (tmp->args.args[1])
		exit_err(tmp);
	if (tmp->args.args[1])
		g_var.stat = ft_atoi(tmp->args.args[1]);
	exit(g_var.stat);
}

void	cmd_cd(t_cmd_line *cmd_line, t_vector *path)
{
	t_cmd_line	*tmp;
	char		*tmp2;
	int			i;

	i = 0;
	tmp = cmd_line;
	if (tmp->args.args[1] != NULL)
	{
		if (!chdir(tmp->args.args[1]))
		{
			g_var.stat = 0;
			return ;
		}
		else
		{
			printf("%s: %s: No such file or directory\n", \
				tmp->args.args[0], tmp->args.args[1]);
			g_var.stat = 1;
			return ;
		}
	}
	else
		cd_home(path);
}
