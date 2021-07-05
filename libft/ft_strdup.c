/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 20:49:17 by mdaifi            #+#    #+#             */
/*   Updated: 2021/06/11 16:17:43 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (tmp)
	{
		while (str[i])
		{
			tmp[i] = str[i];
			i++;
		}
		tmp[i] = '\0';
		return (tmp);
	}
	return (NULL);
}
