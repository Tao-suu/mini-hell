/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 00:14:28 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/25 21:30:06 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_arg(char *arg)
{
	int	j;

	j = 1;
	if (arg[0] != '-' || arg[1] != 'n')
		return (FALSE);
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (FALSE);
		j++;
	}
	return (TRUE);
}

unsigned char	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (cmd->argv[i] && is_valid_arg(cmd->argv[i]))
	{
		flag = 1;
		i++;
	}
	while (cmd->argv[i])
	{
		if (ft_putstr(cmd->argv[i]) < 0)
			return (print_builtin_echo_error("write error", NULL));
		if (cmd->argv[i + 1] && ft_putchar(' ') < 0)
			return (print_builtin_echo_error("write error", NULL));
		i++;
	}
	if (!flag && ft_putchar('\n') < 0)
		return (print_builtin_echo_error("write error", NULL));
	return (0);
}
