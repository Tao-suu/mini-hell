/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbez--du <tbez--du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 00:14:28 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/21 05:49:36 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_valid_arg(char *arg)
{
	int	j;

	j = 1;
	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	while (arg[j])
	{
		if (arg[j] != 'n')
			return (0);
		j++;
	}
	return (1);
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
		if (write(1, cmd->argv[i], ft_strlen(cmd->argv[i])) < 0)
		{
			perror("");
			return (1);
		}
		if (cmd->argv[i + 1])
			if (write(1, " ", 1) < 0)
			{
				perror("");
				return (1);
			}
		i++;
	}
	if (!flag && write(1, "\n", 1) < 0)
	{
		perror("");
		return (1);
	}
	return (0);
}
