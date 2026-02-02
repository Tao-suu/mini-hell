/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 01:40:32 by tbez--du          #+#    #+#             */
/*   Updated: 2026/02/01 01:56:53 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strisnum(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (FALSE);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

static int	is_long(char *str)
{
	size_t	str_size;
	size_t	long_max_size;
	int		cmp;

	if (str[0] == '+')
		str++;
	str_size = ft_strlen(str);
	long_max_size = ft_strlen("9223372036854775807");
	if (str[0] == '-')
		long_max_size++;
	if (str_size > long_max_size)
		return (FALSE);
	if (str_size < long_max_size)
		return (TRUE);
	if (str[0] == '-')
		cmp = ft_strcmp(str, "-9223372036854775808");
	else
		cmp = ft_strcmp(str, "9223372036854775807");
	return (cmp <= 0);
}

int	builtin_exit(t_data *data, t_cmd *cmd, int flag)
{
	int	arg_number;
	int	ret;

	if (!flag)
		printf("exit\n");
	if (cmd->argv[1] && ft_strisnum(cmd->argv[1]) && cmd->argv[2])
		return (print_builtin_exit_error(NULL, "too many arguments") + 1);
	ret = get_exit_code(data);
	if (cmd->argv[1])
	{
		if (!ft_strisnum(cmd->argv[1]) || !is_long(cmd->argv[1]))
		{
			print_builtin_exit_error(cmd->argv[1], "numeric argument required");
			ret = 2;
		}
		else
		{
			arg_number = ft_atoi(cmd->argv[1]);
			ret = arg_number % 256;
		}
	}
	ft_putstr(CLR_RESET);
	free_data(data, TRUE, !flag);
	exit(ret);
}
