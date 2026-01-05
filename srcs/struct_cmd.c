/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 21:40:47 by picheval          #+#    #+#             */
/*   Updated: 2026/01/05 15:31:56 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *elem)
{
	if (!elem)
		return ;
	if (elem->path)
		free(elem->path);
	if (elem->argv)
		ft_tabclear(elem->argv);
	if (elem->ast)
		free_ast_tree(elem->ast);
	if (elem->in)
		free_redirection_list(elem->in);
	if (elem->out)
		free_redirection_list(elem->out);
	free(elem);
}

void	free_cmds_list(t_cmd *list)
{
	t_cmd	*cursor;

	while (list)
	{
		cursor = list;
		list = list->next;
		free_cmd(cursor);
	}
}

void	add_cmd_elem_in_list(t_cmd **list, t_cmd *elem)
{
	t_cmd	*cursor;

	if (!*list)
	{
		*list = elem;
		return ;
	}
	cursor = *list;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = elem;
}

t_cmd	*create_cmd_elem(size_t nb_argv)
{
	t_cmd	*ret;

	ret = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!ret)
		return (NULL);
	if (nb_argv == 0)
		return (ret);
	ret->argv = (char **)ft_calloc(nb_argv + 1, sizeof(char *));
	if (!ret->argv)
	{
		free_cmd(ret);
		return (NULL);
	}
	return (ret);
}
