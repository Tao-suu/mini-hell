/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:25:54 by picheval          #+#    #+#             */
/*   Updated: 2026/01/25 18:17:05 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	manage_value(int fd, int *n, ssize_t *ret)
{
	if (*n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	if (*n < 0)
	{
		if (ft_putchar_fd('-', fd) < 0)
			return (-1);
		*n *= -1;
		(*ret)++;
	}
	return (0);
}

ssize_t	ft_putnbr_fd(int n, int fd)
{
	ssize_t	ret;
	ssize_t	ret2;

	ret = 0;
	ret2 = manage_value(fd, &n, &ret);
	if (ret2 != 0)
		return (ret);
	if (n >= 10)
	{
		ret2 = ft_putnbr_fd(n / 10, fd);
		if (ret2 < 0)
			return (-1);
		ret += ret2;
		ret2 = ft_putnbr_fd(n % 10, fd);
		if (ret2 < 0)
			return (-1);
		ret += ret2;
		return (ret);
	}
	if (ft_putchar_fd(n + '0', fd) < 0)
		return (-1);
	return (ret + 1);
}
