/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 17:40:45 by picheval          #+#    #+#             */
/*   Updated: 2026/01/14 19:09:21 by picheval         ###   ########.fr       */
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

void	print_cmd(t_cmd *cmd, int lvl)
{
	t_redirection	*cursor;
	int				i;

	print_tabs(lvl);
	print_color(lvl);
	if (cmd->argv)
	{
		i = -1;
		while (cmd->argv[++i])
			ft_printf("%s%c", cmd->argv[i], (cmd->argv[i + 1] ? ' ': '\0'));
	}
	else
		ft_printf("NO CMD");
	ft_printf(" / ");
	cursor = cmd->in;
	if (!cursor)
		ft_printf("NO REDIR IN");
	while (cursor)
	{
		ft_printf("%s%s(%s)", (cursor == cmd->in ? "" : " "), cursor->name, cursor->operator->name);
		cursor = cursor->next;
	}
	ft_printf(" / ");
	cursor = cmd->out;
	if (!cursor)
		ft_printf("NO REDIR OUT");
	while (cursor)
	{
		ft_printf("%s%s(%s)", (cursor == cmd->out ? "" : " "), cursor->name, cursor->operator->name);
		cursor = cursor->next;
	}
	ft_printf("%s\n", CLR_RESET);
	if (cmd->ast)
		print_ast(cmd->ast, lvl);
}

void	print_ast(t_ast *ast, int lvl)
{
	t_cmd	*cursor;

	if (ast->node_type != NODE_TYPE_CMD)
	{
		print_ast(ast->left, lvl + 1);
		print_tabs(lvl);
		print_color(lvl);
		ft_printf("%s%s\n", (ast->node_type == NODE_TYPE_AND ? "&&" : "||"), CLR_RESET);
		print_ast(ast->right, lvl + 1);
		return ;
	}
	cursor = ast->cmds;
	while (cursor)
	{
		print_cmd(cursor, lvl);
		cursor = cursor->next;
	}
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