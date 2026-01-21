/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 18:21:19 by picheval          #+#    #+#             */
/*   Updated: 2026/01/21 02:41:51 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	manage_operator_line(t_operator **list, char *line)
{
	char		**fields;
	t_operator	*tmp;
	size_t		line_size;

	line_size = ft_strlen(line);
	if (line_size > 0 && line[line_size - 1] == '\n')
		line[line_size - 1] = '\0';
	if (!line[0] || line[0] == '#')
		return (TRUE);
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

static int	create_op_dep_array(t_operator **tab, t_operator ***deps_array,
	char *tmp_deps)
{
	char		**deps_list;
	int			i;

	if (!tmp_deps)
		return (TRUE);
	deps_list = ft_split(tmp_deps, GRAMMAR_DEP_SEP);
	if (!deps_list)
		return (print_sys_error("create_op_dep_array / ft_split"));
	*deps_array = (t_operator **)ft_calloc(sizeof(t_operator *),
			ft_tablen(deps_list) + 1);
	if (!deps_array)
		return (print_sys_error("create_op_dep_array / ft_calloc"));
	i = -1;
	while (deps_list[++i])
	{
		(*deps_array)[i] = find_operator_by_name(tab, deps_list[i]);
		if (!((*deps_array)[i]))
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
		if (!create_op_dep_array(tab, &(tab[i]->before), tab[i]->tmp_before)
			|| !create_op_dep_array(tab, &(tab[i]->after), tab[i]->tmp_after))
			return (FALSE);
	}
	return (TRUE);
}

static int	manage_operators_array(t_operator ***tab, t_operator *list, int ret)
{
	if (!ret)
	{
		free_operator_list(list);
		return (FALSE);
	}
	*tab = create_operator_tab_from_list(list);
	if (!*tab || !manage_operator_deps(*tab))
	{
		free_operator_list(list);
		return (FALSE);
	}
	//print_operators(*tab);
	return (TRUE);
}

int	create_operators_array(t_operator ***tab)
{
	t_operator	*list;
	int			fd;
	char		*line;
	int			ret;

	fd = open(GRAMMAR_FILE, O_RDONLY);
	if (fd < 3)
		return (print_sys_error("grammar open"));
	ret = TRUE;
	list = NULL;
	while (42)
	{
		line = get_next_line(fd, FALSE);
		if (!line)
			break ;
		ret = manage_operator_line(&list, line);
		free(line);
		if (ret == TRUE)
			continue ;
		get_next_line(fd, TRUE);
		break ;
	}
	close(fd);
	return (manage_operators_array(tab, list, ret));
}
