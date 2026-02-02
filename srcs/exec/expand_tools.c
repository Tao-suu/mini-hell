/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 01:41:50 by tbez--du          #+#    #+#             */
/*   Updated: 2026/02/03 01:41:50 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_empty_structure(size_t size)
{
	char	*ret;

	ret = ft_calloc(size + 1, sizeof(char));
	if (!ret)
	{
		print_sys_error("create_empty_structure ft_calloc");
		return (NULL);
	}
	ft_memset((void *)ret, 'n', size);
	return (ret);
}

int	count_env_var_key_size(char *arg)
{
	int	size;

	size = 0;
	if (arg[0] == '?' || ft_isdigit(arg[0]))
		return (1);
	if (!ft_isalpha(arg[size]) && arg[size] != '_')
		return (size);
	size++;
	while (arg[size])
	{
		if (!ft_isalnum(arg[size]) && arg[size] != '_')
			return (size);
		size++;
	}
	return (size);
}
