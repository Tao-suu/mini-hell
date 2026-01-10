/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbez--du <tbez--du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 12:46:22 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/10 12:55:12 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(t_data *data, t_cmd *cmd)
{
	ft_putstr_fd("here\n", 2);
	if (!cmd->argv[1])
		builtin_env(data);
	else
		set_env_var(data, cmd->argv[1]);
	return (0);
}
