/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 23:17:46 by picheval          #+#    #+#             */
/*   Updated: 2026/02/03 02:17:22 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirection(t_redirection *elem)
{
	if (!elem)
		return ;
	if (elem->name)
		free(elem->name);
	if (elem->elements)
		free_cmd_params_list(elem->elements);
	if (elem->expanded_params)
		free_cmd_params_list(elem->expanded_params);
	free(elem);
}

void	free_redirection_list(t_redirection *list)
{
	t_redirection	*cursor;

	while (list)
	{
		cursor = list;
		list = list->next;
		free_redirection(cursor);
	}
}

void	add_redirection_in_list(t_redirection **list, t_redirection *elem)
{
	t_redirection	*cursor;

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

t_redirection	*create_redirection_elem(t_operator *operator, char *name)
{
	t_redirection	*ret;

	ret = (t_redirection *)ft_calloc(1, sizeof(t_redirection));
	if (!ret)
	{
		print_sys_error("malloc");
		return (NULL);
	}
	ret->operator = operator;
	ret->valid_wild = TRUE;
	if (!name)
		return (ret);
	ret->name = ft_strdup(name);
	if (!ret->name)
	{
		free_redirection(ret);
		print_sys_error("ft_strdup");
		return (NULL);
	}
	return (ret);
}
