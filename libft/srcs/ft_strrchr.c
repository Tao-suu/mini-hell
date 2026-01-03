/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:37:09 by picheval          #+#    #+#             */
/*   Updated: 2025/11/07 17:00:41 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	if ((char)c == '\0')
		return (&(((char *)s)[ft_strlen(s)]));
	i = ft_strlen(s) - 1;
	while (i >= 0 && s[i] != (char)c)
		i--;
	if (i < 0)
		return (NULL);
	return (&(((char *)s)[i]));
}
