/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:03:44 by picheval          #+#    #+#             */
/*   Updated: 2026/01/25 17:10:17 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
