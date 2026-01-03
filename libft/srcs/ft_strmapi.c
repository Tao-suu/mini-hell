/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 11:23:57 by picheval          #+#    #+#             */
/*   Updated: 2025/11/14 16:30:23 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ret;
	size_t			size;
	unsigned int	i;

	size = ft_strlen(s);
	ret = ft_strnew(size);
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < size)
		ret[i] = f(i, s[i]);
	return (ret);
}
