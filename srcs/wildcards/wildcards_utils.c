/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbez--du <tbez--du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 17:16:41 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/31 17:19:28 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	its_just_void(void *content)
{
	(void)content;
}

int	check_pattern(char *file, char *pattern)
{
	if (!*pattern)
		return (!*file);
	if (*pattern != '*')
	{
		if (!*file || *pattern != *file)
			return (0);
		return (check_pattern(file + 1, pattern + 1));
	}
	if (check_pattern(file, pattern + 1))
		return (1);
	if (*file && check_pattern(file + 1, pattern))
		return (1);
	return (0);
}
