/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:34:49 by mdaifi            #+#    #+#             */
/*   Updated: 2021/06/11 16:23:45 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*convert(int count, int n)
{
	char	*str;
	int		ok;

	ok = n;
	str = (char *)malloc(sizeof(char) * count + 1);
	if (str)
	{
		if (n < 0)
			n = n * -1;
		str[count] = '\0';
		while (count != 0)
		{
			str[count - 1] = (n % 10) + '0';
			n = n / 10;
			count--;
		}
		if (ok < 0)
			str[0] = '-';
		return (str);
	}
	return (ft_strdup(""));
}

char	*ft_itoa(int n)
{
	int		l;
	int		count;

	count = 0;
	l = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (n <= 2147483647)
	{
		while (l != 0)
		{
			l = l / 10;
			count++;
		}
		if (n < 0)
			count++;
		return (convert(count, n));
	}
	return (ft_strdup(""));
}
