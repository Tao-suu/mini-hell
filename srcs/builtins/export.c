/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 12:46:22 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/12 06:55:50 by picheval         ###   ########.fr       */
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

static int	export_print(t_env *env)
{
	while (env)
	{
		if (env->state <= STATE_SET)
		{
			ft_printf("export %s", env->key);
			if (env->value)
				ft_printf("=\"%s\"", env->value);
			ft_printf("\n");
		}
		env = env->next;
	}
	return (0);
}

int	builtin_export(t_env **env, t_cmd *cmd)
{
	char	*equal_index;
	int		i;
	int		ret;

	if (!cmd->argv[1])
		return (export_print(*env));
	ret = 0;
	i = 0;
	while (cmd->argv[++i])
	{
		if (!export_valid_arg(cmd->argv[i]))
		{
			ret = !print_bash_export_error(cmd->argv[i]);
			continue ;
		}
		equal_index = ft_strchr(cmd->argv[i], '=');
		if (equal_index)
		{
			*equal_index = 0;
			equal_index++;
		}
		if (!create_or_update_env(env, cmd->argv[i], equal_index, STATE_ENV))
			return (1);
	}
	return (ret);
}
