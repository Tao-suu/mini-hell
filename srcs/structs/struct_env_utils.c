/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:38:52 by picheval          #+#    #+#             */
/*   Updated: 2026/01/25 22:03:02 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *elem)
{
	if (!elem)
		return ;
	if (elem->key)
		free(elem->key);
	if (elem->value)
		free(elem->value);
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

static void	add_env_elem_in_list(t_env **list, t_env *elem)
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

int	create_and_add_env_elem(t_env **env, char *key, char *value,
	t_env_state state)
{
	t_env	*elem;

	elem = (t_env *)ft_calloc(1, sizeof(t_env));
	if (elem)
	{
		elem->key = key;
		elem->value = value;
		elem->state = state;
		add_env_elem_in_list(env, elem);
		return (TRUE);
	}
	if (key)
		free(key);
	if (value)
		free(value);
	return (FALSE);
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
