/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:59:26 by picheval          #+#    #+#             */
/*   Updated: 2025/11/14 15:41:11 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	size_t	size;

	size = ft_strlen(s);
	ret = ft_strnew(size);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s, size + 1);
	return (ret);
}
