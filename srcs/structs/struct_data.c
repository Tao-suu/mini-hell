/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:13:29 by picheval          #+#    #+#             */
/*   Updated: 2026/01/14 18:04:11 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

// full: if TRUE, clear all / else only clear line infos
void	free_data(t_data *data, char full)
{
	if (!data)
		return ;
	if (data->line)
		free(data->line);
	data->line = NULL;
	if (data->head)
		free_lexem_list(data->head);
	data->head = NULL;
	if (data->ast)
		free_ast_tree(data->ast);
	data->ast = NULL;
	if (full == FALSE)
		return ;
	if (data->env)
		free_env_list(data->env);
	if (data->operators)
		free_operator_tab(data->operators);
}

// static int	init_data_env(t_data *data)
// {
// 	char	*value;
// 	char	*tmp;
// 	char	buff[1000];
// 	int		ret;

// 	data->env = ft_tabdup(environ, TAB_EXTRA_SPACE);
// 	if (!data->env)
// 		return (print_sys_error("init_data_env ft_tabdup"));
// 	data->env_size = ft_tablen(data->env) + TAB_EXTRA_SPACE;
// 	if (!get_env_var(data, "PATH")
// 		&& !set_env_key_value(data, "PATH", "/usr/local/sbin:/usr/local/bin:"
// 			"/usr/sbin:/usr/bin:/sbin:/bin"))
// 		return (FALSE);
// 	if (!get_env_var(data, "PWD") && !set_env_key_value(data, "PWD", getcwd(buff, 1000)))
// 		return (FALSE);
// 	value = get_env_var(data, "SHLVL");
// 	if (!value)
// 		return (set_env_key_value(data, "SHLVL", "0"));
// 	tmp = ft_itoa(ft_atoi(value) + 1);
// 	if (!tmp)
// 		return (print_sys_error("init_data_env ft_atoi"));
// 	ret = set_env_key_value(data, "SHLVL", tmp);
// 	free(tmp);
// 	return (ret);
// }

// static int	init_data_set(t_data *data)
// {
// 	char	*value;

// 	data->set = ft_tabdup(NULL, TAB_EXTRA_SPACE);
// 	if (!data->set)
// 		return (print_sys_error("init_data_set ft_tabdup"));
// 	data->set_size = 0 + TAB_EXTRA_SPACE;
// 	value = get_env_var(data, "PATH");
// 	if (!value)
// 		return (print_error("WTF no PATH in env"));
// 	if (!set_set_key_value(data, "PATH", value))
// 		return (FALSE);
// 	value = get_env_var(data, "SHLVL");
// 	if (!value)
// 		return (print_error("WTF no SHLVL in env"));
// 	return (set_set_key_value(data, "SHLVL", value));
// }


static int	init_env_shlvl(t_env **env)
{
	t_env	*elem;
	char	*tmp;

	elem = find_env_var(*env, "SHLVL");
	if (!elem)
		return (create_or_update_env(env, "SHLVL", "0", STATE_ENV));
	tmp = ft_itoa(ft_atoi(elem->value) + 1);
	if (!tmp)
		return (print_sys_error("ft_itoa"));
	free(elem->value);
	elem->value = tmp;
	return (TRUE);
}

static int	init_env_pwd_path(t_env **env)
{
	char	buff[5000];

	if (!find_env_var(*env, "PWD") && !create_or_update_env(env, "PWD", getcwd(buff, 1000), STATE_ENV))
		return (FALSE);
	if (!find_env_var(*env, "OLDPWD") && !create_or_update_env(env, "OLDPWD", NULL, STATE_ENV))
		return (FALSE);
	if (!find_env_var(*env, "PATH") && !create_or_update_env(env, "PATH", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", STATE_SET))
		return (FALSE);
	return (TRUE);
}

static int	init_env(t_env **env)
{
	int		i;

	i = -1;
	while (environ[++i])
	{
		if (!create_env_from_string(env, environ[i], STATE_ENV))
		{
			free_env_list(*env);
			return (FALSE);
		}
	}
	if (!init_env_shlvl(env))
		return (FALSE);
	if (!init_env_pwd_path(env))
		return (FALSE);
	return (create_or_update_env(env, "?", "0", STATE_HIDDEN));
}

int	init_data(t_data *data)
{
	ft_memset((void *)data, 0, sizeof(t_data));
	if (!init_env(&(data->env)))
		return (FALSE);
	//print_debug_env(data->env);
	// if (!init_data_env(data) || !init_data_set(data))
	// 	return (FALSE);
	if (!create_operators_array(&(data->operators)))
		return (FALSE);
	return (TRUE);
}
