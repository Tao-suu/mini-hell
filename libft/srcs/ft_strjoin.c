/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 21:25:35 by picheval          #+#    #+#             */
/*   Updated: 2025/11/14 15:42:12 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	size;

	size = ft_strlen(s1) + ft_strlen(s2);
	ret = ft_strnew(size);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s1, size + 1);
	ft_strlcat(ret, s2, size + 1);
	return (ret);
}
