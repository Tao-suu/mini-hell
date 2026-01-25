/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:38:16 by picheval          #+#    #+#             */
/*   Updated: 2026/01/25 22:17:17 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_env_size(t_env *env, t_env_state state)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->value && env->state <= state)
			i++;
		env = env->next;
	}
	return (i);
}

char	**get_env_tab_from_list(t_env *env)
{
	int		len;
	int		i;
	char	**arr;

	len = get_env_size(env, STATE_ENV);
	arr = ft_calloc(len + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (!env->value || env->state != STATE_ENV)
		{
			env = env->next;
			continue ;
		}
		if (!merge_with_sep(&(arr[i]), env->key, env->value, "="))
		{
			ft_tabclear(arr);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	return (arr);
}

static int	create_new_env(t_env **env, char *key, char *tmp_value,
	t_env_state state)
{
	char	*tmp_key;

	tmp_key = ft_strdup(key);
	if (!tmp_key)
	{
		if (tmp_value)
			free(tmp_value);
		return (print_sys_error("ft_strdup"));
	}
	return (create_and_add_env_elem(env, tmp_key, tmp_value, state));
}

int	create_or_update_env(t_env **env, char *key, char *value, t_env_state state)
{
	t_env	*elem;
	char	*tmp_value;

	tmp_value = NULL;
	if (value)
	{
		tmp_value = ft_strdup(value);
		if (!tmp_value)
			return (print_sys_error("ft_strdup"));
	}
	elem = find_env_var(*env, key);
	if (elem)
	{
		if (elem->value)
			free(elem->value);
		elem->state = state;
		elem->value = tmp_value;
		return (TRUE);
	}
	return (create_new_env(env, key, tmp_value, state));
}

int	create_env_from_string(t_env **env, char *string, t_env_state state)
{
	char	*equal_index;
	char	*key;
	char	*value;

	equal_index = ft_strchr(string, '=');
	if (!equal_index)
		return (print_error("no '=' in environ variable"));
	if (equal_index == string)
		return (print_error("'=' at the begining of environ variable"));
	key = ft_substr(string, 0, equal_index - string);
	if (!key)
		return (print_sys_error("ft_substr key"));
	value = ft_substr(equal_index + 1, 0, ft_strlen(equal_index + 1));
	if (!value)
	{
		free(key);
		return (print_sys_error("ft_substr value"));
	}
	return (create_and_add_env_elem(env, key, value, state));
}
