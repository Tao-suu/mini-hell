/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:00:44 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/14 21:24:03 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_env *env)
{
	(void)env;
	char	buffer[5000];

	if (!getcwd(buffer, 5000))
		return (print_bash_cmd_error(NULL, "pwd: error retrieving current directory: getcwd: cannot access parent directories", NULL));
	printf("%s\n", buffer);
	return (FALSE);
}
