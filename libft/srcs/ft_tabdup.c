/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:20:22 by picheval          #+#    #+#             */
/*   Updated: 2026/01/08 18:22:38 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **tab, size_t extra_space)
{
	char	**ret;
	size_t	size;
	size_t	i;

	size = 0;
	if (tab)
		size = ft_tablen(tab);
	ret = (char **)ft_calloc(size + extra_space + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		ret[i] = ft_strdup(tab[i]);
		if (!ret[i])
		{
			ft_tabclear(ret);
			return (NULL);
		}
	}
	return (ret);
}
