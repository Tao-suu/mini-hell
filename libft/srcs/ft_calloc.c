/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 13:55:13 by picheval          #+#    #+#             */
/*   Updated: 2025/11/12 17:56:08 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ret;
	size_t	total_size;

	if ((nmemb >= UINT_MAX || size >= UINT_MAX) && ULLONG_MAX / nmemb < size)
		return (NULL);
	total_size = nmemb * size;
	ret = malloc(total_size);
	if (!ret)
		return (NULL);
	ft_bzero(ret, total_size);
	return (ret);
}
