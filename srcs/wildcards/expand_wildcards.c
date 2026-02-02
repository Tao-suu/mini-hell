/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:24:12 by tbez--du          #+#    #+#             */
/*   Updated: 2026/02/03 01:28:20 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_wildcards(t_cmd_param *param, char **files, t_list **new_argv)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (files[i])
	{
		if (param->original_value[0] != '.' && *(files[i]) == '.')
			;
		else if (check_pattern(files[i], param, 0))
		{
			flag = 1;
			ft_lstadd_back(new_argv, ft_lstnew(ft_strdup(files[i])));
		}
		i++;
	}
	if (!flag)
		ft_lstadd_back(new_argv, ft_lstnew(ft_strdup(param->original_value)));
	return (1);
}

static char	**create_tab_from_argv_list(t_list *lst)
{
	char	**ret;
	int		i;

	ret = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (lst)
	{
		ret[i++] = (char *)lst->content;
		lst = lst->next;
	}
	return (ret);
}

int	expand_wildcards_argv(t_cmd *cmd, char **files_name)
{
	t_cmd_param	*cursor;
	t_list	*new_argv;

	new_argv = NULL;
	if (!files_name)
		return (0);
	cursor = cmd->expanded_params;
	while (cursor)
	{
		if (ft_strchr(cursor->expanded_value, 'y'))
		{
			if (!expand_wildcards(cursor, files_name, &new_argv))
				return (0);
		}
		else
			ft_lstadd_back(&new_argv, ft_lstnew(ft_strdup(cursor->original_value)));
		cursor = cursor->next;
	}
	//ft_tabclear(cmd->argv);
	cmd->argv = create_tab_from_argv_list(new_argv);
	if (!cmd->argv)
		return (0);
	ft_lstclear(&new_argv, its_just_void);
	return (1);
}

int	expand_wildcards_cmd(t_cmd *cmd)
{
	char	**files_name;

	files_name = get_files_name();
	if (!files_name)
		return (0);
	sort_files(files_name);
	while (cmd)
	{
		if (!(expand_wildcards_argv(cmd, files_name)
				&& expand_wildcards_redir(cmd, files_name)))
			return (0);
		cmd = cmd->next;
	}
	ft_tabclear(files_name);
	return (1);
}
