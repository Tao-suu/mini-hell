/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 12:29:02 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/11 23:37:44 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_data *data, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->argv[++i])
	{
		// if invalid key format, then continue ;
		if (ft_strchr(cmd->argv[i], '='))
			continue ;
		unset_env_key(data, cmd->argv[i]);
	}
	return (0);
}
