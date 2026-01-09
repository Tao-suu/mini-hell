/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:50:35 by picheval          #+#    #+#             */
/*   Updated: 2026/01/09 16:23:16 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

static void	handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putchar('\n');
	}
	rl_on_new_line();
	rl_redisplay();
}

void	dfl_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ign_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	init_signal(void)
{
	signal(SIGINT, &handler);
	signal(SIGQUIT, SIG_IGN);
}
