/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:13:29 by picheval          #+#    #+#             */
/*   Updated: 2026/01/03 16:11:58 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

// full: if TRUE, clear all / else only clear line infos
void	free_data(t_data *data, char full)
{
	if (!data)
		return ;
	if (data->line)
		free(data->line);
	// TODO: free head / ast
	if (full == FALSE)
		return ;
	if (data->env)
		ft_tabclear(data->env);
	if (data->set)
		ft_tabclear(data->set);
	// TODO: free operators
}

int	init_data(t_data *data)
{
	ft_memset((void *)data, 0, sizeof(t_data));
	data->env = ft_tabdup(environ);
	if (!data->env)
		return (print_sys_error("ft_tabdup"));
	ft_tabprint(data->env);

	// TODO
		// init set
		// init operators
	
	return (TRUE);
}
