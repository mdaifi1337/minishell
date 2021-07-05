/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 21:09:46 by mdaifi            #+#    #+#             */
/*   Updated: 2021/06/11 16:13:50 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = (char *)malloc(count * size);
	if (tmp)
	{
		while (i < count * size)
		{
			tmp[i] = 0;
			i++;
		}
		return ((void *)tmp);
	}
	return (NULL);
}
