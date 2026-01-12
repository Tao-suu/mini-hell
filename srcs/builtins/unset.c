/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 12:29:02 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/12 06:24:38 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_env *env, t_cmd *cmd)
{
	t_env	*tmp;
	int		i;

	i = 0;
	while (cmd->argv[++i])
	{
		tmp = find_env_var(env, cmd->argv[i]);
		if (!tmp || tmp->state >= STATE_HIDDEN)
			continue ;
		if (tmp->value)
			free(tmp->value);
		tmp->value = NULL;
		tmp->state = STATE_DEAD;
	}
	return (0);
}
