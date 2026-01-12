/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:00:44 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/12 03:57:43 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_data *data)
{
	char	buffer[1000];

	if (get_env_var(data, "PWD") && !ft_strcmp(getcwd(buffer, 1000), "PWD"))
		printf("%s\n", get_env_var(data, "PWD"));
	else if (!getcwd(buffer, 1000))
	{
		perror("");
		return (0);
	}
	else
		printf("%s\n", buffer);
	return (1);
}
