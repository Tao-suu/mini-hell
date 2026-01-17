/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 18:45:34 by picheval          #+#    #+#             */
/*   Updated: 2026/01/17 12:00:15 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_ast_recurse(t_ast **root, t_lexem *start, t_lexem *end,
				int level);

static int	manage_cmd_redir(t_cmd *cmd, t_lexem **start, t_lexem *end)
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
	tmp = create_redirection_elem((*start)->type, (*start)->next->value);
	if (!tmp)
		return (FALSE);
	add_redirection_in_list(&(cmd->redir), tmp);
	*start = (*start)->next;
	return (TRUE);
}
// (ls < in1 < in2 &&ls >> toto)||(ls -l <in > out&&ls)
// (ls < in1 < in2 &&ls >> toto) > toto&& test ||(ls -l <in > out&&ls)

static int	manage_parenthesis(t_ast **ast, t_lexem **start, t_lexem *end)
{
	t_lexem	*sub_start;

	if (ft_strcmp((*start)->type->name, "PO"))
		return (TRUE);
	sub_start = (*start)->next;
	if (!sub_start)
		return (FALSE);
	skip_parenthesis(start, end);
	return (create_ast_recurse(ast, sub_start, *start, (*start)->lvl + 1));
}

static int	create_cmd_pipeline(t_cmd **list, t_lexem *start, t_lexem *end)
{
	t_cmd	*cmd;
	size_t	nb_argv;
	int		i_argv;

	while (start && start != end)
	{
		nb_argv = compute_nb_params(start, end);
		cmd = create_cmd_elem(nb_argv);
		if (!cmd)
			return (FALSE);
		add_cmd_elem_in_list(list, cmd);
		i_argv = -1;
		while (start && start != end && ft_strcmp(start->type->name, "PIPE"))
		{
			if (!ft_strcmp(start->type->name, "cmd")
				|| !ft_strcmp(start->type->name, "param"))
				cmd->argv[++i_argv] = ft_strdup(start->value);
			else if (!manage_cmd_redir(cmd, &start, end))
				return (FALSE);
			else if (!manage_parenthesis(&(cmd->ast), &start, end))
				return (FALSE);
			start = start->next;
		}
		if (start && start != end)
			start = start->next;
	}
	return (TRUE);
}

// start included, end excluded
static int	create_ast_recurse(t_ast **root, t_lexem *start, t_lexem *end,
	int level)
{
	t_lexem	*sep;
	t_ast	*new_elem;

	new_elem = create_ast_elem();
	if (!new_elem)
		return (FALSE);
	*root = new_elem;
	sep = find_first_operator_in_level(start, end, level);
	if (sep)
	{
		if (!ft_strcmp(sep->type->name, "AND"))
			new_elem->node_type = NODE_TYPE_AND;
		else
			new_elem->node_type = NODE_TYPE_OR;
		if (!create_ast_recurse(&(new_elem->left), start, sep, level))
			return (FALSE);
		return (create_ast_recurse(&(new_elem->right), sep->next, end, level));
	}
	new_elem->node_type = NODE_TYPE_CMD;
	return (create_cmd_pipeline(&(new_elem)->cmds, start, end));
}

int	create_ast(t_data *data)
{
	if (!create_ast_recurse(&(data->ast), data->head, NULL, 0))
		return (FALSE);
	//ft_printf("\n");
	//print_ast(data->ast, 0);
	return (TRUE);
}
/*
APP		1
HERE	2

flag = APP | HERE

(flag & APP) == APP
(flag & HERE) == HERE
*/
