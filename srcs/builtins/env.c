/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 01:36:14 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/12 06:15:13 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_env *env)
{
	while (env)
	{
		if (env->value && env->state == STATE_ENV)
			ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
