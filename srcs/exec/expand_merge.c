/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_merge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 08:18:11 by picheval          #+#    #+#             */
/*   Updated: 2026/02/02 10:41:36 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_new_param(char *value, int size, char *new_param[2])
{
	size_t	structure_size;
	int		i;

	structure_size = 0;
	if (new_param[1])
		structure_size = ft_strlen(new_param[1]);
	if (!strjoin_free(&(new_param[0]), ft_substr(value, 0, size))
		|| !strjoin_free(&(new_param[1]), create_empty_structure(size)))
	{
		if (new_param[0])
			free(new_param[0]);
		if (new_param[1])
			free(new_param[1]);
		return (FALSE);
	}
	i = -1;
	while (++i < size)
	{
		if (value[i] == '*')
			new_param[1][structure_size + i] = 'y';
	}
	return (TRUE);
}

static int	manage_unquoted_param_spaces(t_cmd_param **new_params, char *value,
	int *i, char *new_param[2])
{
	if (new_param[0]
		&& !new_cmd_param(new_params, new_param[0], new_param[1], -1))
		return (FALSE);
	new_param[0] = NULL;
	new_param[1] = NULL;
	while (ft_isspace(value[*i]))
		(*i)++;
	return (TRUE);
}

static int	manage_unquoted_param(t_cmd_param **new_params, t_cmd_param *elem,
	char *new_param[2], char trim_env_var)
{
	char	*value;
	int		i;
	int		j;

	if (elem->state == PARAM_SQUOTED || elem->state == PARAM_DQUOTED)
		return (TRUE);
	i = 0;
	value = elem->expanded_value;
	while (value && value[i])
	{
		if (trim_env_var && ft_isspace(value[i])
			&& !manage_unquoted_param_spaces(new_params, value, &i, new_param))
			return (FALSE);
		if (!value[i])
			return (TRUE);
		j = 0;
		while (value[i + j] && (!trim_env_var || !ft_isspace(value[i + j])))
			j++;
		if (!update_new_param(value + i, j, new_param))
			return (FALSE);
		i += j;
	}
	return (TRUE);
}

static int	manage_quoted_param(t_cmd_param *elem, char *new_param[2])
{
	if (elem->state != PARAM_SQUOTED && elem->state != PARAM_DQUOTED)
		return (TRUE);
	if (!elem->expanded_value)
	{
		elem->expanded_value = ft_strdup("");
		if (!elem->expanded_value)
			return (print_sys_error("merge_exploded_params ft_strdup"));
	}
	if (!strjoin_free(&(new_param[0]), ft_strdup(elem->expanded_value))
		|| !strjoin_free(&(new_param[1]),
			create_empty_structure(ft_strlen(elem->expanded_value))))
		return (FALSE);
	return (TRUE);
}

int	merge_exploded_params(t_cmd_param **new_params, t_cmd_param *elements,
	char trim_env_var)
{
	char		*new_param[2];

	new_param[0] = NULL;
	new_param[1] = NULL;
	while (elements)
	{
		if (!manage_quoted_param(elements, new_param))
			return (FALSE);
		if (!manage_unquoted_param(new_params, elements, new_param,
				trim_env_var))
			return (FALSE);
		elements = elements->next;
	}
	if (new_param[0]
		&& !new_cmd_param(new_params, new_param[0], new_param[1], -1))
		return (FALSE);
	return (TRUE);
}
