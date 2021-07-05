/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 21:38:42 by mdaifi            #+#    #+#             */
/*   Updated: 2021/06/11 16:15:52 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		end;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup(""));
	end = ft_strlen(s1) - 1;
	while (set[j] && i <= end)
	{
		if (set[j] == s1[i])
		{
			i++;
			j = 0;
		}
		if (set[j] == s1[end])
		{
			end--;
			j = 0;
		}
		else if (set[j] != s1[i] && set[j] != s1[end])
			j++;
	}
	return (ft_substr(s1, i, (end - i + 1)));
}
