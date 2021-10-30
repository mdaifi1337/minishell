#ifndef MINISHELL_
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_type
{
	e_word, e_pipe, e_less, e_great, e_dless, e_dgreat, e_start, e_end
}t_type;

typedef struct s_char_vec {
	char	*arg;
	int		size;
	int		used_size;
}t_char_vec;

typedef struct s_vector {
	char		**args;
	int			size;
	int			used_size;
}t_vector;

typedef struct s_redir
{
	t_type					type;
	char					*file;
	struct s_redir		*next;
}t_redir;


typedef struct	s_cmd_line
{
	t_vector			args;
	int					i;
	t_redir			*redir;
	struct s_cmd_line	*next;
}t_cmd_line;

typedef	struct	s_token
{
	char			*token;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}t_token;

int		check_nbr_of_quotes(char *str);
int		check_token_syntax(t_token *token);
void	remove_quotes(t_vector *v);
void	double_free(char **tab, int size);
void	ft_free_list(t_token *head);
void	ft_free_redir_list(t_redir *head);
void	free_cmd_line_list(t_cmd_line *cmd_line);
void	free_token_list(t_token *head);
void	free_vector(t_vector *v);
void	char_vec_add(t_char_vec *char_vec, char c);
void	init_char_vec(t_char_vec *char_vec);
void	vector_init(t_vector *v);
void	vector_add(t_vector *v, char *item);
void	vector_resize(t_vector *v, int size);
void	vector_add_at_index(t_vector *v, int index, char *item);
void	lst_add_back_redir(t_redir **redir, t_type type, char *file);
void	lst_add_back_token(t_token **token_list, t_type type, char *str);
void	lst_add_back_cmd(t_cmd_line **cmd_line, t_vector v, t_redir *redir);
void	ignore_dollar_var(t_vector *v, int i);
void	dollar_var_not_found(t_vector *v, int i);
void	resize_vec_when_dollar_var_empty(t_vector *v, int i);
void	insert_dollar_vars_in_vector(t_vector *v, int size, int curr_pos);
void	replace_dollar_var(t_vector *v, int curr_pos, char *name, char *value);
t_vector	copy_vector(t_vector v);
t_char_vec	new_char_vec(t_vector *v, int i, int *j);
t_cmd_line	*treat_pipe_sequence(t_token *token_list);

#endif
