/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:48:54 by picheval          #+#    #+#             */
/*   Updated: 2025/11/17 15:16:00 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnbr_base(int value, char *base, char dry)
{
	size_t		ret;
	long long	v;

	v = (long long)value;
	ret = 0;
	if (v < 0)
	{
		v *= -1;
		if (dry == FALSE)
			ft_putchar('-');
		ret++;
	}
	return (ret + ft_putnbr_ull_base((unsigned long long)v, base, dry));
}
