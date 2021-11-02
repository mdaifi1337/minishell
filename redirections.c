/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 18:25:24 by mdaifi            #+#    #+#             */
/*   Updated: 2021/10/30 18:30:33 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	redirections(char *str, int i)
{
	if (!ft_strncmp(str + i, "<<", 2))
		return (e_dless);
	if (!ft_strncmp(str + i, ">>", 2))
		return (e_dgreat);
	if (!ft_strncmp(str + i, "<", 1))
		return (e_less);
	if (!ft_strncmp(str + i, ">", 1))
		return (e_great);
	if (!ft_strncmp(str + i, "|", 1))
		return (e_pipe);
	return (e_word);
}
