/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 14:38:19 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/10 17:22:04 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(char **env, t_cmd_line *cmd)
{
	char	**args;

	args = copy_array(cmd->args.args, cmd->args.used_size);
	if (execve(args[0], args, env) < 0)
	{
		free_array_of_strings(args, cmd->args.used_size + 1);
		write(1, "minishell: ", 12);
		ft_putstr_fd(args[0], 1);
		write(1, ": ", 3);
		perror("");
		waitpid(g_var.pid, &g_var.stat, 0);
		if (WIFEXITED(g_var.stat))
			g_var.stat = WEXITSTATUS(g_var.stat);
		exit(g_var.stat);
	}
}

static void	exe_first_cmd(t_cmd_line *cmd, t_vector *path, int size)
{
	char *cmd_path;
	int i;

	if ((check_built_ins(cmd) && size != 1) || cmd->args.args[0][0] == '.')
		built_ins(cmd, path);
	else
	{
		i = 0;
		cmd_path = search_for_path_in_env(path->args);
		path_not_found(cmd_path);
		while (cmd->args.args[0][i])
		{
			if (cmd->args.args[0][i] == '/')
			{
				i = -1;
				break ;
			}
			i++;
		}
		if (i != -1)
			cmd->args.args[0] = search_path_of_cmd(cmd->args.args[0], cmd_path);
		if (cmd->args.args[0][0] == '/')
			execute_cmd(path->args, cmd);
	}
}

static void	ft_child_process(t_cmd_line *cmd, t_vector *path, int *p, int size)
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
	exe_first_cmd(cmd, path, size);
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
		g_var.stat = 128 + WTERMSIG(g_var.stat);
		if (WTERMSIG(g_var.stat) == SIGQUIT)
			write(1, "Quit: 3\n", 9);
		if (WTERMSIG(g_var.stat) == SIGINT)
			write(1, "\n", 1);
	}
}

void	execute_second_cmd(t_cmd_line *cmd_line, t_vector *path, int *p, int size)
{
	int p2[2];
	int ret;
	pid_t pid;

	pipe(p2);
	g_var.pid = fork();
	if (g_var.pid == 0)
		ft_child_process(cmd_line, path, p2, size);
	else
	{
		signal(SIGINT, SIG_IGN);
		close(p2[1]);
		ret = wait(&g_var.stat);
		if (cmd_line->next == NULL)
			last_node_exit_status(ret, p2);
		else
		{
			if (g_var.original_stdin)
				close(g_var.original_stdin);
			g_var.original_stdin = p2[0];
			cmd_line = cmd_line->next;
			execute_second_cmd(cmd_line, path, p2, size);
		}
		signal(SIGINT, parent_sig);
	}
}
