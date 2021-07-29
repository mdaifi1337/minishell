#include "minishell.h"

void vector_init(t_vector *v)
{
    v->size = 1;
    v->total_size = 0;
    v->args = (char **)malloc(sizeof(char *) * v->size);
}

static char	**ft_realloc(char **args, size_t size)
{
	char	**new;
	char	**tmp;
	int		i;
	int		length;

	length = 0;
	while (args[length])
		length++;
	tmp = (char **)malloc(sizeof(char *) * length + 1);
	i = -1;
	while (args[++i])
		tmp[i] = args[i];
	tmp[i] = NULL;
	new = (char **)malloc(sizeof(char *) * size + 1);
	i = -1;
	while (args[++i])
		new[i] = args[i];
	while (new[i])
		new[i++] = NULL;
	new[i++] = NULL;
	return (new);
}

static void vector_resize(t_vector *v, int size)
{
    char	**items;

	items = (char **)ft_realloc(v->args, size);
    if (items)
	{
        v->args = items;
        v->size = size;
    }
}

void	vector_add(t_vector *v, char *item)
{
	if (v->size == v->total_size)
    	vector_resize(v, v->size * 2);
    v->args[v->total_size++] = item;
}