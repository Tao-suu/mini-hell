/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:17:27 by picheval          #+#    #+#             */
/*   Updated: 2026/01/03 18:43:07 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // perror
#include "minishell.h"

int	print_sys_error(char *msg)
{
	perror(msg);
	return (FALSE);
}

int	print_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	return (FALSE);
}

static void	print_bash_name(void)
{
	// TODO: replace 'bash' by $TERM
	ft_putstr_fd("bash: ", 2);
}

static int	print_syntax_token_error(char *msg, char *token)
{
	print_bash_name();
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" `", 2);
	ft_putstr_fd(CLR_RED, 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd(CLR_RESET, 2);
	ft_putendl_fd("'", 2);
	return (FALSE);
}

int	print_syntax_error(char *token)
{
	return (print_syntax_token_error("syntax error near unexpected token", token));
}

int	print_matching_error(void)
{
	return (print_syntax_token_error("unexpected EOF while looking for matching", ")"));
}

int	print_bash_error(char *msg)
{
	print_bash_name();
	ft_putstr_fd(CLR_RED, 2);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd(CLR_RESET, 2);
	return (FALSE);
}
