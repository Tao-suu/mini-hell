/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 13:51:35 by picheval          #+#    #+#             */
/*   Updated: 2026/01/09 02:27:06 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	data;

	init_signal();
	if (!init_data(&data))
		return (1);
	main_loop(&data);


	// Init
		// env / set
			// recreate if not exist (SHLVL TERM LINES COLUMNS PWD SHELL/BASH HOSTNAME?/USERNAME?)
			// .bash_history ?
			// SHLVL management
		// signaux / t_data

	// every read loop
		// store & parse line
		// store ast in data
		// built-in management before execve
		// execve
			// reparse PATH

	// heredoc(s): fork ? singleton ?

	// env variables : d'abord check dans env, PUIS dans set uniquement si pas trouve avant
		// env -i
		// !! export set vs env (ex SHLVL)

	free_data(&data, TRUE);
	return (0);
}