/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:01:01 by picheval          #+#    #+#             */
/*   Updated: 2026/01/28 10:30:43 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_loop(t_data *data)
{
	if (manage_line(data) && manage_lexems(data) && create_ast(data))
	{
		// TODO ? Revoir quand on [ign|init]_signal exactement ?
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
	t_env	*exit_code_env_var;
	int		exit_code;

	exit_code_env_var = find_env_var(data->env, "?");
	exit_code = 0;
	if (exit_code_env_var)
		exit_code = ft_atoi(exit_code_env_var->value);
	while (42)
	{
		if (exit_code == 130)
			printf("\n");
		else if (exit_code == 131)
			printf("quit (core dumped)\n");
		// TODO: generate prompt dynamicaly
		data->line = readline("blop $> ");
		if (!data->line)
			break ;
		manage_loop(data);
		add_history(data->line);
		free_data(data, FALSE, TRUE);
	}
	ft_putstr_fd("exit\n", 1);
}
