/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:17:27 by picheval          #+#    #+#             */
/*   Updated: 2026/01/25 18:47:33 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

int	print_sys_error(char *msg)
{
	print_bash_name();
	perror(msg);
	return (FALSE);
}

int	print_error(char *msg)
{
	print_bash_name();
	ft_putendl_fd(msg, 2);
	return (FALSE);
}
