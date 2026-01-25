/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:50:09 by picheval          #+#    #+#             */
/*   Updated: 2026/01/25 16:59:42 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void free_heredoc(t_heredoc *elem, char even_files)
{
	if (elem->delimiter)
		free(elem->delimiter);
	if (elem->filename)
	{
		if (even_files)
			unlink(elem->filename);
		free(elem->filename);
	}
	free(elem);
}

void	free_heredoc_list(t_heredoc *list, char even_files)
{
	t_heredoc	*cursor;

	while (list)
	{
		cursor = list;
		list = list->next;
		free_heredoc(cursor, even_files);
	}
}

static void	add_heredoc_in_list(t_heredoc **lst, t_heredoc *elem)
{
	t_heredoc	*cursor;

	if (!*lst)
	{
		*lst = elem;
		return ;
	}
	cursor = *lst;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = elem;
}

static size_t	heredoc_lst_size(t_heredoc *lst)
{
	size_t	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

int	manage_heredoc_elem(t_heredoc **lst, t_redirection *redir, char *delimiter)
{
	t_heredoc	*elem;

	elem = (t_heredoc *)ft_calloc(1, sizeof(t_heredoc));
	if (!elem)
		return (FALSE);
	elem->delimiter = ft_strdup(delimiter);
	elem->filename = create_file_name(TMP_FILE_NAME, heredoc_lst_size(*lst));
	if (!elem->delimiter || !elem->filename)
	{
		free_heredoc(elem, TRUE);
		return (print_sys_error("manage_heredoc_elem"));
	}
	add_heredoc_in_list(lst, elem);
	redir->heredoc = elem;
	return (TRUE);
}
