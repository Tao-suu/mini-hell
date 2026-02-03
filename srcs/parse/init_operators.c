/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 18:21:19 by picheval          #+#    #+#             */
/*   Updated: 2026/02/03 02:15:19 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	link_op_deps(t_operator **tab, t_operator ***deps_array,
	char **deps_list)
{
	int			i;

	i = -1;
	while (deps_list[++i])
	{
		(*deps_array)[i] = find_operator_by_name(tab, deps_list[i]);
		if (!((*deps_array)[i]))
		{
			ft_tabclear(deps_list);
			return (print_error("create_op_dep_array / dep not found"));
		}
	}
	ft_tabclear(deps_list);
	return (TRUE);
}

static int	create_op_dep_array(t_operator **tab, t_operator ***deps_array,
	char *tmp_deps)
{
	char	**deps_list;

	if (!tmp_deps)
		return (TRUE);
	deps_list = ft_split(tmp_deps, GRAMMAR_DEP_SEP);
	if (!deps_list)
		return (print_sys_error("create_op_dep_array / ft_split"));
	*deps_array = (t_operator **)ft_calloc(sizeof(t_operator *),
			ft_tablen(deps_list) + 1);
	if (!*deps_array)
	{
		ft_tabclear(deps_list);
		return (print_sys_error("create_op_dep_array / ft_calloc"));
	}
	return (link_op_deps(tab, deps_array, deps_list));
}

static int	manage_operator_deps(t_operator **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		if (!create_op_dep_array(tab, &(tab[i]->before), tab[i]->tmp_before)
			|| !create_op_dep_array(tab, &(tab[i]->after), tab[i]->tmp_after))
			return (FALSE);
	}
	return (TRUE);
}

int	create_operators_array(t_operator ***tab)
{
	t_operator	*list;

	list = NULL;
	if (!create_operators_list(&list))
	{
		free_operator_list(list);
		return (FALSE);
	}
	*tab = create_operator_tab_from_list(list);
	if (!*tab)
	{
		free_operator_list(list);
		return (print_sys_error("create_operator_tab_from_list"));
	}
	if (!manage_operator_deps(*tab))
		return (FALSE);
	return (TRUE);
}
