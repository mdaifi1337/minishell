#ifndef MINISHELL_
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef enum	e_type
{
	e_word, e_pipe, e_less, e_great, e_dless, e_dgreat, e_start, e_end
}t_type;

typedef struct s_vector {
    char	**args;
    int		size;
    int		total_size;
}t_vector;

typedef struct s_redirect
{
	t_type					type;
	char					*file;
	struct s_redirect		*next;
}t_redirect;


typedef struct	s_cmd_line
{
	char				**args;
	int					i;
	t_redirect			*redirect;
	struct s_cmd_line	*next;
}t_cmd_line;

typedef	struct	s_token
{
	char			*token;
	t_type			type;
	struct s_token	*next;
}t_token;

int		check_token_syntax(t_token *token);
char	**copy_table(char **tab, int size);
void	ft_free_list(t_token *head);
void	ft_free_redirect_list(t_redirect *head);
void	free_vector(t_vector *v);
void	vector_init(t_vector *v);
void	vector_add(t_vector *v, char *item);
void	vector_add(t_vector *v, char *item);
void	lst_add_back_cmd(t_cmd_line **cmd_line, t_vector *v, t_redirect *redirect);
void	lst_add_back_redirect(t_redirect **redirect, t_type type, char *file);
t_cmd_line	*treat_pipe_sequence(t_token *token_list);

#endif
