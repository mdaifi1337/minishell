#include "minishell.h"

void vector_init(t_vector *v)
{
    v->size = 1;
    v->total_size = 0;
    v->args = (char **)malloc(sizeof(char *) * v->size);
}

static char	**ft_realloc(t_vector *v, int size)
{
	char	**new;
	char	**tmp;
	int		i;
	int		length;

	length = 0;
	while (length < v->total_size)
		length++;
	tmp = (char **)malloc(sizeof(char *) * length + 1);
	i = -1;
	while (++i < v->total_size)
		tmp[i] = v->args[i];
	tmp[i] = NULL;
	new = (char **)malloc(sizeof(char *) * size + 1);
	i = -1;
	while (++i < v->total_size)
		new[i] = v->args[i];
	// while (i < size - 1)
	// 	new[i++] = NULL;
	// new[i] = NULL;
	return (new);
}

static void	vector_resize(t_vector *v, int size)
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
	// printf("Add\n");
	if (v->size == v->total_size)
	{
    	vector_resize(v, v->size * 2);
	}
	// printf("item : %s\n", item);
    v->args[v->total_size++] = item;
}

void	free_vector(t_vector *v)
{
	int	i;

	i = -1;
	while (++i < v->size)
		free(v->args[i]);
	free(v->args);
}