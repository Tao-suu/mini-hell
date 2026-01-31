/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards_redir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbez--du <tbez--du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:04:35 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/31 17:11:01 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	match_number(char *name, char **files)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (files[i])
	{
		if (check_pattern(files[i], name))
			j++;
		i++;
	}
	return (j);
}

static int	set_valid_wildcard(t_redirection *redir, char **files)
{
	if (!redir->name)
	{
		redir->valid_wild = 1;
		return (0);
	}
	else if (ft_strchr(redir->name, '*')
		&& match_number(redir->name, files) < 1)
		redir->valid_wild = 1;
	else if (ft_strchr(redir->name, '*')
		&& match_number(redir->name, files) > 1)
		redir->valid_wild = 0;
	else if (ft_strchr(redir->name, '*'))
	{
		redir->valid_wild = 1;
		return (1);
	}
	else
		redir->valid_wild = 1;
	return (0);
}

static int	sub_expand_wildcards_redir(char **str, char **files)
{
	int	i;

	i = 0;
	while (files[i])
	{
		if (check_pattern(files[i], *str))
		{
			free(*str);
			*str = ft_strdup(files[i]);
			if (!*str)
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
			&& !sub_expand_wildcards_redir(&redir->name, files))
			return (0);
		redir = redir->next;
	}
	return (1);
}
