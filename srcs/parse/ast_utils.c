/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 02:54:51 by picheval          #+#    #+#             */
/*   Updated: 2026/01/21 05:20:43 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexem	*find_last_operator_in_level(t_lexem *start, t_lexem *end,
		int level)
{
	t_lexem	*ret;

	ret = NULL;
	while (start && start != end)
	{
		if ((!ft_strcmp(start->type->name, "AND")
				|| !ft_strcmp(start->type->name, "OR"))
			&& (start->lvl == level))
			ret = start;
		start = start->next;
	}
	return (ret);
}

void	skip_parenthesis(t_lexem **start, t_lexem *end)
{
	int	lvl;

	if (ft_strcmp((*start)->type->name, "PO"))
		return ;
	lvl = (*start)->lvl;
	while (*start && *start != end
		&& (ft_strcmp((*start)->type->name, "PC") || (*start)->lvl != lvl))
		*start = (*start)->next;
}

size_t	compute_nb_params(t_lexem *start, t_lexem *end)
{
	size_t	nb_argv;
	size_t	nb_redir;

	nb_argv = 0;
	nb_redir = 0;
	while (start && start != end && ft_strcmp(start->type->name, "PIPE"))
	{
		if (!ft_strcmp(start->type->name, "PO"))
		{
			skip_parenthesis(&start, end);
			start = start->next;
			continue ;
		}
		nb_argv++;
		if (!ft_strcmp(start->type->name, "IN")
			|| !ft_strcmp(start->type->name, "OUT")
			|| !ft_strcmp(start->type->name, "APPEND")
			|| !ft_strcmp(start->type->name, "HEREDOC"))
			nb_redir++;
		start = start->next;
	}
	return (nb_argv - (nb_redir * 2));
}
