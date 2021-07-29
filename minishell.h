#ifndef MINISHELL_
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef enum	e_type
{
	e_word, e_pipe, e_less, e_great, e_dless, e_dgreat, e_start, e_end
}t_type;

typedef struct s_vector {
    char	**args;
    int		size;
    int		total_size;
}t_vector;

typedef struct	s_command_line
{
	char					**args;
	struct s_command_line	*next;
}t_command_line;

typedef	struct	s_token
{
	char	*token;
	t_type	type;
}t_token;

void	ft_free_list(t_list *head);
void	vector_add(t_vector *v, char *item);
int		check_token_syntax(t_list *token);
t_list	*treat_quotes(t_list *token_list);

#endif
