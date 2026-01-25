/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lexems.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:31:41 by picheval          #+#    #+#             */
/*   Updated: 2026/01/25 21:34:58 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_if_elem_can_be_after_prev(t_lexem *elem)
{
	char		*op_name;

	op_name = OP_START;
	if (elem->prev)
		op_name = elem->prev->type->name;
	if (!elem->type->before)
		return (print_syntax_error(elem->value));
	if (!(find_operator_by_name(elem->type->before, op_name)))
		return (print_syntax_error(elem->value));
	return (TRUE);
}

static int	check_if_elem_can_be_last(t_lexem *elem)
{
	if (!elem->type->after)
		return (print_syntax_error("newline"));
	if (!(find_operator_by_name(elem->type->after, OP_END)))
		return (print_syntax_error("newline"));
	return (TRUE);
}

static int	apply_level_and_print(t_lexem *elem, int *lvl)
{
	elem->lvl = *lvl;
	if (elem->type->lvl_up <= 0)
		elem->lvl += elem->type->lvl_up;
	*lvl = elem->lvl;
	if (elem->type->lvl_up > 0)
		*lvl += elem->type->lvl_up;
	if (*lvl < 0)
		return (print_syntax_error(elem->value));
	return (TRUE);
}

int	manage_lexems(t_data *data)
{
	t_lexem	*elem;
	t_lexem	*elem_prev;
	int		lvl;

	elem = data->head;
	lvl = 0;
	elem_prev = NULL;
	while (elem)
	{
		if (!check_if_elem_can_be_after_prev(elem))
			return (FALSE);
		// WTF this case seems stupid "ls (cat)" => "syntax error near 'cat'""
		// Is there a case where "cmd (something)" is valid ?
		if (!ft_strcmp(elem->type->name, "PO") && elem->next
			&& elem_prev && !ft_strcmp(elem_prev->type->name, "cmd"))
			return (print_syntax_error(elem->next->value));
		if (!apply_level_and_print(elem, &lvl))
			return (FALSE);
		elem_prev = elem;
		elem = elem->next;
	}
	if (elem_prev && !check_if_elem_can_be_last(elem_prev))
		return (FALSE);
	if (lvl != 0)
		return (print_matching_error(')'));
	return (TRUE);
}
