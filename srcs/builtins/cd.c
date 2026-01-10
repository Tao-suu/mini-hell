/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbez--du <tbez--du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:42:32 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/10 12:09:39 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(t_data *data, t_cmd *cmd)
{
	char	buffer[PATH_MAX];

	if (!cmd->argv[1] && !get_env_var(data, "HOME"))
	{
		ft_putstr_fd("HOME not set\n", 2);
		return (1);
	}
	if (!cmd->argv[1])
	{
		if (chdir(get_env_var(data, "HOME")) < 0)
			return (1);
		set_env_key_value(data, "PWD", get_env_var(data, "HOME"));
	}
	else
	{
		if (chdir(cmd->argv[1]) < 0)
		{
			perror("");
			return (1);
		}
		getcwd(buffer, PATH_MAX);
		set_env_key_value(data, "PWD", buffer);
	}
	return (0);
}
