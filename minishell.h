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

typedef	struct s_token
{
	char			*token;
	t_type			type;
}t_token;

void	check_token_syntax(t_list *token);

#endif
