/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:17:03 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/25 21:31:36 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_ast(t_data *data, t_ast *ast)
{
	int	ast_ret;

	if (ast->node_type == NODE_TYPE_CMD)
	{
		if (!ast->cmds)
			return (0);
		return (exec_pipe(data, ast->cmds));
	}
	ast_ret = exec_ast(data, ast->left);
	if (ast->node_type == NODE_TYPE_AND && !ast_ret && ast_ret != 130)
		return (exec_ast(data, ast->right));
	else if (ast->node_type == NODE_TYPE_OR && ast_ret && ast_ret != 130)
		return (exec_ast(data, ast->right));
	return (ast_ret);
}
