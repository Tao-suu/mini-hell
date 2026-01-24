/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbez--du <tbez--du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:24:12 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/24 15:45:24 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pattern(char *file, char *pattern)
{
	int	i;

	i = 0;
	while (*pattern && file[i])
	{
		if (*pattern == '*')
		{
			pattern++;
			while (file[i] && file[i] != *pattern)
				i++;
		}
		else
		{
			if (*pattern != file[i])
				return (0);
			i++;
			pattern++;
		}
	}
	if (*pattern == '*' && !pattern[1])
		return (1);
	if (*pattern != file[i])
		return (0);
	return (1);
}

int	expand_wildcards(char **str, char **files)
{
	char	*new;

	if (!ft_strchr(*str, '*'))
		return (1);
	new = ft_calloc(1, 1);
	while (*files)
	{
		if (check_pattern(*files, *str))
			ft_strjoin(new, *files);
		files++;
	}
	free(*str);
	*str = new;
	printf("%s\n", new);
	return (1);
}

int		expand_wildcards_argv(t_cmd *cmd, char **files_name)
{
	int		i;
	
	if (!files_name)
		return (0);
	i = 0;
	while (cmd->argv[i])
	{
		if (!expand_wildcards(cmd->argv + i, files_name))
			return (0);
		i++;
	}
	return (1);
}

int		expand_wildcards_cmd(t_cmd *cmd)
{
	char	**files_name;

	files_name = get_files_name();
	if (!files_name)
		return (0);
	while (cmd)
	{
		if (!expand_wildcards_argv(cmd, files_name))
			return (0);
		cmd = cmd->next;
	}
	return (1);
}
