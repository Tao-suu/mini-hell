/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:01:48 by picheval          #+#    #+#             */
/*   Updated: 2026/01/14 13:10:11 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_printf_env(t_printf_env *e)
{
	va_end(e->ap);
}

static void	init_conv_function(t_printf_env *e)
{
	int		i;

	i = -1;
	e->conv_function[++i] = print_character;
	e->conv_function[++i] = print_string;
	e->conv_function[++i] = print_pointer;
	e->conv_function[++i] = print_decimal;
	e->conv_function[++i] = print_decimal;
	e->conv_function[++i] = print_unsigned_decimal;
	e->conv_function[++i] = print_hex_lowercase;
	e->conv_function[++i] = print_hex_uppercase;
	e->conv_function[++i] = print_percent;
}

void	init_printf_env(t_printf_env *e, const char *str)
{
	ft_memset((void *)e, 0, sizeof(t_printf_env));
	e->str = str;
	e->str_i = 0;
	e->ret = 0;
	init_conv_function(e);
}
