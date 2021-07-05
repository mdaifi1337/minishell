/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 20:44:44 by mdaifi            #+#    #+#             */
/*   Updated: 2021/06/11 16:17:24 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup(""));
	tmp = (char *)malloc(sizeof(char) *(ft_strlen(s1) + ft_strlen(s2) + 1));
	if (tmp)
	{
		while (s1[i])
		{
			tmp[i] = s1[i];
			i++;
		}
		while (s2[j])
			tmp[i++] = s2[j++];
		tmp[i] = '\0';
		return (tmp);
	}
	return (NULL);
}
