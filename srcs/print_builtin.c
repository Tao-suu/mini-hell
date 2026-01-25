/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:00:49 by picheval          #+#    #+#             */
/*   Updated: 2026/01/25 19:20:28 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// WARNING !! Those function are builtins-specific !
// They returns 1 (ERROR) AND NOT 0 (FALSE)

int	print_builtin_pwd_error(char *msg, char *syscall, char *syscall_msg)
{
	ft_putstr_fd("pwd: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(syscall, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(syscall_msg, 2);
	ft_putstr_fd(": ", 2);
	perror(NULL);
	return (1);
}

int	print_builtin_echo_error(char *syscall_msg, char *msg)
{
	print_bash_cmd_error("echo", syscall_msg, msg);
	return (1);
}

int	print_builtin_exit_error(char *arg, char *msg)
{
	print_bash_name();
	ft_putstr_fd("exit: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(msg, 2);
	return (1);
}

int	print_builtin_cd_error(char *filename, char *msg)
{
	print_bash_cmd_error("cd", filename, msg);
	return (1);
}

int	print_builtin_export_error(char *arg)
{
	print_bash_name();
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}
