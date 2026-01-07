/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbez--du <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:17:03 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/07 05:39:26 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_ast(t_data *data, t_ast *ast)
{
	//printf("ast type: %s\n", ast->node_type);
	if (!ft_strcmp(ast->node_type, "cmd"))
	{
		if (!ast->cmds)
			return (0);
		//dprintf(2, "ast cmd: %s\n", ast->cmds->argv[0]);
		return (exec_pipe(data, ast->cmds));
	}
	int ret = exec_ast(data, ast->left);
	int deg =  ft_strcmp(ast->node_type, "&&");
	if (!deg && !ret)
		return exec_ast(data, ast->right);
	else if (!ft_strcmp(ast->node_type, "||") && ret)
		return exec_ast(data, ast->right);
	return (ret);
}
