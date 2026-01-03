/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_lexems.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 16:31:41 by picheval          #+#    #+#             */
/*   Updated: 2026/01/03 18:36:26 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_if_elem_can_be_after_prev(t_lexem *elem)
{
	t_operator	*start;
	char		*op_name;

	op_name = OP_START;
	if (elem->prev)
		op_name = elem->prev->type->name;
	if (!elem->type->before)
		return (print_error("Manage lexem: No before in elem"));
	if (!(start = find_operator_by_name(elem->type->before, op_name)))
		return (print_syntax_error(elem->value));
	return (TRUE);
}

static int	check_if_elem_can_be_last(t_lexem *elem)
{
	t_operator	*end;

	if (!elem->type->after)
		return (print_error("Manage lexem: No after in elem"));
	if (!(end = find_operator_by_name(elem->type->after, OP_END)))
		return (print_syntax_error("newline"));
	return (TRUE);
}

int	manage_lexems(t_data *data)
{
	t_lexem	*elem;
	t_lexem	*elem_prev;
	int		lvl;
	int		i;

	elem = data->head;
	lvl = 0;
	elem_prev = NULL;
	while (elem)
	{
		if (!check_if_elem_can_be_after_prev(elem))
			return (FALSE);
		lvl += elem->type->lvl_up;
		// If a closed parenthesis has not been previously opened
		if (lvl < 0)
			return (print_syntax_error(elem->value));
		// WTF this case seems stupid "ls (cat)" => "syntax error near 'cat'""
		// Is there a case where "cmd (something)" is valid ?
		if (!ft_strcmp(elem->type->name, "PO") && elem->next
			&& elem_prev && !ft_strcmp(elem_prev->type->name, "cmd"))
			return (print_syntax_error(elem->next->value));
		elem->lvl = lvl;
		i = -1;
		while (++i < lvl)
			printf("\t");
		printf("\t%s%s%s\t(%s)\n", CLR_GREEN, elem->value, CLR_RESET, elem->type->name);
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
