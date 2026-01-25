/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:48:54 by picheval          #+#    #+#             */
/*   Updated: 2026/01/25 18:06:01 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putnbr_base(int value, char *base, char dry)
{
	ssize_t		ret;
	ssize_t		ull_base_ret;
	long long	v;

	v = (long long)value;
	ret = 0;
	if (v < 0)
	{
		v *= -1;
		if (dry == FALSE && ft_putchar('-') < 0)
			return (-1);
		ret++;
	}
	ull_base_ret = ft_putnbr_ull_base((unsigned long long)v, base, dry);
	if (ull_base_ret < 0)
		return (-1);
	return (ret + ull_base_ret);
}
