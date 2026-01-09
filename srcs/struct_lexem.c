/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_lexem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 18:34:54 by picheval          #+#    #+#             */
/*   Updated: 2026/01/09 02:32:25 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexem_elem(t_lexem *elem)
{
	if (elem->value)
		free(elem->value);
	free(elem);
}

void	free_lexem_list(t_lexem *list)
{
	t_lexem	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free_lexem_elem(tmp);
	}
}

void	add_lexem_elem(t_lexem **list, t_lexem *elem)
{
	t_lexem	*cursor;

	if (!*list)
	{
		*list = elem;
		return ;
	}
	cursor = *list;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = elem;
	elem->prev = cursor;
}

t_lexem	*create_lexem_elem(void)
{
	t_lexem	*ret;

	ret = (t_lexem *)ft_calloc(sizeof(t_lexem), 1);
	if (!ret)
	{
		print_sys_error("create_lexem_elem / ft_calloc");
		return (NULL);
	}
	return (ret);
}
