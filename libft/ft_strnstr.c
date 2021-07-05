/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:12:24 by mdaifi            #+#    #+#             */
/*   Updated: 2021/06/11 16:16:03 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while ((s2[j] != '\0' && s1[i] != '\0') && i < len)
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			while (s2[j] != '\0' && s1[i] == s2[j] && i < len)
			{
				i++;
				j++;
			}
		}
		else
			i++;
	}
	if (j == ft_strlen(s2))
		return ((char *)s1 + (i - j));
	return (NULL);
}
