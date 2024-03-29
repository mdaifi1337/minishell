/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:48:21 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/15 11:29:11 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->token);
		free(tmp);
	}
}

void	free_array_of_strings(char **tab, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (tab[i])
			free(tab[i]);
	}
	free(tab);
	tab = NULL;
}

void	free_vector(t_vector *v)
{
	int	i;

	i = -1;
	while (++i < v->used_size)
	{
		if (v->args[i])
			free(v->args[i]);
	}
	free(v->args);
}

void	free_cmd_line_list(t_cmd_line *cmd_line)
{
	int			i;
	t_cmd_line	*tmp;

	while (cmd_line)
	{
		tmp = cmd_line;
		i = -1;
		while (++i < tmp->args.used_size)
		{
			if (tmp->args.args[i])
				free(tmp->args.args[i]);
		}
		free(tmp->args.args);
		ft_free_redir_list(tmp->redir);
		cmd_line = cmd_line->next;
		free(tmp);
	}
}

void	ft_free_redir_list(t_redir *head)
{
	t_redir	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
	}
}
