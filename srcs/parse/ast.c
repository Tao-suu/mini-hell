/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 18:45:34 by picheval          #+#    #+#             */
/*   Updated: 2026/02/02 10:40:51 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_cmd_pipeline(t_data *data, t_cmd **list, t_lexem *start,
	t_lexem *end)
{
	t_cmd	*cmd;

	// size_t	nb_argv;
	while (start && start != end)
	{
		// nb_argv = compute_nb_params(start, end);
		// cmd = create_cmd_elem(nb_argv);
		cmd = create_cmd_elem();
		if (!cmd)
			return (FALSE);
		add_cmd_elem_in_list(list, cmd);
		while (start && start != end && ft_strcmp(start->type->name, "PIPE"))
		{
			if (!manage_cmd_pipeline_elem(data, cmd, &start, end))
				return (FALSE);
			start = start->next;
		}
		if (start && start != end)
			start = start->next;
	}
	return (TRUE);
}

int	create_ast_recurse(t_data *data, t_ast **root, t_lexem *store[2],
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
