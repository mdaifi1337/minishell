/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 18:20:53 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/15 11:25:29 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_lines(t_cmd_line *cmd_line)
{
	int			i;
	t_cmd_line	*tmp;
	t_redir		*tmp_redir;

	tmp = cmd_line;
	while (tmp)
	{
		i = -1;
		while (++i < tmp->args.used_size)
			printf("---- |%s|\n", tmp->args.args[i]);
		tmp_redir = tmp->redir;
		while (tmp_redir)
		{
			printf("+++ %s\n", tmp_redir->file);
			printf("+++ %d\n", tmp_redir->type);
			tmp_redir = tmp_redir->next;
		}
		printf("~~~~~~~~~~~~~~~~~~~~~~\n");
		tmp = tmp->next;
	}
}

static void	save_and_execute_cmd_line(t_vector *path, char *str)
{
	t_cmd_line	*cmd_line;
	t_token		*token_list;

	cmd_line = NULL;
	add_history(str);
	token_list = tokenize_command_line(str);
	if (token_list && !check_token_syntax(token_list))
		free_token_list(token_list);
	else if (token_list)
	{
		cmd_line = treat_pipe_sequence(token_list);
		free_token_list(token_list);
		if (cmd_line)
		{
			look_for_expandable_vars(cmd_line, path);
			// print_cmd_lines(cmd_line);
			check_cmd(cmd_line, path);
			free_cmd_line_list(cmd_line);
		}
	}
}	

int	main(int argc, char *argv[], char *env[])
{
	t_vector	*path;
	char		*str;
	int			true;

	true = 1;
	path = env_copy(env);
	init_global_struct();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, parent_sig);
	while (true)
	{
		str = readline("minishell > ");
		if (!str)
			exit(1);
		else if (ft_strlen(str))
		{
			save_and_execute_cmd_line(path, str);
			free(str);
		}
	}
	return (0);
}
