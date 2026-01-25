/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:51:01 by picheval          #+#    #+#             */
/*   Updated: 2026/01/25 17:58:54 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	add_padding_character(char c, ssize_t size)
{
	ssize_t	i;

	i = -1;
	while (++i < size)
		ft_putchar(c);
	return (i);
}

int	add_number_suffix(t_printf_param p, ssize_t size)
{
	if (p.minus == FALSE || p.min_width < 0 || (ssize_t)p.min_width <= size)
		return (0);
	return (add_padding_character(' ', (p.min_width - size)));
}

static ssize_t	add_number_sign(t_printf_param p, char sign, char dry)
{
	if (sign >= 0 && p.plus == FALSE && p.space == FALSE && p.hashtag == FALSE)
		return (0);
	if (p.hashtag == TRUE)
	{
		if (sign == 0)
			return (0);
		if (dry == FALSE && p.conversion == 'x')
			ft_putstr("0x");
		else if (dry == FALSE && p.conversion == 'X')
			ft_putstr("0X");
		return (2);
	}
	if (dry == FALSE && sign < 0)
		ft_putchar('-');
	else if (dry == FALSE && p.plus == TRUE)
		ft_putchar('+');
	else if (dry == FALSE && p.space == TRUE)
		ft_putchar(' ');
	return (1);
}

int	add_number_prefix(t_printf_param p, ssize_t size, char sign)
{
	ssize_t	precision;
	ssize_t	min_width;
	ssize_t	sign_size;
	int		ret;

	ret = 0;
	sign_size = add_number_sign(p, sign, TRUE);
	precision = 0;
	if (p.dot > -1 && (ssize_t)p.dot > size)
		precision = (ssize_t)p.dot - size;
	min_width = 0;
	if (p.min_width > -1 && (ssize_t)p.min_width > size + sign_size + precision)
		min_width = (ssize_t)p.min_width - size - sign_size - precision;
	if ((p.zero == FALSE && p.minus == FALSE)
		|| (p.zero == TRUE && p.dot > -1 && p.min_width > p.dot))
		ret += add_padding_character(' ', min_width);
	ret += add_number_sign(p, sign, FALSE);
	if (p.zero == TRUE && p.dot < 0)
		ret += add_padding_character('0', min_width);
	ret += add_padding_character('0', precision);
	return (ret);
}

int	add_padding(t_printf_param p, ssize_t size, char before)
{
	char	c;

	if ((before == TRUE && p.minus == TRUE)
		|| (before == FALSE && p.minus == FALSE)
		|| p.min_width < 0)
		return (0);
	c = ' ';
	if ((ssize_t)p.min_width <= size)
		return (0);
	return (add_padding_character(c, (ssize_t)p.min_width - size));
}
