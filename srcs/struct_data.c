/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:13:29 by picheval          #+#    #+#             */
/*   Updated: 2026/01/05 15:35:22 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

// full: if TRUE, clear all / else only clear line infos
void	free_data(t_data *data, char full)
{
	if (!data)
		return ;
	if (data->line)
		free(data->line);
	data->line = NULL;
	if (data->head)
		free_lexem_list(data->head);
	data->head = NULL;
	if (data->ast)
		free_ast_tree(data->ast);
	data->ast = NULL;
	if (full == FALSE)
		return ;
	if (data->env)
		ft_tabclear(data->env);
	if (data->set)
		ft_tabclear(data->set);
	if (data->operators)
		free_operator_tab(data->operators);
}

int	init_data(t_data *data)
{
	ft_memset((void *)data, 0, sizeof(t_data));
	data->env = ft_tabdup(environ);
	if (!data->env)
		return (print_sys_error("ft_tabdup"));
	if (!create_operators_array(&(data->operators)))
		return (FALSE);

	// TODO
		// init set
	
	return (TRUE);
}
