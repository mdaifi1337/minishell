/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 21:39:39 by mdaifi            #+#    #+#             */
/*   Updated: 2021/06/11 16:18:57 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	if (n / 10 != 0)
		ft_putnbr_fd(n / 10, fd);
	if (sign == -1 && n / 10 == 0)
		ft_putchar_fd('-', fd);
	ft_putchar_fd((n % 10) * sign + '0', fd);
}
