/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 18:45:34 by picheval          #+#    #+#             */
/*   Updated: 2026/01/25 13:40:26 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_ast_recurse(t_data *data, t_ast **root, t_lexem *store[2],
				int level);

static int	manage_cmd_redir(t_data *data, t_cmd *cmd, t_lexem **start,
	t_lexem *end)
{
	t_redirection	*tmp;

	if (ft_strcmp((*start)->type->name, "IN")
		&& ft_strcmp((*start)->type->name, "OUT")
		&& ft_strcmp((*start)->type->name, "APPEND")
		&& ft_strcmp((*start)->type->name, "HEREDOC"))
		return (TRUE);
	// If suivant inutile ? (pas reussi a le declencher)
	// En theorie il est deja gere par le parser
	if (!(*start)->next || (*start)->next == end
		|| ft_strcmp((*start)->next->type->name, "file"))
		return (print_error("cmd_redir: no file"));
	if (!ft_strcmp((*start)->type->name, "HEREDOC"))
		tmp = create_redirection_elem((*start)->type, NULL);
	else
		tmp = create_redirection_elem((*start)->type, (*start)->next->value);
	if (!tmp)
		return (FALSE);
	add_redirection_in_list(&(cmd->redir), tmp);
	if (!ft_strcmp((*start)->type->name, "HEREDOC")
		&& !manage_heredoc_elem(&(data->heredocs), tmp, (*start)->next->value))
		return (FALSE);
	*start = (*start)->next;
	return (TRUE);
}

static int	manage_parenthesis(t_data *data, t_ast **ast, t_lexem **start,
	t_lexem *end)
{
	t_lexem	*sub_start;
	t_lexem	*tmp[2];

	if (ft_strcmp((*start)->type->name, "PO"))
		return (TRUE);
	sub_start = (*start)->next;
	if (!sub_start)
		return (FALSE);
	skip_parenthesis(start, end);
	tmp[0] = sub_start;
	tmp[1] = *start;
	return (create_ast_recurse(data, ast, tmp, (*start)->lvl + 1));
}

static int	create_cmd_pipeline(t_data *data, t_cmd **list, t_lexem *start,
	t_lexem *end)
{
	t_cmd	*cmd;
	size_t	nb_argv;

	while (start && start != end)
	{
		nb_argv = compute_nb_params(start, end);
		cmd = create_cmd_elem(nb_argv);
		if (!cmd)
			return (FALSE);
		add_cmd_elem_in_list(list, cmd);
		while (start && start != end && ft_strcmp(start->type->name, "PIPE"))
		{
			if (!ft_strcmp(start->type->name, "cmd")
				|| !ft_strcmp(start->type->name, "param"))
				cmd->argv[cmd->argc++] = ft_strdup(start->value);
			else if (!manage_cmd_redir(data, cmd, &start, end))
				return (FALSE);
			else if (!manage_parenthesis(data, &(cmd->ast), &start, end))
				return (FALSE);
			start = start->next;
		}
		if (start && start != end)
			start = start->next;
	}
	return (TRUE);
}

// start included, end excluded
static int	create_ast_recurse(t_data *data, t_ast **root, t_lexem *store[2],
	int level)
{
	t_lexem	*tmp[2];
	t_lexem	*sep;
	t_ast	*new_elem;

	new_elem = create_ast_elem();
	if (!new_elem)
		return (FALSE);
	*root = new_elem;
	sep = find_last_operator_in_level(store[0], store[1], level);
	if (sep)
	{
		if (!ft_strcmp(sep->type->name, "AND"))
			new_elem->node_type = NODE_TYPE_AND;
		else
			new_elem->node_type = NODE_TYPE_OR;
		tmp[0] = store[0];
		tmp[1] = sep;
		if (!create_ast_recurse(data, &(new_elem->left), tmp, level))
			return (FALSE);
		tmp[0] = sep->next;
		tmp[1] = store[1];
		return (create_ast_recurse(data, &(new_elem->right), tmp, level));
	}
	new_elem->node_type = NODE_TYPE_CMD;
	return (create_cmd_pipeline(data, &(new_elem)->cmds, store[0], store[1]));
}

int	create_ast(t_data *data)
{
	t_lexem	*store[2];

	store[0] = data->head;
	store[1] = NULL;
	if (!create_ast_recurse(data, &(data->ast), store, 0))
		return (FALSE);
	// ft_printf("\n");
	// print_ast(data->ast, 0);
	return (TRUE);
}
