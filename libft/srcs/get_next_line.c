/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:40:25 by picheval          #+#    #+#             */
/*   Updated: 2025/12/09 16:50:44 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_find_endl(t_file *file, char **line)
{
	size_t	nl_i;
	char	*tmp;

	nl_i = 0;
	if (!file->rest)
		return (0);
	while (file->rest[nl_i] && file->rest[nl_i] != '\n')
		nl_i++;
	if (!file->rest[nl_i])
		return (0);
	*line = ft_submem(file->rest, file->rest_size, 0, nl_i + 1);
	if (!*line)
		return (-1);
	tmp = ft_submem(file->rest, file->rest_size, nl_i + 1,
			file->rest_size - (nl_i + 1));
	if (!tmp)
		return (-1);
	free(file->rest);
	file->rest = tmp;
	file->rest_size -= (nl_i + 1);
	return (1);
}

static int	compute_next_line(t_file *file, char **line)
{
	int		nb_read;
	int		ret;

	while (42)
	{
		ret = check_find_endl(file, line);
		if (ret)
			return (ret);
		if (!ft_realloc(file, BUFFER_SIZE))
			return (-1);
		nb_read = read(file->fd, file->rest + file->rest_size, BUFFER_SIZE);
		if (nb_read < 0)
			return (-1);
		if (nb_read == 0)
		{
			if (file->rest_size)
				*line = ft_submem(file->rest, file->rest_size, 0,
						file->rest_size);
			return (0);
		}
		file->rest_size += nb_read;
	}
}

char	*get_next_line(int fd, int purge)
{
	static t_file	*files = NULL;
	t_file			*file;
	char			*line;
	int				ret;

	line = NULL;
	file = find_or_create_file(&files, fd);
	if (!file)
		return (NULL);
	if (purge)
	{
		remove_file(&files, file);
		return (NULL);
	}
	ret = compute_next_line(file, &line);
	if (ret < 0)
	{
		if (line)
			free(line);
		remove_file(&files, file);
		return (NULL);
	}
	if (ret == 0 && !remove_file(&files, file))
		return (NULL);
	return (line);
}
