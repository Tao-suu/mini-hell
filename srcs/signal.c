/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:50:35 by picheval          #+#    #+#             */
/*   Updated: 2026/01/03 16:02:04 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>				// signal
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

void	init_signal(void)
{
	struct sigaction	sig;

	sig.sa_flags = 0;
	sigemptyset(&(sig.sa_mask));
	sig.sa_handler = handler;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}