/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 15:03:32 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/07 15:24:25 by mdaifi           ###   ########.fr       */
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

static void	file_does_not_exist(char *file)
{
	if (access(file, F_OK))
	{
		write(2, file, ft_strlen(file));
		write(2, " : ", 4);
		perror("");
		exit(1);
	}
}

void	check_permissions(char *file, char *permission)
{
	if (!ft_strncmp(permission, "read", 5))
	{
		if (access(file, R_OK))
			file_does_not_exist(file);
	}
	else if (!ft_strncmp(permission, "write", 6))
	{
		if (access(file, W_OK))
			file_does_not_exist(file);
	}
}
