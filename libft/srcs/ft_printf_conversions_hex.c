/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversions_hex.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 15:34:20 by picheval          #+#    #+#             */
/*   Updated: 2025/11/22 12:08:33 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_hex_prefix(int format)
{
	if (format == UPPERCASE)
		ft_putstr(HEX_UPPERCASE_PREFIX);
	else
		ft_putstr(HEX_LOWERCASE_PREFIX);
	return (2);
}

void	print_pointer(t_printf_env *e)
{
	void				*p;
	unsigned long long	v;
	size_t				p_size;

	p = va_arg(e->ap, void *);
	v = (unsigned long long)p;
	p_size = 5;
	if (p)
		p_size = 2 + ft_putnbr_ull_base(v, BASE16_LOWERCASE, TRUE);
	e->ret += add_padding(e->param, p_size, TRUE);
	if (!p)
		e->ret += ft_putstr("(nil)");
	else
		e->ret += print_hex_prefix(LOWERCASE)
			+ ft_putnbr_ull_base(v, BASE16_LOWERCASE, FALSE);
	e->ret += add_padding(e->param, p_size, FALSE);
}

static void	print_hex(t_printf_env *e, char *base)
{
	unsigned int		x;
	unsigned long long	u;
	size_t				u_size;
	int					prefix_size;

	x = va_arg(e->ap, unsigned int);
	u = (unsigned long long)x;
	u_size = 0;
	if (u != 0 || e->param.dot != 0)
		u_size = ft_putnbr_ull_base(u, base, TRUE);
	prefix_size = add_number_prefix(e->param, u_size, x != 0);
	if (u != 0 || e->param.dot != 0)
		e->ret += ft_putnbr_ull_base(u, base, FALSE);
	e->ret += prefix_size + add_number_suffix(e->param, prefix_size + u_size);
}

void	print_hex_lowercase(t_printf_env *e)
{
	print_hex(e, BASE16_LOWERCASE);
}

void	print_hex_uppercase(t_printf_env *e)
{
	print_hex(e, BASE16_UPPERCASE);
}
