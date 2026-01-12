/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 10:42:32 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/12 07:19:46 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int builtin_cd_home(t_env **env, t_cmd *cmd)
{
	t_env	*home_var;

	if (cmd->argv[1] && ft_strcmp(cmd->argv[1], "~"))
		return (0);
	// TODO : "cd ~" works even if HOME doesn't exist ... how ????
	home_var = find_env_var(*env, "HOME");
	if (!home_var || !home_var->value)
		return (print_bash_cd_error(NULL, "HOME not set"));
	if (chdir(home_var->value) < 0)
		return (print_bash_cd_error(home_var->value, NULL));
	create_or_update_env(env, "PWD", home_var->value, STATE_ENV);
	return (0);
}

static int builtin_cd_old(t_env **env, t_cmd *cmd)
{
	t_env	*oldpwd_var;

	if (!cmd->argv[1] || ft_strcmp(cmd->argv[1], "-"))
		return (0);
	oldpwd_var = find_env_var(*env, "OLDPWD");
	if (!oldpwd_var || !oldpwd_var->value)
		return (print_bash_cd_error(NULL, "OLDPWD not set"));
	if (chdir(oldpwd_var->value) < 0)
		return (print_bash_cd_error(oldpwd_var->value, NULL));
	ft_putendl(oldpwd_var->value);
	create_or_update_env(env, "PWD", oldpwd_var->value, STATE_ENV);
	return (0);
}

static int builtin_cd_other(t_env **env, t_cmd *cmd)
{
	char	buffer[5000];

	if (!cmd->argv[1] || !ft_strcmp(cmd->argv[1], "-")
		|| !ft_strcmp(cmd->argv[1], "~"))
		return (0);
	if (chdir(cmd->argv[1]) < 0)
		return (print_bash_cd_error(cmd->argv[1], NULL));
	getcwd(buffer, 5000);
	create_or_update_env(env, "PWD", buffer, STATE_ENV);
	return (0);
}


int	builtin_cd(t_env **env, t_cmd *cmd)
{
	t_env	*pwd_var;
	char	*pwd_var_tmp;

	pwd_var = find_env_var(*env, "PWD");
	if (!pwd_var || !pwd_var->value)
	{
		print_error("Aie PWD");
		return (1);
	}
	pwd_var_tmp = ft_strdup(pwd_var->value);
	if (!pwd_var_tmp)
		return (print_sys_error("ft_strdup"));
	if (builtin_cd_home(env, cmd) || builtin_cd_old(env, cmd)
		|| builtin_cd_other(env, cmd))
	{
		free(pwd_var_tmp);
		return (1);
	}
	create_or_update_env(env, "OLDPWD", pwd_var_tmp, STATE_ENV);
	free(pwd_var_tmp);
	return (0);
}
