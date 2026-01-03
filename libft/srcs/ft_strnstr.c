/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 19:09:24 by picheval          #+#    #+#             */
/*   Updated: 2025/11/07 19:39:19 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *)big);
	i = 0;
	while (42)
	{
		while (i < len && big[i] && big[i] != little[0])
			i++;
		j = 0;
		while (i + j < len && big[i + j] && big[i + j] == little[j])
			j++;
		if (j == little_len)
			return (&(((char *)big)[i]));
		if (i == len || !big[i])
			break ;
		i++;
	}
	return (NULL);
}
