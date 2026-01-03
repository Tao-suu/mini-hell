/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:40:44 by picheval          #+#    #+#             */
/*   Updated: 2025/12/09 16:25:56 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	remove_file(t_file **files, t_file *file)
{
	t_file	*cursor;
	t_file	*tmp;

	if (file->rest)
		free(file->rest);
	if (*files == file)
	{
		tmp = file;
		*files = file->next;
		free(tmp);
		return (1);
	}
	cursor = *files;
	while (cursor->next && cursor->next != file)
		cursor = cursor->next;
	if (!cursor->next)
		return (0);
	tmp = cursor->next;
	cursor->next = cursor->next->next;
	free(tmp);
	return (1);
}

static t_file	*create_and_add_file(t_file **files, int fd)
{
	t_file	*cursor;
	t_file	*new;

	new = (t_file *)malloc(sizeof(t_file));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->rest = NULL;
	new->rest_size = 0;
	new->next = NULL;
	if (!*files)
	{
		*files = new;
		return (new);
	}
	cursor = *files;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = new;
	return (new);
}

t_file	*find_or_create_file(t_file **files, int fd)
{
	t_file	*cursor;

	cursor = *files;
	while (cursor)
	{
		if (cursor->fd == fd)
			return (cursor);
		cursor = cursor->next;
	}
	return (create_and_add_file(files, fd));
}

char	*ft_submem(char const *s, size_t s_size, unsigned int start,
	size_t len)
{
	char	*ret;
	size_t	ret_size;
	size_t	i;

	if (start >= s_size || len == 0)
		ret_size = 0;
	else
	{
		ret_size = len;
		if (start + len > s_size)
			ret_size = s_size - start;
	}
	ret = (char *)malloc(sizeof(char) * (ret_size + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < ret_size)
		ret[i] = s[start + i];
	ret[i] = '\0';
	return (ret);
}

int	ft_realloc(t_file *file, int size_up)
{
	char	*new;
	size_t	new_size;
	size_t	i;

	new_size = file->rest_size + size_up + 1;
	new = (char *)malloc(sizeof(char) * new_size);
	if (!new)
		return (0);
	i = -1;
	while (++i < file->rest_size)
		new[i] = file->rest[i];
	while (i < new_size)
		new[i++] = '\0';
	if (file->rest)
		free(file->rest);
	file->rest = new;
	return (1);
}
