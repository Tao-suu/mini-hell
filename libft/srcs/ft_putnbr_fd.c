/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:25:54 by picheval          #+#    #+#             */
/*   Updated: 2025/11/16 22:08:40 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putnbr_fd(int n, int fd)
{
	size_t	ret;

	ret = 0;
	if (n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
		ret++;
	}
	if (n >= 10)
	{
		ret += ft_putnbr_fd(n / 10, fd);
		ret += ft_putnbr_fd(n % 10, fd);
		return (ret);
	}
	ft_putchar_fd(n + '0', fd);
	return (ret + 1);
}
