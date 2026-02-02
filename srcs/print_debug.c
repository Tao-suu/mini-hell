/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:40:45 by picheval          #+#    #+#             */
/*   Updated: 2026/02/02 11:13:05 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tabs(int nb_tabs)
{
	int	i;

	i = -1;
	while (++i < nb_tabs)
		ft_printf("\t");
}

static void	print_color(int lvl)
{
	if (lvl % 3 == 0)
		ft_printf("%s", CLR_GREEN);
	else if (lvl % 3 == 1)
		ft_printf("%s", CLR_MAG);
	else
		ft_printf("%s", CLR_CYAN);
}

void	print_cmd_elements(t_cmd_param *cmd_elements, int lvl)
{
	char	*elem_state[4] = {
		"NONE", "UNQUOTED", "SINGLE-QUOTED", "DOUBLE-QUOTED"
	};

	while (cmd_elements)
	{
		print_tabs(lvl);
		ft_printf("|%s| => |%s| (%s)\n",
			cmd_elements->original_value,
			cmd_elements->expanded_value,
			elem_state[cmd_elements->state]);
		cmd_elements = cmd_elements->next;
	}
}

void	print_cmd_expanded_args(t_cmd_param *cmd_elements, int lvl)
{
	while (cmd_elements)
	{
		print_tabs(lvl);
		ft_printf("=> arg: |%s| / struct: |%s|\n",
			cmd_elements->original_value,
			cmd_elements->expanded_value);
		cmd_elements = cmd_elements->next;
	}
}
void	print_cmd_params(t_cmd *cmd, int lvl)
{
	t_cmd_param		*cursor_params;
	t_cmd_param		*cursor_elem;
	t_redirection	*redir;

	cursor_params = cmd->params;
	print_color(lvl + 2);
	while (cursor_params)
	{
		print_tabs(lvl + 1);
		ft_printf("%s\n", cursor_params->original_value);
		print_cmd_elements(cursor_params->elements, lvl + 2);
		cursor_params = cursor_params->next;
	}
	redir = cmd->redir;
	while (redir)
	{
		print_tabs(lvl + 1);
		ft_printf("%s %s\n", redir->operator->value, redir->name);
		print_cmd_elements(redir->elements, lvl + 2);
		redir = redir->next;
	}

	cursor_elem = cmd->expanded_params;
	print_color(lvl);
	print_tabs(lvl + 1);
	ft_printf("Expanded args:\n");
	print_cmd_expanded_args(cmd->expanded_params, lvl + 2);
	redir = cmd->redir;
	if (!redir)
		return ;
	print_tabs(lvl + 1);
	ft_printf("Expanded redirections:\n");
	while (redir)
	{
		print_tabs(lvl + 2);
		ft_printf("%s %s\n", redir->operator->value, redir->name);
		print_cmd_expanded_args(redir->expanded_params, lvl + 3);
		redir = redir->next;
	}
}

void	print_cmd(t_cmd *cmd, int lvl)
{
	t_redirection	*cursor_redir;
	t_cmd_param		*cursor_param;
	int				nb_param;

	print_tabs(lvl);
	print_color(lvl);
	if (cmd->params)
	{
		cursor_param = cmd->params;
		nb_param = 0;
		while (cursor_param)
		{
			ft_printf("%s%c", cursor_param->original_value, (cursor_param->next ? ' ' : '\0'));
			cursor_param = cursor_param->next;
			nb_param++;
		}
		ft_printf(" (%d)", nb_param);
	}
	else
		ft_printf("NO CMD");
	ft_printf(" / ");
	cursor_redir = cmd->redir;
	if (!cursor_redir)
		ft_printf("NO REDIR");
	while (cursor_redir)
	{
		ft_printf("%s%s(%s)", (cursor_redir == cmd->redir ? "" : " "), cursor_redir->name, cursor_redir->operator->name);
		cursor_redir = cursor_redir->next;
	}
	ft_printf("\n");
	print_cmd_params(cmd, lvl);
	ft_printf("%s", CLR_RESET);
	if (cmd->ast)
		print_ast(cmd->ast, lvl);
}

void	print_cmds(t_cmd *cmds, int lvl)
{
	t_cmd	*cursor;
	
	cursor = cmds;
	while (cursor)
	{
		print_cmd(cursor, lvl);
		cursor = cursor->next;
	}
}

void	print_ast(t_ast *ast, int lvl)
{

	if (ast->node_type != NODE_TYPE_CMD)
	{
		print_ast(ast->left, lvl + 1);
		print_tabs(lvl);
		print_color(lvl);
		ft_printf("%s%s\n", (ast->node_type == NODE_TYPE_AND ? "&&" : "||"), CLR_RESET);
		print_ast(ast->right, lvl + 1);
		return ;
	}
	print_cmds(ast->cmds, lvl);
}

static void	print_deps(t_operator **deps, char *prefix)
{
	int	i;

	ft_printf("\t%s:\t", prefix);
	if (!deps)
	{
		ft_printf("NONE\n");
		return ;
	}
	i = -1;
	while (deps[++i])
	{
		if (i > 0)
			ft_printf(", ");
		ft_printf("%s", deps[i]->name);
	}
	ft_printf("\n");
}

void	print_operators(t_operator **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		ft_printf("%s%d\t%s\t%s%s\n", CLR_GREEN, tab[i]->id, tab[i]->name, tab[i]->value, CLR_RESET);
		print_deps(tab[i]->before, "before");
		print_deps(tab[i]->after, "after");
	}
}

void	print_debug_env(t_env *env)
{
	while (env)
	{
		ft_printf("%d\t%s\t%s%s%s\n", env->state, env->key, CLR_RED, env->value, CLR_RESET);
		env = env->next;
	}
}
