/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:37:13 by picheval          #+#    #+#             */
/*   Updated: 2026/02/03 02:16:41 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_non_null_lst_elem(t_list *lst)
{
	int	ret;

	ret = 0;
	while (lst)
	{
		if (lst->content)
			ret++;
		lst = lst->next;
	}
	return (ret);
}

char	**create_tab_from_lst(t_list *lst)
{
	t_list	*tmp;
	char	**ret;
	int		i;

	ret = (char **)ft_calloc(count_non_null_lst_elem(lst) + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (lst)
	{
		tmp = lst;
		if (tmp->content)
			ret[i++] = tmp->content;
		lst = lst->next;
		free(tmp);
	}
	return (ret);
}

int	create_lst_empty(t_list **lst)
{
	t_list	*elem;

	elem = ft_lstnew(NULL);
	if (!elem)
		return (FALSE);
	ft_lstadd_back(lst, elem);
	return (TRUE);
}

int	lst_add_or_join_back(t_list **lst, char *value)
{
	t_list	*last;
	char	*tmp;

	last = ft_lstlast(*lst);
	if (!last->content)
	{
		last->content = value;
		return (TRUE);
	}
	tmp = last->content;
	last->content = ft_strjoin(tmp, value);
	free(tmp);
	free(value);
	if (!last->content)
		return (print_sys_error("lst_add_or_join_back ft_strjoin"));
	return (TRUE);
}
