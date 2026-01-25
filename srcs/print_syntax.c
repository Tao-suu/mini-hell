/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 22:07:26 by picheval          #+#    #+#             */
/*   Updated: 2026/01/25 22:07:51 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_syntax_token_error(char *msg, char *token, char c)
{
	print_bash_name();
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" `", 2);
	ft_putstr_fd(CLR_RED, 2);
	if (token)
		ft_putstr_fd(token, 2);
	else
		ft_putchar_fd(c, 2);
	ft_putstr_fd(CLR_RESET, 2);
	ft_putendl_fd("'", 2);
	return (FALSE);
}

int	print_syntax_error(char *token)
{
	return (print_syntax_token_error("syntax error near unexpected token",
			token, 0));
}

int	print_matching_error(char c)
{
	return (print_syntax_token_error("unexpected EOF while looking for "
			"matching", NULL, c));
}
