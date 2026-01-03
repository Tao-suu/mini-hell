/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:08:18 by picheval          #+#    #+#             */
/*   Updated: 2025/11/22 12:08:08 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_character(t_printf_env *e)
{
	char	c;

	c = (char)va_arg(e->ap, int);
	e->ret += add_padding(e->param, 1, TRUE);
	ft_putchar(c);
	e->ret++;
	e->ret += add_padding(e->param, 1, FALSE);
}

void	print_string(t_printf_env *e)
{
	char	*s;
	size_t	s_size;

	s = va_arg(e->ap, char *);
	s_size = 6;
	if (s)
		s_size = ft_strlen(s);
	if (e->param.dot > -1)
	{
		if (!s && e->param.dot < 6)
			s_size = 0;
		else if (s && (size_t)e->param.dot < s_size)
			s_size = e->param.dot;
	}
	e->ret += add_padding(e->param, s_size, TRUE);
	if (!s && s_size >= 6)
		e->ret += write(1, "(null)", s_size);
	else if (s)
		e->ret += write(1, s, s_size);
	e->ret += add_padding(e->param, s_size, FALSE);
}

void	print_decimal(t_printf_env *e)
{
	int					d;
	unsigned long long	u;
	size_t				u_size;
	char				sign;
	int					prefix_size;

	d = va_arg(e->ap, int);
	sign = 0;
	u = (unsigned long long)d;
	if (d < 0)
	{
		u = (unsigned long long)((long long)d * -1);
		sign = -1;
	}
	else if (d > 0)
		sign = 1;
	u_size = 0;
	if (u != 0 || e->param.dot != 0)
		u_size = ft_putnbr_ull_base((unsigned long long)u, BASE10, TRUE);
	prefix_size = add_number_prefix(e->param, u_size, sign);
	if (u != 0 || e->param.dot != 0)
		e->ret += ft_putnbr_ull_base((unsigned long long)u, BASE10, FALSE);
	e->ret += prefix_size + add_number_suffix(e->param, prefix_size + u_size);
}

void	print_unsigned_decimal(t_printf_env *e)
{
	unsigned int	u;
	size_t			u_size;
	int				sign;
	int				prefix_size;

	u = va_arg(e->ap, unsigned int);
	sign = 0;
	if (u > 0)
		sign = 1;
	u_size = 0;
	if (u != 0 || e->param.dot != 0)
		u_size = ft_putnbr_ull_base((unsigned long long)u, BASE10, TRUE);
	prefix_size = add_number_prefix(e->param, u_size, sign);
	if (u != 0 || e->param.dot != 0)
		e->ret += ft_putnbr_ull_base((unsigned long long)u, BASE10, FALSE);
	e->ret += prefix_size + add_number_suffix(e->param, prefix_size + u_size);
}

void	print_percent(t_printf_env *e)
{
	ft_putchar('%');
	e->ret++;
}
