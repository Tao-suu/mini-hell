/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 10:41:31 by picheval          #+#    #+#             */
/*   Updated: 2025/11/14 16:30:37 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	compute_size(long long tmp)
{
	size_t	size;

	if (tmp == 0)
		return (1);
	size = 0;
	if (tmp < 0)
	{
		tmp *= -1;
		size++;
	}
	while (tmp)
	{
		tmp /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char		*ret;
	size_t		size;
	long long	tmp;

	tmp = (long long)n;
	size = compute_size(tmp);
	ret = ft_strnew(size);
	if (!ret)
		return (NULL);
	if (tmp < 0)
	{
		ret[0] = '-';
		tmp *= -1;
	}
	if (tmp == 0)
		ret[0] = '0';
	while (tmp)
	{
		ret[--size] = (tmp % 10) + '0';
		tmp /= 10;
	}
	return (ret);
}
