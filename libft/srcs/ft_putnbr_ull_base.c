/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ull_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:48:54 by picheval          #+#    #+#             */
/*   Updated: 2025/11/17 15:16:28 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnbr_ull_base(unsigned long long value, char *base, char dry)
{
	size_t	base_size;
	size_t	ret;

	base_size = ft_strlen(base);
	ret = 0;
	if (value < base_size)
	{
		if (dry == FALSE)
			ft_putchar((char)base[value]);
		return (1);
	}
	ret += ft_putnbr_ull_base(value / base_size, base, dry);
	ret += ft_putnbr_ull_base(value % base_size, base, dry);
	return (ret);
}
