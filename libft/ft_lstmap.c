/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:43:30 by mdaifi            #+#    #+#             */
/*   Updated: 2021/06/11 16:21:03 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;
	t_list	*head;
	void	*tmp2;

	if (lst == NULL)
		return (lst);
	tmp = lst->next;
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (NULL);
	head = new;
	while (tmp != NULL)
	{
		tmp2 = tmp->content;
		new->next = ft_lstnew(f(tmp2));
		if (!new)
		{
			ft_lstclear(&head, del);
			break ;
		}
		new = new->next;
		tmp = tmp->next;
	}
	return (head);
}
