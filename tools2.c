/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 16:33:30 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/10 16:39:08 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_array(char **tab, int size)
{
	int		i;
	char	**args;

	args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL); //allocation error
	i = -1;
	while (++i < size)
		args[i] = tab[i];
	args[i] = NULL;
	return (args);
}