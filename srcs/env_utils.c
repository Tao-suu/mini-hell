/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:02:19 by picheval          #+#    #+#             */
/*   Updated: 2026/01/09 00:30:42 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(t_data *data, char *var_name)
{
	return (get_var(data->env, var_name));
}

int	unset_env_key(t_data *data, char *key)
{
	return (unset_key(data->env, key));
}

int	set_env_var(t_data *data, char *var)
{
	return (set_var(&(data->env), &(data->env_size), var));
}

int	set_env_key_value(t_data *data, char *key, char *value)
{
	return (set_key_value(&(data->env), &(data->env_size), key, value));
}
