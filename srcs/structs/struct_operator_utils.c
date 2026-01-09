/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_operator_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 02:04:38 by picheval          #+#    #+#             */
/*   Updated: 2026/01/09 02:06:55 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_operator	*find_operator_by_value(t_operator **tab, char *value)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		if (tab[i]->value
			&& !ft_strncmp(value, tab[i]->value, ft_strlen(tab[i]->value)))
			return (tab[i]);
	}
	return (NULL);
}

t_operator	*find_operator_by_name(t_operator **tab, char *name)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		if (tab[i]->name
			&& !ft_strncmp(name, tab[i]->name, ft_strlen(tab[i]->name)))
			return (tab[i]);
	}
	return (NULL);
}

void	add_operator_elem(t_operator **list, t_operator *elem)
{
	t_operator	*cursor;

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

static int	compute_operator_list_size(t_operator *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

t_operator	**create_operator_tab_from_list(t_operator *list)
{
	t_operator	**ret;
	int			list_size;
	int			i;

	list_size = compute_operator_list_size(list);
	ret = (t_operator **)ft_calloc(sizeof(t_operator *), list_size + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (list)
	{
		ret[++i] = list;
		list = list->next;
	}
	return (ret);
}
