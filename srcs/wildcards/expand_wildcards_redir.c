/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards_redir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:04:35 by tbez--du          #+#    #+#             */
/*   Updated: 2026/02/03 01:32:43 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	match_number(t_cmd_param *param, char **files)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (files[i])
	{
		if (param->original_value[0] != '.' && files[i][0] == '.')
		{
			i++;
			continue ;
		}
		if (check_pattern(files[i], param, 0))
			j++;
		i++;
	}
	return (j);
}

static int	set_valid_wildcard(t_redirection *redir, char **files)
{
	char	*pattern;

	if (!redir->expanded_params)
	{
		redir->valid_wild = 1;
		return (0);
	}
	pattern = redir->expanded_params->expanded_value;
	if (ft_strchr(pattern, 'y')
		&& match_number(redir->expanded_params, files) < 1)
		redir->valid_wild = 1;
	else if (ft_strchr(pattern, 'y')
		&& match_number(redir->expanded_params, files) > 1)
		redir->valid_wild = 0;
	else if (ft_strchr(pattern, 'y'))
	{
		redir->valid_wild = 1;
		return (1);
	}
	else
		redir->valid_wild = 1;
	return (0);
}

static int	sub_expand_wildcards_redir(t_cmd_param *param, char **files)
{
	int	i;

	i = 0;
	while (files[i])
	{
		if (param->original_value[0] != '.' && files[i][0] == '.')
		{
			i++;
			continue ;
		}
		else if (check_pattern(files[i], param, 0))
		{
			free(param->original_value);
			param->original_value = ft_strdup(files[i]);
			if (!param->original_value)
				return (0);
			return (1);
		}
		i++;
	}
	return (1);
}

int	expand_wildcards_redir(t_cmd *cmd, char **files)
{
	t_redirection	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (set_valid_wildcard(redir, files)
			&& !sub_expand_wildcards_redir(redir->expanded_params, files))
			return (0);
		redir = redir->next;
	}
	return (1);
}
