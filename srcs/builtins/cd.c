/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:42:32 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/11 18:55:52 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int builtin_cd_home(t_data *data, t_cmd *cmd)
{
	char	*home_var;

	if (cmd->argv[1] && ft_strcmp(cmd->argv[1], "~"))
		return (0);
	// TODO : "cd ~" works even if HOME doesn't exist ... how ????
	home_var = get_env_var(data, "HOME");
	if (!home_var)
		return (print_bash_cd_error(NULL, "HOME not set"));
	if (chdir(home_var) < 0)
		return (print_bash_cd_error(home_var, NULL));
	set_env_key_value(data, "PWD", home_var);
	return (0);
}

static int builtin_cd_old(t_data *data, t_cmd *cmd)
{
	char	*oldpwd_var;

	if (!cmd->argv[1] || ft_strcmp(cmd->argv[1], "-"))
		return (0);
	oldpwd_var = get_env_var(data, "OLDPWD");
	if (!oldpwd_var)
		return (print_bash_cd_error(NULL, "OLDPWD not set"));
	if (chdir(oldpwd_var) < 0)
		return (print_bash_cd_error(oldpwd_var, NULL));
	ft_putendl(oldpwd_var);
	set_env_key_value(data, "PWD", oldpwd_var);
	return (0);
}

static int builtin_cd_other(t_data *data, t_cmd *cmd)
{
	char	buffer[PATH_MAX];

	if (!cmd->argv[1] || !ft_strcmp(cmd->argv[1], "-")
		|| !ft_strcmp(cmd->argv[1], "~"))
		return (0);
	if (chdir(cmd->argv[1]) < 0)
		return (print_bash_cd_error(cmd->argv[1], NULL));
	getcwd(buffer, PATH_MAX);
	set_env_key_value(data, "PWD", buffer);
	return (0);
}


int	builtin_cd(t_data *data, t_cmd *cmd)
{
	char	*pwd_var;

	pwd_var = get_env_var(data, "PWD");
	pwd_var = ft_strdup(pwd_var);
	if (!pwd_var)
	{
		print_sys_error("ft_strdup");
		return (1);
	}
	if (builtin_cd_home(data, cmd) || builtin_cd_old(data, cmd)
		|| builtin_cd_other(data, cmd))
	{
		free(pwd_var);
		return (1);
	}
	set_env_key_value(data, "OLDPWD", pwd_var);
	free(pwd_var);
	return (0);
}
