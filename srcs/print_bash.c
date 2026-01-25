/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 02:57:08 by picheval          #+#    #+#             */
/*   Updated: 2026/01/28 20:53:53 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_bash_name(void)
{
	// TODO: replace 'bash' by $TERM
	ft_putstr_fd("bash: ", 2);
}

int	print_bash_cmd_error(char *cmd, char *filename, char *msg)
{
	print_bash_name();
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (filename)
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putendl_fd(msg, 2);
	else
		perror(NULL);
	return (FALSE);
}

int	print_bash_error(char *msg)
{
	print_bash_name();
	ft_putstr_fd(CLR_RED, 2);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd(CLR_RESET, 2);
	return (FALSE);
}
