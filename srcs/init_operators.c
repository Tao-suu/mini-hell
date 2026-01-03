/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 18:21:19 by picheval          #+#    #+#             */
/*   Updated: 2026/01/03 18:27:44 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	manage_operator_line(t_operator **list, char *line)
{
	char		**fields;
	t_operator	*tmp;

	if (line[0] == '#')
		return (TRUE);
	if (!(fields = ft_split(line, GRAMMAR_FIELD_SEP)))
		return (print_sys_error("ft_split"));
	tmp = create_operator_elem(fields);
	ft_tabclear(fields);
	if (!tmp)
		return (FALSE);
	add_operator_elem(list, tmp);
	return (TRUE);
}

// static void	print_deps(t_operator **deps, char *prefix)
// {
// 	int	i;

// 	ft_printf("\t%s:\t", prefix);
// 	if (!deps)
// 	{
// 		ft_printf("NONE\n");
// 		return ;
// 	}
// 	i = -1;
// 	while (deps[++i])
// 	{
// 		if (i > 0)
// 			ft_printf(", ");
// 		ft_printf("%s", deps[i]->name);
// 	}
// 	ft_printf("\n");
// }

// static void	print_operators(t_operator **tab)
// {
// 	int	i;

// 	i = -1;
// 	while (tab[++i])
// 	{
// 		ft_printf("%s%d\t%s\t%s%s\n", CLR_GREEN, tab[i]->id, tab[i]->name, tab[i]->value, CLR_RESET);
// 		print_deps(tab[i]->before, "before");
// 		print_deps(tab[i]->after, "after");
// 	}
// }

static int	create_operator_dep_array(t_operator **tab, t_operator ***deps_array, char *tmp_deps)
{
	char		**deps_list;
	int			i;

	if (!tmp_deps) // operator doesn't have deps
		return (TRUE);
	if (!(deps_list = ft_split(tmp_deps, GRAMMAR_DEP_SEP)))
		return (print_sys_error("create_operator_dep_array / ft_split"));
	if (!(*deps_array = (t_operator **)ft_calloc(sizeof(t_operator *), ft_tablen(deps_list) + 1)))
		return (print_sys_error("create_operator_dep_array / ft_calloc"));
	i = -1;
	while (deps_list[++i])
	{
		if (!((*deps_array)[i] = find_operator_by_name(tab, deps_list[i])))
		{
			ft_tabclear(deps_list);
			free(*deps_array);
			return (print_error("dep not found"));
		}
	}
	ft_tabclear(deps_list);
	return (TRUE);
}

static int	manage_operator_deps(t_operator **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		if (!create_operator_dep_array(tab, &(tab[i]->before), tab[i]->tmp_before)
			|| !create_operator_dep_array(tab, &(tab[i]->after), tab[i]->tmp_after))
			return (FALSE);
	}
	return (TRUE);
}

int	create_operators_array(t_operator ***tab)
{
	t_operator	*list;
	int			fd;
	char		*line;
	int			ret;

	if ((fd = open(GRAMMAR_FILE, O_RDONLY)) < 3)
		return (print_sys_error("open"));
	ret = TRUE;
	list = NULL;
	while ((line = get_next_line(fd, FALSE)))
	{
		ret = manage_operator_line(&list, line);
		free(line);
		if (!ret)
			break ;
	}
	close(fd);
	if (!ret || !(*tab = create_operator_tab_from_list(list))
		|| !manage_operator_deps(*tab))
	{
		free_operator_list(list);
		return (FALSE);
	}
	//print_operators(*tab);
	return (TRUE);
}
