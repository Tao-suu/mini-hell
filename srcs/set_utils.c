/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:02:19 by picheval          #+#    #+#             */
/*   Updated: 2026/01/09 00:32:16 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_set_var(t_data *data, char *var_name)
{
	return (get_var(data->set, var_name));
}

int	unset_set_key(t_data *data, char *key)
{
	return (unset_key(data->set, key));
}

int	set_set_var(t_data *data, char *var)
{
	return (set_var(&(data->set), &(data->set_size), var));
}

int	set_set_key_value(t_data *data, char *key, char *value)
{
	return (set_key_value(&(data->set), &(data->set_size), key, value));
}
