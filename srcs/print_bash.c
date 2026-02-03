/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 02:57:08 by picheval          #+#    #+#             */
/*   Updated: 2026/02/03 02:01:47 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_bash_name(void)
{
	ft_putstr_fd("bash: ", 2);
}

int	print_bash_ambiguous_redirection(char *name)
{
	write(2, "bash: ", 6);
	if (name)
	{
		write(2, name, ft_strlen(name));
		write(2, ": ", 2);
	}
	write(2, "ambiguous redirect\n", 19);
	return (FALSE);
}

void	print_bash_heredoc_warning(int nb_execution, char *delimiter)
{
	print_bash_name();
	ft_putstr_fd("warning: here-document at line ", 2);
	ft_putnbr_fd(nb_execution, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putendl_fd("')", 2);
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
