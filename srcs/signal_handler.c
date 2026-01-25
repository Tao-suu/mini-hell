/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:56:28 by picheval          #+#    #+#             */
/*   Updated: 2026/01/25 16:57:58 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar('\n');
	}
	rl_on_new_line();
	rl_redisplay();
}

void	heredoc_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = signal;
		ft_putchar('\n');
		close(STDIN_FILENO);
	}
}
