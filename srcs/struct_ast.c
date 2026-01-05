/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:24:16 by picheval          #+#    #+#             */
/*   Updated: 2026/01/05 16:09:08 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_ast_elem(void)
{
	t_ast	*ret;

	if (!(ret = (t_ast *)ft_calloc(sizeof(t_ast), 1)))
	{
		print_sys_error("create_ast_elem / ft_calloc");
		return (NULL);
	}
	return (ret);
}

void	free_ast_tree(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->left)
		free_ast_tree(ast->left);
	if (ast->right)
		free_ast_tree(ast->right);
	if (ast->node_type)
		free(ast->node_type);
	if (ast->cmds)
		free_cmds_list(ast->cmds);
	free(ast);
}