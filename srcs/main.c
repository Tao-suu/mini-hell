/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 13:51:35 by picheval          #+#    #+#             */
/*   Updated: 2026/01/28 09:52:27 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_data	data;
	int		ret;

	init_signal();
	if (!init_data(&data))
	{
		free_data(&data, TRUE, TRUE);
		return (1);
	}
	main_loop(&data);


	// Init
		// env / set
			// recreate if not exist (SHLVL TERM LINES COLUMNS PWD SHELL/BASH HOSTNAME?/USERNAME?)
			// .bash_history ?

	// exit --> exit status --> cast unsigned char --> % 255 --> atoll --> no numeri si depasse long long max == char * != int 
		// 1) check numeri
		// 2) nb args
		// 3) nb_args = 0 exit exit_status

	ret = ft_atoi(find_env_var(data.env, "?")->value);
	free_data(&data, TRUE, TRUE);
	return (ret);
}
