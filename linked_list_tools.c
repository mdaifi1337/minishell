/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 16:17:20 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/15 10:32:40 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_redir_list(t_cmd_line *cmd_line, t_redir *redir)
{
	t_redir	*tmp_redir;

	tmp_redir = redir;
	while (tmp_redir)
	{
		lst_add_back_redir(&cmd_line->redir, tmp_redir->type, tmp_redir->file);
		tmp_redir = tmp_redir->next;
	}
}

void	lst_add_back_cmd(t_cmd_line **cmd_line, t_vector v, t_redir *redir)
{
	t_cmd_line	*tmp;
	t_cmd_line	*new;

	new = (t_cmd_line *)malloc(sizeof(t_cmd_line));
	if (new == NULL)
		return ;
	new->redir = NULL;
	if (redir)
		copy_redir_list(new, redir);
	new->args = copy_vector(v);
	new->next = NULL;
	tmp = *cmd_line;
	if (*cmd_line == NULL)
		*cmd_line = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	lst_add_back_redir(t_redir **redir, t_type type, char *file)
{
	t_redir	*tmp;
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (new == NULL)
		return ;
	new->type = type;
	new->file = ft_strdup(file);
	new->next = NULL;
	tmp = *redir;
	if (*redir == NULL)
		*redir = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	lst_add_back_token(t_token **token_list, t_type type, char *str)
{
	t_token	*new;
	t_token	*tmp;

	new = (t_token *)malloc(sizeof(t_token));
	new->token = ft_strdup(str);
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	tmp = *token_list;
	if (*token_list == NULL)
	{
		new->prev = NULL;
		*token_list = new;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

int	ft_lst_size(t_cmd_line *lst)
{
	int		size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
