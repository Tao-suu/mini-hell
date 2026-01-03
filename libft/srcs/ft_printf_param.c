/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:19:12 by picheval          #+#    #+#             */
/*   Updated: 2025/11/28 17:58:09 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	parse_param_flag(t_printf_env *e)
{
	char	c;

	c = e->str[e->str_i];
	if (c == '-')
		e->param.minus = TRUE;
	else if (c == '0')
		e->param.zero = TRUE;
	else if (c == '#')
		e->param.hashtag = TRUE;
	else if (c == ' ')
		e->param.space = TRUE;
	else if (c == '+')
		e->param.plus = TRUE;
	else
		return (0);
	e->str_i++;
	return (1);
}

static int	parse_param_number(t_printf_env *e)
{
	int	ret;

	ret = 0;
	while (ft_isdigit(e->str[e->str_i]))
		ret = ret * 10 + (e->str[e->str_i++] - '0');
	return (ret);
}

void	ft_printf_parse_param(t_printf_env *e)
{
	ft_memset(&(e->param), 0, sizeof(t_printf_param));
	e->param.dot = -1;
	e->param.min_width = -1;
	while (e->str[e->str_i])
	{
		if (parse_param_flag(e))
			continue ;
		if (ft_isdigit(e->str[e->str_i]))
			e->param.min_width = parse_param_number(e);
		if (e->str[e->str_i] == '.')
		{
			e->str_i++;
			e->param.dot = parse_param_number(e);
		}
		if (e->str[e->str_i])
			e->param.conversion = e->str[e->str_i++];
		break ;
	}
}
