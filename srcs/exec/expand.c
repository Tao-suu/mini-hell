/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:36:38 by tbez--du          #+#    #+#             */
/*   Updated: 2026/02/05 14:43:48 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_env_var(t_data *data, t_cmd_param *param_elem)
{
	t_env	*env_var;

	if (!ft_strcmp(param_elem->original_value, "$"))
	{
		if (param_elem->state == PARAM_UQUOTED && param_elem->next)
			return (TRUE);
		param_elem->expanded_value = ft_strdup("$");
		if (!param_elem->expanded_value)
			return (print_sys_error("expand_env_var ft_strdup $"));
		return (TRUE);
	}
	env_var = find_env_var(data->env, param_elem->original_value + 1);
	if (!env_var || !env_var->value)
		return (TRUE);
	param_elem->expanded_value = ft_strdup(env_var->value);
	if (!param_elem->expanded_value)
		return (print_sys_error("expand_env_var ft_strdup"));
	return (TRUE);
}

static int	create_elems_expanded_value(t_data *data, t_cmd_param *param_elems)
{
	while (param_elems)
	{
		if (param_elems->state != PARAM_SQUOTED
			&& param_elems->original_value[0] == '$')
		{
			if (!expand_env_var(data, param_elems))
				return (FALSE);
			param_elems = param_elems->next;
			continue ;
		}
		param_elems->expanded_value = ft_strdup(param_elems->original_value);
		if (!param_elems->expanded_value)
			return (print_sys_error("create_elems_expanded_value ft_strdup"));
		param_elems = param_elems->next;
	}
	return (TRUE);
}

static int	expand_redir(t_data *data, t_cmd *cmd)
{
	t_redirection	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->name && (!explode_cmd_param(&(redir->elements),
					redir->name, 0)
				|| !create_elems_expanded_value(data, redir->elements)
				|| !merge_exploded_params(&(redir->expanded_params),
					redir->elements, FALSE)))
			return (FALSE);
		redir = redir->next;
	}
	return (TRUE);
}

static int	expand_cmd(t_data *data, t_cmd *cmd)
{
	t_cmd_param		*param;

	param = cmd->params;
	while (param)
	{
		if (!explode_cmd_param(&(param->elements), param->original_value, 0)
			|| !create_elems_expanded_value(data, param->elements)
			|| !merge_exploded_params(&(cmd->expanded_params), param->elements,
				TRUE))
			return (FALSE);
		param = param->next;
	}
	return (TRUE);
}

int	expand_pipe(t_data *data, t_cmd *cmds)
{
	t_cmd	*cmd;

	cmd = cmds;
	while (cmd)
	{
		if (!expand_cmd(data, cmd) || !expand_redir(data, cmd))
			return (FALSE);
		cmd = cmd->next;
	}
	return (TRUE);
}
