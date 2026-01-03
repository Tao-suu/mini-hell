/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:01:48 by picheval          #+#    #+#             */
/*   Updated: 2025/11/22 12:08:47 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_printf_env(t_printf_env *e)
{
	va_end(e->ap);
	free(e);
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

t_printf_env	*init_printf_env(const char *str)
{
	t_printf_env	*e;

	e = (t_printf_env *)malloc(sizeof(t_printf_env));
	if (!e)
		return (NULL);
	e->str = str;
	e->str_i = 0;
	e->ret = 0;
	init_conv_function(e);
	return (e);
}
