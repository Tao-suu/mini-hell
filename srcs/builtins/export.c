/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 12:46:22 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/12 01:28:16 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_valid_arg(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (FALSE);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	builtin_export(t_data *data, t_cmd *cmd)
{
	char	*equal_index;
	int		i;
	int		ret;

	if (!cmd->argv[1])
		return (builtin_env(data));
	ret = 0;
	i = -1;
	while (cmd->argv[++i])
	{
		equal_index = ft_strchr(cmd->argv[i], '=');
		if (!equal_index)
			continue ;
		if (equal_index == cmd->argv[i] || !export_valid_arg(cmd->argv[i]))
		{
			ret = 1;
			print_bash_export_error(cmd->argv[i]);
		}
		else if (!set_env_var(data, cmd->argv[i]))
		{
			ret = 1;
			break ;
		}
	}
	return (ret);
}
