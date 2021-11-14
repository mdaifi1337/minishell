/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 18:25:24 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/14 15:11:00 by mdaifi           ###   ########.fr       */
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

static void	heredocs(char *file, char **str)
{
	char	*tmp;
	char	*buff;

	*str = NULL;
	while (1)
	{
		buff = readline("> ");
		if (!buff || !ft_strcmp(file, buff))
			break;
		if (!*str)
			*str = ft_strdup(buff);
		else
		{
			tmp = *str;
			*str = ft_strjoin_new_line(*str, buff);
			free(tmp);
		}
		free(buff);
	}
	*str = ft_strjoin_new_line(*str, "");
}

void exec_redir(t_redir *redir, t_vector *path)
{
	int		fd;
	int		i;
	int		p[2];
	char	*str;

	i = 0;
	pipe(p);
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
			g_var.heredoc = 1;
			heredocs(redir->file, &str);
			write(p[1], str, ft_strlen(str));
			dup2(p[0], g_var.original_stdin);
			close(p[1]);
			close(p[0]);
			i = 0;
		}
		else if (redir->type == e_less && !redir->next)
		{
			fd = open(redir->file, O_RDONLY, 0755);
			dup2(fd, 0);
		}
		if (redir->type != e_dless && redir->type != e_less && i != 0)
		{
			check_permissions(redir);
			fd_error(fd);
		}
		redir = redir->next;
	}
	if (i != 0)
		dup2(fd, 1);
	// close(fd);
}
