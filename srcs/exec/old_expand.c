/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_old.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:36:38 by tbez--du          #+#    #+#             */
/*   Updated: 2026/02/01 22:46:50 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_to_expand_argv(char *s)
{
	char	quote;
	int		i;

	i = 0;
	quote = 0;
	while (s[i])
	{
		if (s[i] == '*')
			return (1);
		if (s[i] == '"' || s[i] == '\'')
		{
			quote = s[i++];
			while (s[i] && s[i] != quote)
				i++;
		}
		i++;
	}
	return (0);
}

static int	set_is_to_expand(t_cmd *cmd)
{
	int	i;

	if (!cmd->argv)
		return (1);
	i = 0;
	while (cmd->argv[i])
		i++;
	cmd->to_expand = ft_calloc(i + 1, 1);
	if (!cmd->to_expand)
		return (0);
	i = 0;
	while (cmd->argv[i])
	{
		if (is_to_expand_argv(cmd->argv[i]))
			cmd->to_expand[i] = 'y';
		else
			cmd->to_expand[i] = 'n';
		i++;
	}
	cmd->to_expand[i] = 0;
	return (1);
}

// Cree une liste chainee contenant chaque argv expanded
// Transforme cette liste en tableau pour remplacer l'ancien cmd->argv
static int	expand_cmd(t_data *data, t_cmd *cmd)
{
	t_list	*lst;
	char	**argv;
	int		i;

	i = -1;
	lst = NULL;
	while (cmd->argv && cmd->argv[++i])
	{
		if (create_lst_empty(&lst)
			&& expand_token(data, &lst, cmd->argv[i], TRUE))
			continue ;
		ft_lstclear(&lst, free);
		return (FALSE);
	}
	argv = create_tab_from_lst(lst);
	if (!argv)
	{
		ft_lstclear(&lst, free);
		return (print_sys_error("create_tab_from_lst"));
	}
	if (cmd->argv)
		ft_tabclear(cmd->argv);
	cmd->argv = argv;
	cmd->argc = ft_tablen(cmd->argv);
	return (TRUE);
}

static int	expand_file(t_data *data, char **name)
{
	t_list	*lst;

	lst = NULL;
	if (!create_lst_empty(&lst) || !expand_token(data, &lst, *name, FALSE))
	{
		ft_lstclear(&lst, free);
		return (FALSE);
	}
	free(*name);
	*name = lst->content;
	free(lst);
	return (TRUE);
}

// TODO

int	expand_pipe(t_data *data, t_cmd *cmds)
{
	t_redirection	*tmp;

	while (cmds)
	{
		if (!expand_cmd(data, cmds) || !set_is_to_expand(cmds))
			return (FALSE);
		tmp = cmds->redir;
		while (tmp)
		{
			if (tmp->name && !expand_file(data, &(tmp->name)))
				return (FALSE);
			tmp = tmp->next;
		}
		cmds = cmds->next;
	}
	return (TRUE);
}
