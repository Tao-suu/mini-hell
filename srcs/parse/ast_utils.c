/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 02:54:51 by picheval          #+#    #+#             */
/*   Updated: 2026/02/02 10:41:13 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	manage_cmd_redir(t_data *data, t_cmd *cmd, t_lexem **start,
	t_lexem *end)
{
	t_redirection	*tmp;

	if (ft_strcmp((*start)->type->name, "IN")
		&& ft_strcmp((*start)->type->name, "OUT")
		&& ft_strcmp((*start)->type->name, "APPEND")
		&& ft_strcmp((*start)->type->name, "HEREDOC"))
		return (TRUE);
	// If suivant inutile ? (pas reussi a le declencher)
	// En theorie il est deja gere par le parser
	if (!(*start)->next || (*start)->next == end
		|| ft_strcmp((*start)->next->type->name, "file"))
		return (print_error("cmd_redir: no file"));
	if (!ft_strcmp((*start)->type->name, "HEREDOC"))
		tmp = create_redirection_elem((*start)->type, NULL);
	else
		tmp = create_redirection_elem((*start)->type, (*start)->next->value);
	if (!tmp)
		return (FALSE);
	add_redirection_in_list(&(cmd->redir), tmp);
	if (!ft_strcmp((*start)->type->name, "HEREDOC")
		&& !manage_heredoc_elem(&(data->heredocs), tmp, (*start)->next->value))
		return (FALSE);
	*start = (*start)->next;
	return (TRUE);
}

static int	manage_parenthesis(t_data *data, t_ast **ast, t_lexem **start,
	t_lexem *end)
{
	t_lexem	*sub_start;
	t_lexem	*tmp[2];

	if (ft_strcmp((*start)->type->name, "PO"))
		return (TRUE);
	sub_start = (*start)->next;
	if (!sub_start)
		return (FALSE);
	skip_parenthesis(start, end);
	tmp[0] = sub_start;
	tmp[1] = *start;
	return (create_ast_recurse(data, ast, tmp, (*start)->lvl + 1));
}

int	manage_cmd_pipeline_elem(t_data *data, t_cmd *cmd, t_lexem **start,
	t_lexem *end)
{
	if (!ft_strcmp((*start)->type->name, "cmd")
		|| !ft_strcmp((*start)->type->name, "param"))
		return (new_cmd_param(&(cmd->params), ft_strdup((*start)->value),
				NULL, -1));
	if (!manage_cmd_redir(data, cmd, start, end))
		return (FALSE);
	if (!manage_parenthesis(data, &(cmd->ast), start, end))
		return (FALSE);
	return (TRUE);
}

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

// size_t	compute_nb_params(t_lexem *start, t_lexem *end)
// {
// 	size_t	nb_argv;
// 	size_t	nb_redir;

// 	nb_argv = 0;
// 	nb_redir = 0;
// 	while (start && start != end && ft_strcmp(start->type->name, "PIPE"))
// 	{
// 		if (!ft_strcmp(start->type->name, "PO"))
// 		{
// 			skip_parenthesis(&start, end);
// 			start = start->next;
// 			continue ;
// 		}
// 		nb_argv++;
// 		if (!ft_strcmp(start->type->name, "IN")
// 			|| !ft_strcmp(start->type->name, "OUT")
// 			|| !ft_strcmp(start->type->name, "APPEND")
// 			|| !ft_strcmp(start->type->name, "HEREDOC"))
// 			nb_redir++;
// 		start = start->next;
// 	}
// 	return (nb_argv - (nb_redir * 2));
// }
