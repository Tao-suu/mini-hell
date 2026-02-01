/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 17:16:41 by tbez--du          #+#    #+#             */
/*   Updated: 2026/02/03 01:35:20 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	its_just_void(void *content)
{
	(void)content;
}

int	check_pattern(char *file, t_cmd_param *param, int param_index)
{
	if (!param->expanded_value[param_index])
		return (!*file);
	if (param->expanded_value[param_index] != 'y')
	{
		if (!*file || param->original_value[param_index] != *file)
			return (0);
		return (check_pattern(file + 1, param, param_index + 1));
	}
	if (check_pattern(file, param, param_index + 1))
		return (1);
	if (*file && check_pattern(file + 1, param, param_index))
		return (1);
	return (0);
}
