/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbez--du <tbez--du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:24:12 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/26 18:48:24 by tbez--du         ###   ########.fr       */
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

int		retokenise(t_cmd *cmd, int index)
{
	char	**splitted;
	char	**new;
	int		slen;
	int		i;
	int		j;
	int		k;

	splitted = ft_split(cmd->argv[index], ' ');
	if (!splitted)
		return (0);
	slen = 0;
	while (splitted[slen])
		slen++;
	new = ft_calloc(cmd->argc + slen, sizeof(char *));
	if (!new)
		return (0);
	i = 0;
	j = 0;
	k = 0;
	while (cmd->argv[i])
	{
		if (i == index)
		{
			if (!*splitted)
			{
				new[j++] = ft_strdup(cmd->argv[index]);
				continue ;
			}
			while (splitted[k])
				new[j++] = ft_strdup(splitted[k++]);
		}
		else
			new[j++] = ft_strdup(cmd->argv[i]);
		i++;
	}
	new[j] = NULL;
	cmd->argc = cmd->argc + slen - 1;
	ft_tabclear(splitted);
	ft_tabclear(cmd->argv);
	cmd->argv = new;
	return (1);
	/*
	char	**splitted;
	char	**tmp;
	int		i;
	int 	len;
	int		slen;

	i = 0;
	len = 0;
	sp3litted = ft_split(cmd->argv[index], ' ');
	if (!splitted)
		return (0);
	while (cmd->argv[i++])
		len++;
	i = 0;
	while (splitted[i++])
		len++;
	tmp = ft_calloc(len + 1, sizeof(char *));
	if (!tmp)
		return (ft_tabclear(splitted), 0);
	i = 0;
	slen = 0;
	while (i < len)
	{
		if (i == index)
		{
			while (splitted[i - index])
			{
				tmp[i] = ft_strdup(splitted[i - index]);
				slen++;
				i++;
			}
		}
		else
		{
			tmp[i] = ft_strdup(cmd->argv[i - slen]);
			i++;
		}
	}
	tmp[i] = NULL;
	ft_tabclear(cmd->argv);
	ft_tabclear(splitted);
	cmd->argv = tmp;
	return (1);*/
}

int	expand_wildcards(char **str, char **files)
{
	char	*new;
	int		total_size;
	int		i;
	int		flag;

	flag = 0;
	if (!ft_strchr(*str, '*'))
		return (1);
	total_size = 0;
	i = 0;
	while (files[i])
	{
		if (check_pattern(files[i], *str))
			total_size += ft_strlen(files[i]) + 1;
		i++;
	}
	new = ft_calloc(total_size, 1);
	if (!new)
		return (0);
	i = 0;
	while (files[i])
	{
		if (check_pattern(files[i], *str))
		{
			flag = 1;
			ft_strlcat(new, files[i], total_size);
			ft_strlcat(new, " ", total_size);
		}
		i++;
	}
	if (!flag)
	{
		free(new);
		return (1);
	}
	free(*str);
	*str = new;
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
		if (ft_strchr(cmd->argv[i], '*'))
		{
			if (expand_wildcards(cmd->argv + i, files_name))
			{
				if (!retokenise(cmd, i))
					return (0);
			}
			else
				return (0);
		}
		i++;
	}
	return (1);
}

int		expand_wildcards_cmd(t_cmd *cmd)
{
	char	**files_name;

	(void)cmd;
	files_name = get_files_name();
	if (!files_name)
		return (0);
	while (cmd)
	{
		if (!expand_wildcards_argv(cmd, files_name))
			return (0);
		cmd = cmd->next;
	}
	ft_tabclear(files_name);
	return (1);
}
