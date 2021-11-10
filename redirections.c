/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 18:25:24 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/10 14:56:30 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	redirections(char *str, int i)
{
	if (!ft_strncmp(str + i, "<<", 2))
		return (e_dless);
	if (!ft_strncmp(str + i, ">>", 2))
		return (e_dgreat);
	if (!ft_strncmp(str + i, "<", 1))
		return (e_less);
	if (!ft_strncmp(str + i, ">", 1))
		return (e_great);
	if (!ft_strncmp(str + i, "|", 1))
		return (e_pipe);
	return (e_word);
}

void exec_redir(t_redir *redir, t_vector *path)
{
	int fd;
	int i;
	char *tmp;
	int p[2];
	char *str;

	i = 0;
	pipe(p);
	str = NULL;
	while (redir)
	{
		if (redir->type == e_dgreat)
		{
			fd = open(redir->file, O_WRONLY | O_APPEND | O_CREAT, 0755);
			i++;
		}
		else if (redir->type == e_great)
		{
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0755);
			i++;
		}
		else if (redir->type == e_dless)
		{
			while (1)
			{
				tmp = readline("> ");
				if (!ft_strcmp(redir->file, tmp) || !tmp)
					break;
				if (str)
					str = ft_strdup(tmp);
				else
					str = ft_strjoin_new_line(str, tmp);
			}
			str = ft_strjoin_new_line(str, "");
			write(p[1], str, ft_strlen(str));
			dup2(p[0], 0);
			close(p[1]);
			close(p[0]);
			i = 0;
		}
		else if (redir->type == e_less)
		{
			fd = open(redir->file, O_RDONLY, 0755);
			dup2(fd, 0);
		}
		if (redir->type != e_dless && redir->type != e_less && i != 0)
		{
			if (redir->type == e_less)
				check_permissions(redir->file, "read");
			else if (redir->type == e_great)
				check_permissions(redir->file, "write");
			fd_error(fd);
		}
		redir = redir->next;
	}
	if (i != 0)
		dup2(fd, 1);
}
