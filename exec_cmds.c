/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 14:38:19 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/16 09:27:07 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_child_process(t_cmd_line *cmd, t_vector *path, int *p)
{
	signal(SIGINT, child_sig);
	signal(SIGQUIT, child_sig);
	if (cmd->redir)
		exec_redir(cmd->redir, path);
	if (dup2(g_var.original_stdin, 0) < 0)
		perror("");
	if (cmd->next != NULL)
	{
		close(p[0]);
		if (dup2(p[1], 1) < 0)
			perror("");
	}
	exe_first_cmd(cmd, path);
	exit(g_var.stat);
}

static void	last_node_exit_status(int ret, int *p)
{
	close(p[0]);
	if (g_var.original_stdin)
		close(g_var.original_stdin);
	g_var.original_stdin = 0;
	if (ret == g_var.pid && WIFEXITED(g_var.stat))
		g_var.stat = WEXITSTATUS(g_var.stat);
	else if (ret == g_var.pid && WIFSIGNALED(g_var.stat))
	{
		if (g_var.heredoc != 1)
			g_var.stat = 128 + WTERMSIG(g_var.stat);
		else
		{
			g_var.stat = 1;
			g_var.heredoc = 0;
		}
		if (WTERMSIG(g_var.stat) == SIGQUIT)
			write(1, "Quit: 3\n", 9);
		if (WTERMSIG(g_var.stat) == SIGINT)
			write(1, "\n", 1);
	}
}

static void	execute_next_cmd(t_cmd_line *cmd_line, t_vector *path,
	int *p, int ret)
{
	if (ret == g_var.pid && WIFEXITED(g_var.stat))
	{
		g_var.stat = WEXITSTATUS(g_var.stat);
		if (g_var.stat == 1)
			g_var.reset = 1;
	}
	if (g_var.original_stdin)
		close(g_var.original_stdin);
	g_var.original_stdin = p[0];
	cmd_line = cmd_line->next;
	execute_second_cmd(cmd_line, path);
}

void	execute_second_cmd(t_cmd_line *cmd_line, t_vector *path)
{
	int		p[2];
	int		ret;
	pid_t	pid;

	if (!g_var.reset)
	{
		fd_error(pipe(p));
		g_var.pid = fork();
		if (g_var.pid == 0)
			ft_child_process(cmd_line, path, p);
		else
		{
			signal(SIGINT, SIG_IGN);
			close(p[1]);
			ret = wait(&g_var.stat);
			if (cmd_line->next == NULL)
				last_node_exit_status(ret, p);
			else
				execute_next_cmd(cmd_line, path, p, ret);
			signal(SIGINT, parent_sig);
		}
	}
}
