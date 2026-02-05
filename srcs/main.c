/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 13:51:35 by picheval          #+#    #+#             */
/*   Updated: 2026/02/05 14:44:22 by picheval         ###   ########.fr       */
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
	ret = ft_atoi(find_env_var(data.env, "?")->value);
	free_data(&data, TRUE, TRUE);
	return (ret);
}
