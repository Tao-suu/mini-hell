/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:38:16 by picheval          #+#    #+#             */
/*   Updated: 2026/01/12 07:13:10 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	free_env(t_env *elem)
{
	if (!elem)
		return ;
	free(elem);
}

void	free_env_list(t_env *list)
{
	t_env	*cursor;

	while (list)
	{
		cursor = list;
		list = list->next;
		free_env(cursor);
	}
}

void	add_env_elem_in_list(t_env **list, t_env *elem)
{
	t_env	*cursor;

	if (!*list)
	{
		*list = elem;
		return ;
	}
	cursor = *list;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = elem;
}

t_env	*create_env_elem(char *key, char *value, t_env_state state)
{
	t_env	*ret;

	ret = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!ret)
		return (NULL);
	ret->key = key;
	ret->value = value;
	ret->state = state;
	return (ret);
}

t_env	*find_env_var(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	get_env_size(t_env *env, t_env_state state)
{
	int i;

	i = 0;
	while (env)
	{
		if (env->state <= state)
			i++;
		env = env->next;		
	}
	return (i);
}

char **get_env_tab_from_list(t_env *env)
{
	int 	len;
	int		i;
	int		line_len;
	char	**arr;

	len	= get_env_size(env, STATE_ENV);
	arr = ft_calloc(len + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		if (!env->value || env->state != STATE_ENV)
		{
			env = env->next;
			continue ;
		}
		line_len = ft_strlen(env->key) + 2 + ft_strlen(env->value);
		arr[i] = ft_calloc(line_len, 1);
		if (!arr[i])
		{
			ft_tabclear(arr);
			return (NULL);
		}
		ft_strlcat(arr[i], env->key, line_len);
		ft_strlcat(arr[i], "=", line_len);
		ft_strlcat(arr[i], env->value, line_len);
		env = env->next;
	}
	return (arr);
}

int	create_or_update_env(t_env **env, char *key, char *value, t_env_state state)
{
	t_env	*elem;
	char	*tmp_key;
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
	tmp_key = ft_strdup(key);
	if (!tmp_key)
		return (print_sys_error("ft_strdup"));
	elem = create_env_elem(tmp_key, tmp_value, state);
	if (!elem)
		return (print_sys_error("create_env_elem"));
	add_env_elem_in_list(env, elem);
	return (TRUE);
}


int	create_env_from_string(t_env **env, char *string, t_env_state state)
{
	t_env	*elem;
	char	*equal_index;
	char	*key;
	char	*value;

	equal_index = ft_strchr(string, '=');
	if (!equal_index)
		return (print_error("no '=' in environ variable"));
	if (equal_index == string)
		return (print_error("'=' at the begining of environ variable"));
	key = ft_substr(string, 0, equal_index - string);
	value = ft_substr(equal_index + 1, 0, ft_strlen(equal_index + 1));
	if (!key || !value)
		return (print_sys_error("ft_substr"));
	elem = create_env_elem(key, value, state);
	if (!elem)
		return (print_sys_error("create_env_elem"));
	add_env_elem_in_list(env, elem);
	return (TRUE);
}
