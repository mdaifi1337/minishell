#include "minishell.h"

void	lst_add_back_cmd(t_cmd_line **cmd_line, t_vector v, t_redirect *redirect)
{
	t_cmd_line	*tmp;
	t_cmd_line	*new;
	t_redirect	*tmp_redir;

	new = (t_cmd_line *)malloc(sizeof(t_cmd_line));
	if (new == NULL)
		return ;
	new->redirect = NULL;
	tmp_redir = redirect;
	while (tmp_redir)
	{
		lst_add_back_redirect(&new->redirect, tmp_redir->type, tmp_redir->file);
		tmp_redir = tmp_redir->next;
	}
	new->args = v;
	new->next = NULL;
	tmp = *cmd_line;
	if (*cmd_line == NULL)
		*cmd_line = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	lst_add_back_redirect(t_redirect **redirect, t_type type, char *file)
{
	t_redirect	*tmp;
	t_redirect	*new;

	new = (t_redirect *)malloc(sizeof(t_redirect));
	if (new == NULL)
		return ;
	new->type = type;
	new->file = ft_strdup(file);
	new->next = NULL;
	tmp = *redirect;
	if (*redirect == NULL)
		*redirect = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	free_cmd_line_list(t_cmd_line *cmd_line)
{
	int			i;
	t_cmd_line	*tmp;

	while (cmd_line)
	{
		tmp = cmd_line;
		i = -1;
		while (++i < cmd_line->args.size)
			free(cmd_line->args.args[i]);
		ft_free_redirect_list(cmd_line->redirect);
		cmd_line->redirect = NULL;
		cmd_line = cmd_line->next;
		free(tmp);
	}
}