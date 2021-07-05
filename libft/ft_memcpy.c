/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 21:04:01 by mdaifi            #+#    #+#             */
/*   Updated: 2021/06/11 16:19:14 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	if (!dst && !src)
		return (NULL);
	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return ((void *)s1);
}
