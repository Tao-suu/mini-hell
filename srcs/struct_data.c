/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 15:13:29 by picheval          #+#    #+#             */
/*   Updated: 2026/01/09 02:33:36 by picheval         ###   ########.fr       */
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
	data->line = NULL;
	if (data->head)
		free_lexem_list(data->head);
	data->head = NULL;
	if (data->ast)
		free_ast_tree(data->ast);
	data->ast = NULL;
	if (full == FALSE)
		return ;
	if (data->env)
		ft_tabclear(data->env);
	if (data->set)
		ft_tabclear(data->set);
	if (data->operators)
		free_operator_tab(data->operators);
}

static int	init_data_env(t_data *data)
{
	data->env = ft_tabdup(environ, TAB_EXTRA_SPACE);
	if (!data->env)
		return (print_sys_error("init_data_env ft_tabdup"));
	data->env_size = ft_tablen(data->env) + TAB_EXTRA_SPACE;
	if (!get_env_var(data, "PATH")
		&& !set_env_key_value(data, "PATH", "/usr/local/sbin:/usr/local/bin:"
			"/usr/sbin:/usr/bin:/sbin:/bin"))
		return (FALSE);
	if (get_env_var(data, "SHLVL"))
		return (TRUE);
	return (set_env_key_value(data, "SHLVL", "0"));
}

static int	init_data_set(t_data *data)
{
	char	*value;
	char	*tmp;
	int		ret;

	data->set = ft_tabdup(NULL, TAB_EXTRA_SPACE);
	if (!data->set)
		return (print_sys_error("init_data_set ft_tabdup"));
	value = get_env_var(data, "PATH");
	if (!value)
		return (print_error("WTF no PATH in env"));
	if (!set_set_key_value(data, "PATH", value))
		return (FALSE);
	value = get_env_var(data, "SHLVL");
	if (!value)
		return (print_error("WTF no SHLVL in env"));
	tmp = ft_itoa(ft_atoi(value) + 1);
	if (!tmp)
		return (print_sys_error("init_data_set ft_atoi malloc"));
	ret = set_set_key_value(data, "SHLVL", tmp);
	free(tmp);
	return (ret);
}

int	init_data(t_data *data)
{
	ft_memset((void *)data, 0, sizeof(t_data));
	if (!init_data_env(data) || !init_data_set(data))
		return (FALSE);
	ft_tabprint(data->env);
	ft_printf("\n");
	ft_tabprint(data->set);
	if (!create_operators_array(&(data->operators)))
		return (FALSE);
	return (TRUE);
}
