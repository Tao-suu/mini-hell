/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 01:40:32 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/12 07:40:47 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strisnum(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0); 
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	builtin_exit(t_data *data, t_cmd *cmd)
{
	int	arg_number;

	ft_putstr_fd("exit\n", 2);
	if (cmd->argv[1] && ft_strisnum(cmd->argv[1]) && cmd->argv[2])
	{
		print_bash_exit_error(NULL, "too many arguments");
		return (1);
	}
	if (cmd->argv[1])
	{
		if (!ft_strisnum(cmd->argv[1]))
		{
			print_bash_exit_error(cmd->argv[1], "numeric argument required");
			free_data(data, TRUE);
			exit(2);
		}
		arg_number = ft_atoi(cmd->argv[1]);
		free_data(data, TRUE);
		exit(arg_number % 256);
	}
	free_data(data, TRUE);
	exit(0); // last ret code
}
