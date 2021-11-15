/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 18:25:24 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/15 13:33:27 by mdaifi           ###   ########.fr       */
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

static void	heredocs(char *file, int *i)
{
	char	*tmp;
	char	*buff;
	char	*str;

	*i = 0;
	str = NULL;
	g_var.heredoc = 1;
	while (1)
	{
		buff = readline("> ");
		if (!buff || !ft_strcmp(file, buff))
			break ;
		if (!str)
			str = ft_strdup(buff);
		else
		{
			tmp = str;
			str = ft_strjoin_new_line(str, buff);
			free(tmp);
		}
		free(buff);
	}
	str = ft_strjoin_new_line(str, "");
	write_heredocs_reslut(str);
	free(str);
}

static int	ft_open_files(t_redir *redir, int *i)
{
	int	fd;

	if (redir->type == e_dgreat)
	{
		fd = open(redir->file, O_WRONLY | O_APPEND | O_CREAT, 0755);
		(*i)++;
	}
	else if (redir->type == e_great)
	{
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0755);
		(*i)++;
	}
	else if (redir->type == e_less && !redir->next)
	{
		fd = open(redir->file, O_RDONLY, 0755);
		dup2(fd, 0);
	}
	return (fd);
}

void	exec_redir(t_redir *redir, t_vector *path)
{
	int		fd;
	int		i;

	i = 0;
	while (redir)
	{
		if (redir->type == e_dless)
			heredocs(redir->file, &i);
		else
			fd = ft_open_files(redir, &i);
		if (redir->type != e_dless && redir->type != e_less && i != 0)
		{
			check_permissions(redir);
			fd_error(fd);
		}
		redir = redir->next;
		if (redir)
			close(fd);
	}
	if (i != 0)
		dup2(fd, 1);
	close(fd);
}
