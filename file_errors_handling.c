/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_errors_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 15:03:32 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/13 14:07:51 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_error(int fd)
{
	if (fd == -1)
	{
		perror("");
		exit(1);
	}
}

static void	file_error(char *file)
{
	write(2, "minishell: ", 12);
	write(2, file, ft_strlen(file));
	write(2, " : ", 4);
	perror("");
	exit(1);
}

void	check_permissions(t_redir *redir)
{
	if (redir->type == e_less)
	{
		if (access(redir->file, R_OK) || access(redir->file, F_OK))
			file_error(redir->file);
	}
	else if (redir->type == e_great || redir->type == e_dgreat)
	{
		if (access(redir->file, W_OK) || access(redir->file, F_OK))
			file_error(redir->file);
	}
}
