/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:17:27 by picheval          #+#    #+#             */
/*   Updated: 2026/01/09 02:57:20 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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
