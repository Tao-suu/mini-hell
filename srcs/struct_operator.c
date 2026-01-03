/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 18:21:25 by picheval          #+#    #+#             */
/*   Updated: 2026/01/03 18:30:21 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_operator_elem(t_operator *elem)
{
	if (elem->name)
		free(elem->name);
	if (elem->value)
		free(elem->value);
	if (elem->tmp_before)
		free(elem->tmp_before);
	if (elem->tmp_after)
		free(elem->tmp_after);
	if (elem->before)
		free(elem->before);
	if (elem->after)
		free(elem->after);
	free(elem);
}

t_operator	*find_operator_by_value(t_operator **tab, char *value)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		if (tab[i]->value && !ft_strncmp(value, tab[i]->value, ft_strlen(tab[i]->value)))
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
		if (tab[i]->name && !ft_strncmp(name, tab[i]->name, ft_strlen(tab[i]->name)))
			return (tab[i]);
	}
	return (NULL);
}

void	free_operator_list(t_operator *list)
{
	t_operator	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free_operator_elem(tmp);
	}
}

void	free_operator_tab(t_operator **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free_operator_elem(tab[i]);
	free(tab);
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
	if (!(ret = (t_operator **)ft_calloc(sizeof(t_operator *), list_size + 1)))
		return (NULL);
	i = -1;
	while (list)
	{
		ret[++i] = list;
		list = list->next;
	}
	return (ret);
}

t_operator	*create_operator_elem(char **fields)
{
	t_operator	*ret;

	if (!fields || ft_tablen(fields) != GRAMMAR_NB_FIELDS)
	{
		print_error("Lexer grammar file: Invalid fields count");
		return (NULL);
	}
	if (!(ret = (t_operator *)ft_calloc(sizeof(t_operator), 1)))
	{
		print_sys_error("create_operator_elem / ft_calloc");
		return (NULL);
	}
	ret->id = atoi(fields[0]);
	if (!(ret->name = ft_strdup(fields[1]))
		|| (ft_strcmp(fields[2], GRAMMAR_NULL) && !(ret->value = ft_strdup(fields[2])))
		|| (ft_strcmp(fields[4], GRAMMAR_NULL) && !(ret->tmp_before = ft_strdup(fields[4])))
		|| (ft_strcmp(fields[5], GRAMMAR_NULL) && !(ret->tmp_after = ft_strdup(fields[5]))))
	{
		free_operator_elem(ret);
		return (NULL);
	}
	ret->lvl_up = atoi(fields[3]);
	return (ret);
}