/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:38:16 by picheval          #+#    #+#             */
/*   Updated: 2026/01/12 03:52:55 by picheval         ###   ########.fr       */
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

t_env	*create_env_elem(char *key, char *value, int state)
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

int	create_env_from_string(t_env **env, char *string, int state)
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
