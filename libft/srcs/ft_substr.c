/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:15:02 by picheval          #+#    #+#             */
/*   Updated: 2025/11/14 15:41:42 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	ret_size;
	size_t	s_size;

	s_size = ft_strlen(s);
	if (start < 0 || start >= s_size || len == 0)
		ret_size = 0;
	else
	{
		ret_size = len;
		if (start + len > s_size)
			ret_size = s_size - start;
	}
	ret = ft_strnew(ret_size);
	if (!ret)
		return (NULL);
	if (ret_size)
		ft_strlcpy(ret, s + start, ret_size + 1);
	return (ret);
}
