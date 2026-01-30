/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:50:35 by picheval          #+#    #+#             */
/*   Updated: 2026/01/28 21:23:22 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	heredoc_signal(void)
{
	signal(SIGINT, &heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
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
	g_signal = 0;
	signal(SIGINT, &handler);
	signal(SIGQUIT, SIG_IGN);
}
