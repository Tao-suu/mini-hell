/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 16:44:42 by picheval          #+#    #+#             */
/*   Updated: 2025/11/28 17:52:11 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nbrcmp(const char *nbr1, const char *nbr2)
{
	size_t	size1;
	size_t	size2;
	int		nbr1_neg;
	int		nbr2_neg;

	nbr1_neg = (nbr1[0] == '-');
	nbr2_neg = (nbr2[0] == '-');
	if (nbr1_neg && !nbr2_neg)
		return (-1);
	if (!nbr1_neg && nbr2_neg)
		return (1);
	size1 = ft_strlen(nbr1);
	size2 = ft_strlen(nbr2);
	if (size1 != size2)
	{
		if (nbr1_neg)
			return (size2 - size1);
		return (size1 - size2);
	}
	if (nbr1_neg)
		return (ft_strncmp(nbr2, nbr1, size1));
	return (ft_strncmp(nbr1, nbr2, size1));
}
