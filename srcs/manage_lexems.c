/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lexems.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:31:41 by picheval          #+#    #+#             */
/*   Updated: 2026/01/07 06:25:18 by tbez--du         ###   ########.fr       */
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
		return (print_error("Manage lexem: No before in elem"));
	if (!(find_operator_by_name(elem->type->before, op_name)))
		return (print_syntax_error(elem->value));
	return (TRUE);
}

static int	check_if_elem_can_be_last(t_lexem *elem)
{
	if (!elem->type->after)
		return (print_error("Manage lexem: No after in elem"));
	if (!(find_operator_by_name(elem->type->after, OP_END)))
		return (print_syntax_error("newline"));
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
		// If a closed parenthesis has not been previously opened
		if (lvl < 0)
			return (print_syntax_error(elem->value));
		// WTF this case seems stupid "ls (cat)" => "syntax error near 'cat'""
		// Is there a case where "cmd (something)" is valid ?
		if (!ft_strcmp(elem->type->name, "PO") && elem->next
			&& elem_prev && !ft_strcmp(elem_prev->type->name, "cmd"))
			return (print_syntax_error(elem->next->value));
		elem->lvl = lvl;
		if (elem->type->lvl_up <= 0)
			elem->lvl += elem->type->lvl_up;
		//print_tabs(elem->lvl);
//		ft_printf("%s%s%s\t%d (%s)\n", CLR_GREEN, elem->value, CLR_RESET, elem->lvl, elem->type->name);
		lvl = elem->lvl;
		if (elem->type->lvl_up > 0)
			lvl += elem->type->lvl_up;
		elem_prev = elem;
		elem = elem->next;
	}
	if (elem_prev && !check_if_elem_can_be_last(elem_prev))
		return (FALSE);
	// If some opened parenthesis are not closed
	// TODO: better error message ?
	if (lvl != 0)
		return (print_matching_error());
		// return (print_bash_error("unclosed parenthesis"));
	return (TRUE);
}
