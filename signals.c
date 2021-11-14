/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 10:43:18 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/11 15:15:01 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_sig(int sig)
{
	if (sig == SIGINT && g_var.pid == 0)
	{
		write(1, "\n", 2);
		g_var.stat = 130;
		if (g_var.heredoc == 1)
			g_var.stat = 1;
	}
	else if (sig == SIGQUIT && g_var.pid == 0)
	{
		write(1, "^\\Quit: 3\n", 11);
		g_var.stat = 131;
	}
	exit(g_var.stat);
}

void parent_sig(int sig)
{
	if (g_var.heredoc == 1)
		g_var.stat = 1;
	write(1, "\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_var.stat = 1;
}
