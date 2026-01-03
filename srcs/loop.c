/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:01:01 by picheval          #+#    #+#             */
/*   Updated: 2026/01/03 16:08:26 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_balanced(char *line)
{
	(void)line;
	// TODO: all ;)
	return (TRUE);
}

void	main_loop(t_data *data)
{
	while (42)
	{
		// TODO: generate prompt dynamicaly
		data->line = readline("$> ");
		if (!data->line)
			break ;
		if (!is_balanced(data->line))
			print_error("parse error");
		else
		{
			// TODO: parse line
			add_history(data->line);
			free_data(data, FALSE);
		}
	}
}