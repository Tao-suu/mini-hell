/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 21:33:55 by picheval          #+#    #+#             */
/*   Updated: 2025/11/26 21:57:07 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	compute_size(char **tab, char *sep)
{
	size_t	size;
	int		i;

	size = 0;
	i = -1;
	while (tab[++i])
		size += ft_strlen(tab[i]);
	size += ft_strlen(sep) * (i - 1);
	return (size);
}

char	*ft_tabjoin(char **tab, char *sep)
{
	char	*ret;
	size_t	size;
	int		i;

	size = compute_size(tab, sep);
	ret = ft_strnew(size);
	if (!ret)
		return (NULL);
	i = -1;
	while (tab[++i])
	{
		if (i > 0)
			ft_strlcat(ret, sep, size + 1);
		ft_strlcat(ret, tab[i], size + 1);
	}
	return (ret);
}
