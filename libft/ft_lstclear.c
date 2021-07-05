/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:11:07 by mdaifi            #+#    #+#             */
/*   Updated: 2021/06/11 16:20:53 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*nxt;

	tmp = *lst;
	while (tmp)
	{
		nxt = tmp->next;
		del(tmp->content);
		free(tmp);
		tmp = NULL;
		tmp = nxt;
	}
	*lst = NULL;
}
