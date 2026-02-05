/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:01:01 by picheval          #+#    #+#             */
/*   Updated: 2026/02/05 15:00:20 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_loop(t_data *data)
{
	int	ret;

	if (!manage_line(data))
		return ;
	ret = manage_lexems(data);
	if (create_ast(data) && ret)
	{
		ign_signal();
		if (exec_heredocs(data))
			set_exit_code(&data->env, exec_ast(data, data->ast));
		init_signal();
		return ;
	}
	ign_signal();
	exec_heredocs(data);
	init_signal();
	set_exit_code(&(data->env), 2);
}

void	main_loop(t_data *data)
{
	while (42)
	{
		data->nb_execution++;
		ft_printf("%s", data->color[data->prompt_n++ % 6]);
		if (isatty(0) && isatty(1) && isatty(2))
		{
			data->line = readline(get_prompt(data));
			add_history(data->line);
		}
		else
			data->line = get_next_line(0, 0);
		if (!data->line)
			break ;
		manage_loop(data);
		get_next_line(0, 1);
		free_data(data, FALSE, TRUE);
	}
	ft_putstr_fd("exit\n"CLR_RESET, 1);
	rl_clear_history();
}
