/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 16:39:29 by picheval          #+#    #+#             */
/*   Updated: 2026/01/14 13:10:37 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_conv_function(char c)
{
	int	i;

	i = -1;
	while (CONVERSIONS[++i])
		if (CONVERSIONS[i] == c)
			return (i);
	return (-1);
}

static void	manage_conversion(t_printf_env *e)
{
	int	f_index;

	ft_printf_parse_param(e);
	f_index = find_conv_function(e->param.conversion);
	if (f_index < 0)
		return ;
	e->conv_function[f_index](e);
}

static void	manage_printf(t_printf_env *e)
{
	while (e->str[e->str_i])
	{
		if (e->str[e->str_i] != '%')
		{
			ft_putchar(e->str[e->str_i]);
			e->str_i++;
			e->ret++;
			continue ;
		}
		e->str_i++;
		if (!e->str[e->str_i])
			return ;
		manage_conversion(e);
	}
}

int	ft_printf(const char *str, ...)
{
	t_printf_env	e;
	int				ret;

	if (!str)
		return (-1);
	init_printf_env(&e, str);
	va_start(e.ap, str);
	manage_printf(&e);
	ret = e.ret;
	free_printf_env(&e);
	return (ret);
}
