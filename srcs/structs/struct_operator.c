/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 18:21:25 by picheval          #+#    #+#             */
/*   Updated: 2026/01/30 16:37:24 by picheval         ###   ########.fr       */
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

static int	create_operator_field(char **value, char *field)
{
	if (!ft_strcmp(field, GRAMMAR_NULL))
		return (TRUE);
	*value = ft_strdup(field);
	if (!*value)
		return (print_sys_error("create_operator_field ft_strdup"));
	return (TRUE);
}

t_operator	*create_operator_elem(char **fields)
{
	t_operator	*ret;

	if (!fields || ft_tablen(fields) != GRAMMAR_NB_FIELDS)
	{
		print_error("Lexer grammar: Invalid fields count");
		return (NULL);
	}
	ret = (t_operator *)ft_calloc(sizeof(t_operator), 1);
	if (!ret)
	{
		print_sys_error("create_operator_elem / ft_calloc");
		return (NULL);
	}
	if (!create_operator_field(&(ret->name), fields[1])
		|| !create_operator_field(&(ret->value), fields[2])
		|| !create_operator_field(&(ret->tmp_before), fields[4])
		|| !create_operator_field(&(ret->tmp_after), fields[5]))
	{
		free_operator_elem(ret);
		return (NULL);
	}
	ret->id = atoi(fields[0]);
	ret->lvl_up = atoi(fields[3]);
	return (ret);
}
