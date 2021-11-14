/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:45:15 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/13 15:27:26 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_for_path_in_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			if (ft_strlen(env[i]) > 5)
				return (ft_strchr(env[i], '/'));
	}
	return (NULL);
}

char	*search_path_of_cmd(char *str, char *env)
{
	char	**path;
	char	*tmp;
	int		i;

	path = ft_split(env, ':');
	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin_backslash(path[i], str);
		if (!access(tmp, F_OK))
			return (tmp);
		free(tmp);
	}
	printf("-----%s: command not found\n", str);
	g_var.stat = 127;
	return (NULL);
}

void path_not_found(char *path)
{
	if (!path)
	{
		write(2, "path is empty !", 16);
		exit(1);
	}
}
