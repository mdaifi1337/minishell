#include "minishell.h"

void vector_init(t_vector *v)
{
    v->size = 1;
    v->used_size = 0;
    v->args = (char **)malloc(sizeof(char *) * v->size);
}

static char	**ft_realloc(t_vector *v, int size)
{
	char	**new;
	char	**tmp;
	int		i;

	tmp = (char **)malloc(sizeof(char *) * v->used_size + 1);
	i = -1;
	while (++i < v->used_size)
		tmp[i] = v->args[i];
	tmp[i] = NULL;
	new = (char **)malloc(sizeof(char *) * size + 1);
	i = -1;
	while (++i < v->used_size)
		new[i] = v->args[i];
	while (i < size)
	{
		new[i] = NULL;
		i++;
	}
	return (new);
}

void	vector_resize(t_vector *v, int size)
{
    char	**items;

	items = ft_realloc(v, size);
    if (items)
	{
        v->args = items;
        v->size = size;
    }
}

void	vector_add(t_vector *v, char *item)
{
	if (v->size == v->used_size)
    	vector_resize(v, v->size * 2);
    v->args[v->used_size++] = ft_strdup(item);
}

void	vector_add_at_index(t_vector *v, int index, char *item)
{
	free(v->args[index]);
	v->args[index] = ft_strdup(item);
	if (v->used_size + 1 <= v->size)
		v->used_size++;
}

void	free_vector(t_vector *v)
{
	int	i;

	i = -1;
	while (++i < v->size)
		free(v->args[i]);
	free(v->args);
}