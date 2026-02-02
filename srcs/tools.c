/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:03:44 by picheval          #+#    #+#             */
/*   Updated: 2026/02/02 08:06:02 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strjoin_free(char **dst, char *elem)
{
	char	*old;

	if (!elem)
		return (print_sys_error("strjoin_free elem"));
	if (!*dst)
	{
		*dst = ft_strdup(elem);
		free(elem);
		if (!*dst)
			return (print_sys_error("strjoin_free ft_strdup"));
		return (TRUE);
	}
	old = *dst;
	*dst = ft_strjoin(*dst, elem);
	free(old);
	free(elem);
	if (!*dst)
		return (print_sys_error("strjoin_free ft_strjoin"));
	return (TRUE);
}

int	merge_with_sep(char **ret, char *str1, char *str2, char *sep)
{
	size_t	size;

	size = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(sep) + 1;
	*ret = (char *)ft_calloc(size, sizeof(char));
	if (!*ret)
		return (print_sys_error("merge_with_sep ft_calloc"));
	ft_strlcpy(*ret, str1, size);
	ft_strlcat(*ret, sep, size);
	ft_strlcat(*ret, str2, size);
	return (TRUE);
}

static size_t	compute_number_size(size_t tmp)
{
	size_t	size;

	if (tmp == 0)
		return (1);
	size = 0;
	while (tmp)
	{
		tmp /= 10;
		size++;
	}
	return (size);
}

char	*create_file_name(char *base_file_name, size_t number)
{
	int		name_size;
	int		nbr_size;
	char	*ret;

	name_size = ft_strlen(base_file_name);
	nbr_size = compute_number_size(number);
	ret = ft_calloc(sizeof(char), name_size + nbr_size + 1);
	if (!ret)
		return (NULL);
	ret[name_size + nbr_size] = '\0';
	while (nbr_size--)
	{
		ret[name_size + nbr_size] = (number % 10) + '0';
		number /= 10;
	}
	while (name_size--)
		ret[name_size] = base_file_name[name_size];
	return (ret);
}
