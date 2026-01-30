/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbez--du <tbez--du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:24:12 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/30 19:06:34 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pattern(char *file, char *pattern)
{
	if (!*pattern)
		return (!*file);
	if (*pattern != '*')
	{
		if (!*file || *pattern != *file)
			return (0);
		return check_pattern(file + 1, pattern + 1);
	}
	if (check_pattern(file, pattern + 1))
		return (1);
	if (*file && check_pattern(file + 1, pattern))
		return (1);
	return (0);
}

int	expand_wildcards(char *str, char **files, t_list **new_argv)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (files[i])
	{
		if (str[0] != '.' && *(files[i]) == '.')
			;
		else if (check_pattern(files[i], str))
		{
			flag = 1;
			ft_lstadd_back(new_argv, ft_lstnew(ft_strdup(files[i])));
		}
		i++;
	}
	if (!flag)
		ft_lstadd_back(new_argv, ft_lstnew(ft_strdup(str)));
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

static void	its_just_void(void *content)
{
	(void)content;
}

int		expand_wildcards_argv(t_cmd *cmd, char **files_name)
{
	int		i;
	char	**new_argv_tab;
	t_list	*new_argv;
	
	new_argv = NULL;
	new_argv_tab = NULL;
	if (!files_name)
		return (0);
	i = 0;
	while (cmd->argv[i])
	{
		if (cmd->to_expand[i] == 'y')
		{	
			if (!expand_wildcards(cmd->argv[i], files_name, &new_argv))
				return (0);
		}
		else
			ft_lstadd_back(&new_argv, ft_lstnew(ft_strdup(cmd->argv[i])));
		i++;
	}
	new_argv_tab = create_tab_from_argv_list(new_argv);
	if (!new_argv_tab)
		return (0);
	ft_tabclear(cmd->argv);
	cmd->argv = new_argv_tab;
	ft_lstclear(&new_argv, its_just_void);
	return (1);
}

void	swap_str(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
//
char	minimize(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int		weird_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (minimize(s1[i]) != minimize(s2[i]))
			break ;
		i++;
	}
	return (minimize(s1[i]) - minimize(s2[i]));
}

void	sort_files(char **files)
{
	int	i;
	int	j;

	i = 0;
	while (files[i])
	{
		j = i + 1;
		while (files[j])
		{
			if (weird_strcmp(files[i], files[j]) > 0)
				swap_str(&files[i], &files[j]);
			j++;
		}
		i++;
	}
}

int		expand_wildcards_cmd(t_cmd *cmd)
{
	char	**files_name;

	files_name = get_files_name();
	if (!files_name)
		return (0);
	sort_files(files_name);
	while (cmd)
	{
		if (!(expand_wildcards_argv(cmd, files_name) && expand_wildcards_redir(cmd, files_name)))
			return (0);
		cmd = cmd->next;
	}
	ft_tabclear(files_name);
	return (1);
}
