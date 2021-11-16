/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 18:16:36 by mdaifi            #+#    #+#             */
/*   Updated: 2021/11/16 09:04:47 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# define debug printf("DEBUG\n");

typedef enum e_type
{
	e_word,
	e_pipe,
	e_less,
	e_great,
	e_dless,
	e_dgreat,
	e_start,
	e_end
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
	int			i;
}t_vector;

typedef struct s_redir
{
	t_type				type;
	char				*file;
	struct s_redir		*next;
}t_redir;

typedef struct s_cmd_line
{
	t_vector			args;
	t_redir				*redir;
	struct s_cmd_line	*next;
}t_cmd_line;

typedef struct s_var
{
	int		size;
	int		stat;
	int		reset;
	int		heredoc;
	int		original_stdin;
	pid_t	pid;
}t_var;

typedef struct s_token
{
	char			*token;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}t_token;

extern t_var	g_var;
t_var			g_var;
int			ft_lst_size(t_cmd_line *lst);
int			check_nbr_of_quotes(char *str);
int			check_built_ins(t_cmd_line *cmd);
int			check_token_syntax(t_token *token);
char		*search_for_path_in_env(char **env);
char		*search_path_of_cmd(char *str, char *env);
void		init_global_struct(void);
void		path_not_found(char *path);
void		remove_quotes(t_vector *v);
void		free_array_of_strings(char **tab, int size);
void		ft_free_list(t_token *head);
void		fd_error(int fd);
void		child_sig(int sig);
void		parent_sig(int sig);
void		ft_free_redir_list(t_redir *head);
void		free_cmd_line_list(t_cmd_line *cmd_line);
void		free_token_list(t_token *head);
void		free_vector(t_vector *v);
void		char_vec_add(t_char_vec *char_vec, char c);
void		exec_redir(t_redir *redir, t_vector *path);
void		init_char_vec(t_char_vec *char_vec);
void		vector_init(t_vector *v);
void		cd_home(t_vector *path);
void		vector_add(t_vector *v, char *item);
void		look_for_backslash(char *arg, int *i);
void		vector_delete(t_vector *v, int index);
void		check_cmd(t_cmd_line *cmd, t_vector *path);
void		check_permissions(t_redir *redir);
void		vector_resize(t_vector *v, int size);
void		vector_add_at_index(t_vector *v, char *item);
void		built_ins(t_cmd_line *cmd_line, t_vector *path);
void		execute_cmd(char **env, t_cmd_line *cmd_line);
void		exe_first_cmd(t_cmd_line *cmd, t_vector *path);
void		lst_add_back_redir(t_redir **redir, t_type type, char *file);
void		lst_add_back_token(t_token **token_list, t_type type, char *str);
void		lst_add_back_cmd(t_cmd_line **cmd_line, t_vector v, t_redir *redir);
void		dollar_var_has_multiple_values(t_vector *v,
				t_char_vec *new_char_vec, char **tab, int curr_pos);
void		execute_second_cmd(t_cmd_line *cmd_line, t_vector *path);
void		ignore_dollar_var(t_vector *v);
void		cmd_unset(t_cmd_line *cmd, t_vector *path);
void		cmd_env(t_cmd_line *cmd_line, t_vector *path);
void		cmd_echo(t_cmd_line *cmd);
void		cmd_pwd(t_cmd_line *cmd_line);
void		cmd_exit(t_cmd_line *cmd_line);
void		cmd_export(t_cmd_line *cmd, t_vector *path);
void		cmd_cd(t_cmd_line *cmd_line, t_vector *path);
void		write_heredocs_in_stdin(char *str);
void		replace_path(t_vector *path, t_vector *env, int i);
void		dollar_var_not_found(t_vector *v);
void		look_for_expandable_vars(t_cmd_line *cmd_line, t_vector *env);
void		split_dollar_var(t_vector *v, int curr_pos, char *value);
void		resize_vec_when_dollar_var_empty(t_vector *v);
void		insert_dollar_vars_in_vector(t_vector *v, int size);
void		replace_dollar_var(t_vector *v, char *name, char *value);
t_type		redirections(char *str, int i);
t_token		*tokenize_command_line(char *str);
t_vector	*env_copy(char *env[]);
t_vector	copy_vector(t_vector v);
t_cmd_line	*treat_pipe_sequence(t_token *token_list);
t_char_vec	new_char_vec(t_vector *v);

#endif
