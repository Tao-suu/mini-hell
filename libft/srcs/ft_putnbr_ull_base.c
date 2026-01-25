/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ull_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:48:54 by picheval          #+#    #+#             */
/*   Updated: 2026/01/25 18:17:25 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putnbr_ull_base(unsigned long long value, char *base, char dry)
{
	size_t	base_size;
	ssize_t	ret;
	ssize_t	ret2;

	base_size = ft_strlen(base);
	ret = 0;
	if (value < base_size)
	{
		if (dry == FALSE && ft_putchar((char)base[value]) < 0)
			return (-1);
		return (1);
	}
	ret2 = ft_putnbr_ull_base(value / base_size, base, dry);
	if (ret2 < 0)
		return (-1);
	ret += ret2;
	ret2 = ft_putnbr_ull_base(value % base_size, base, dry);
	if (ret2 < 0)
		return (-1);
	ret += ret2;
	return (ret);
}
