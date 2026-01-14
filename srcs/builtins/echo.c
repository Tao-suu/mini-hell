/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbez--du <tbez--du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 00:14:28 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/14 14:47:17 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_valid_arg(char *arg)
{
	int	j;

	j = 1;
	if (arg[0] != '-')
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
		if (printf("%s", cmd->argv[i]) < 0)
		{
			perror("");
			return (1);
		}
		if (cmd->argv[i + 1])
			printf(" ");
		i++;
	}
	if (!flag && printf("\n") < 0)
	{
		perror("");
		return (1);
	}
	return (0);
}
