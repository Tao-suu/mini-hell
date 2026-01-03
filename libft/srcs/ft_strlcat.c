/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:06:38 by picheval          #+#    #+#             */
/*   Updated: 2025/11/08 19:44:35 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	dst_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	if (siz <= dst_len)
		return (ft_strlen(src) + siz);
	i = -1;
	while (dst_len + ++i < siz - 1 && src[i])
		dst[dst_len + i] = src[i];
	dst[dst_len + i] = '\0';
	return (ft_strlen(src) + dst_len);
}
