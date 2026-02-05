/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:09:51 by picheval          #+#    #+#             */
/*   Updated: 2026/02/05 10:55:34 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	manage_operator_line(t_operator **list, char *line)
{
	char		**fields;
	t_operator	*tmp;

	fields = ft_split(line, GRAMMAR_FIELD_SEP);
	if (!fields)
		return (print_sys_error("ft_split"));
	tmp = create_operator_elem(fields);
	ft_tabclear(fields);
	if (!tmp)
		return (FALSE);
	add_operator_elem(list, tmp);
	return (TRUE);
}

static int	create_operators_2(t_operator **list)
{
	if (!manage_operator_line(list, "8,IN,<,0,cmd|file|param|AND|OR|PIPE|PO"
			"|PC|START,file")
		|| !manage_operator_line(list, "9,OUT,>,0,cmd|file|param|AND|OR|PIPE"
			"|PO|PC|START,file")
		|| !manage_operator_line(list, "10,PO,(,1,cmd|AND|OR|PIPE|PO|START,"
			"cmd|HEREDOC|APPEND|IN|OUT|PO")
		|| !manage_operator_line(list, "11,PC,),-1,cmd|file|param|PC,AND|OR"
			"|PIPE|HEREDOC|APPEND|IN|OUT|PC|END")
		|| !manage_operator_line(list, "12,START,NULL,0,NULL,cmd|HEREDOC"
			"|APPEND|IN|OUT|PO|END")
		|| !manage_operator_line(list, "13,END,NULL,0,cmd|file|param|PC"
			"|START,NULL")
		|| !manage_operator_line(list, "14,SEMI,;,0,NULL,NULL")
		|| !manage_operator_line(list, "15,ESPER,&,0,NULL,NULL")
		|| !manage_operator_line(list, "16,BANG,!,0,NULL,NULL")
		|| !manage_operator_line(list, "17,COLON,:,0,NULL,NULL"))
		return (FALSE);
	return (TRUE);
}

static int	create_operators_1(t_operator **list)
{
	if (!manage_operator_line(list, "0,cmd,NULL,0,file|AND|OR|PIPE|PO|START,"
			"param|AND|OR|PIPE|HEREDOC|APPEND|IN|OUT|PO|PC|END")
		|| !manage_operator_line(list, "1,param,NULL,0,cmd|param,param|AND|OR"
			"|PIPE|HEREDOC|APPEND|IN|OUT|PC|END")
		|| !manage_operator_line(list, "2,file,NULL,0,HEREDOC|APPEND|IN|OUT,"
			"cmd|AND|OR|PIPE|HEREDOC|APPEND|IN|OUT|PO|PC|END")
		|| !manage_operator_line(list, "3,AND,&&,0,cmd|file|param|PC,"
			"cmd|HEREDOC|APPEND|IN|OUT|PO")
		|| !manage_operator_line(list, "4,OR,||,0,cmd|file|param|PC,"
			"cmd|HEREDOC|APPEND|IN|OUT|PO")
		|| !manage_operator_line(list, "5,PIPE,|,0,cmd|file|param|PC,"
			"cmd|HEREDOC|APPEND|IN|OUT|PO")
		|| !manage_operator_line(list, "6,HEREDOC,<<,0,cmd|file|param|AND"
			"|OR|PIPE|PO|PC|START,file")
		|| !manage_operator_line(list, "7,APPEND,>>,0,cmd|file|param|AND"
			"|OR|PIPE|PO|PC|START,file"))
		return (FALSE);
	return (TRUE);
}

int	create_operators_list(t_operator **list)
{
	if (!create_operators_1(list) || !create_operators_2(list))
		return (FALSE);
	return (TRUE);
}
