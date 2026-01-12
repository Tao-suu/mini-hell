/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:00:44 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/12 07:17:30 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_env *env)
{
	t_env	*path;

	path = find_env_var(env, "PWD");
	if (!path)
		return (TRUE);
	printf("%s\n", path->value);
	return (FALSE);
}
