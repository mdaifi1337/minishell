/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:15:56 by mdaifi            #+#    #+#             */
/*   Updated: 2021/06/11 16:20:51 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	t_list	*first;

	if (alst == NULL)
	{
		*alst = new;
		new->next = NULL;
	}
	first = *alst;
	new->next = first;
	*alst = new;
}
