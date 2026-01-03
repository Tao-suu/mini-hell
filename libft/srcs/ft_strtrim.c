/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 21:43:12 by picheval          #+#    #+#             */
/*   Updated: 2025/11/11 20:48:52 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	find_start(char const *s1, char const *set)
{
	unsigned int	i;

	i = -1;
	while (s1[++i])
		if (!ft_strchr(set, s1[i]))
			break ;
	return (i);
}

static unsigned int	find_end(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1);
	while (--i >= 0)
		if (!ft_strchr(set, s1[i]))
			break ;
	return ((unsigned int)i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	size_t			len;

	if (ft_strlen(s1) == 0 || ft_strlen(set) == 0)
		return (ft_strdup(s1));
	start = find_start(s1, set);
	end = find_end(s1, set);
	if (end < start)
		return (ft_strdup(""));
	len = (size_t)(end - start) + 1;
	return (ft_substr(s1, start, len));
}
