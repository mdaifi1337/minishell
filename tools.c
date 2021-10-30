#include "minishell.h"

void	ft_free_redir_list(t_redir *head)
{
	t_redir	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
	}
}

t_vector	copy_vector(t_vector v)
{
	t_vector	res;
	int			i;

	res.args = (char **)malloc(sizeof(char *) * v.size);
	if (!res.args)
		exit(1); //allocation error
	i = -1;
	while (++i < v.used_size)
		res.args[i] = ft_strdup(v.args[i]);
	res.used_size = v.used_size;
	res.size = v.size;
	return(res);
}

t_char_vec	new_char_vec(t_vector *v, int i, int *j)
{
	t_char_vec	res;

	init_char_vec(&res);
	*j = -1;
	while (v->args[i][++(*j)] && v->args[i][(*j)] != '$')
		char_vec_add(&res, v->args[i][(*j)]);
	(*j)++;
	while ((ft_isalnum(v->args[i][(*j)]) || v->args[i][(*j)] == '_')
		&& v->args[i][(*j)])
		(*j)++;
	if (v->args[i][(*j)] == '\\' && v->args[i][(*j)] != '?')
		(*j)++;
	(*j)--;
	while (v->args[i][++(*j)])
		char_vec_add(&res, v->args[i][(*j)]);
	return (res);
}
