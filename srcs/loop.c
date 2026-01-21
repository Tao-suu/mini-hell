/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:01:01 by picheval          #+#    #+#             */
/*   Updated: 2026/01/21 05:47:31 by tbez--du         ###   ########.fr       */
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
		//if (exit_status == 130)
		//{
		//	printf("\n");
		//}
		data->line = readline("$> ");
		//data->line = NULL;
		if (!data->line)
			break ;
		if (!is_balanced(data->line))
			print_error("parse error");
		else
		{
			if (manage_line(data) && manage_lexems(data) && create_ast(data))
			{
				ign_signal();
				exec_ast(data, data->ast);
				init_signal();
			}
			add_history(data->line);
			free_data(data, FALSE);
		}
	}
	ft_putstr_fd("exit\n", 1);
}
