/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cmd_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 22:19:46 by picheval          #+#    #+#             */
/*   Updated: 2026/02/02 10:39:55 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_param(t_cmd_param *elem)
{
	if (!elem)
		return ;
	if (elem->original_value)
		free(elem->original_value);
	if (elem->expanded_value)
		free(elem->expanded_value);
	if (elem->elements)
		free_cmd_params_list(elem->elements);
	free(elem);
}

void	free_cmd_params_list(t_cmd_param *list)
{
	t_cmd_param	*cursor;

	while (list)
	{
		cursor = list;
		list = list->next;
		free_cmd_param(cursor);
	}
}

static void	add_cmd_param_elem_in_list(t_cmd_param **list, t_cmd_param *elem)
{
	t_cmd_param	*cursor;

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

static t_cmd_param	*create_cmd_param_elem(char *value, char quote)
{
	t_cmd_param	*ret;

	ret = (t_cmd_param *)ft_calloc(1, sizeof(t_cmd_param));
	if (!ret)
		return (NULL);
	ret->original_value = value;
	if (quote == -1)
		ret->state = PARAM_NONE;
	else if (quote == '"')
		ret->state = PARAM_DQUOTED;
	else if (quote == '\'')
		ret->state = PARAM_SQUOTED;
	else
		ret->state = PARAM_UQUOTED;
	return (ret);
}

int	new_cmd_param(t_cmd_param **param_elems, char *original, char *expanded,
	char quote)
{
	t_cmd_param	*elem;

	if (!original)
	{
		if (expanded)
			free(expanded);
		return (print_sys_error("new_cmd_param original"));
	}
	elem = create_cmd_param_elem(original, quote);
	if (!elem)
	{
		free(original);
		if (expanded)
			free(expanded);
		return (print_sys_error("new_cmd_param create_cmd_param_elem"));
	}
	elem->expanded_value = expanded;
	add_cmd_param_elem_in_list(param_elems, elem);
	return (TRUE);
}
