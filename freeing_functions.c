/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 14:48:21 by mdaifi            #+#    #+#             */
/*   Updated: 2021/10/26 16:21:24 by mdaifi           ###   ########.fr       */
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

void	double_free(char **tab, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(tab[i]);
	free(tab);
}

void	free_vector(t_vector *v)
{
	int	i;

	i = -1;
	while (++i < v->size)
		free(v->args[i]);
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
		while (++i < cmd_line->args.size)
		{
			if (cmd_line->args.used_size)
				free(cmd_line->args.args[i]);
		}
		ft_free_redir_list(cmd_line->redir);
		cmd_line->redir = NULL;
		cmd_line = cmd_line->next;
		free(tmp);
	}
}