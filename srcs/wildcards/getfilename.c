/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getfilename.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:23:02 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/31 18:32:06 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**realloc_arr(char **arr)
{
	char	**new;
	int		i;

	if (!arr)
		return (ft_calloc(2, sizeof(char *)));
	i = 0;
	while (arr[i])
		i++;
	new = ft_calloc(i + 2, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		new[i] = arr[i];
		i++;
	}
	free(arr);
	return (new);
}

static char	**get_filename_arr(DIR *dir)
{
	char		**ret;
	t_dirent	*file;
	int			i;

	i = 0;
	ret = NULL;
	while (1)
	{
		file = readdir(dir);
		if (!file)
			break ;
		ret = realloc_arr(ret);
		if (!ret)
			return (NULL);
		ret[i] = ft_strdup(file->d_name);
		if (!ret[i])
		{
			ft_tabclear(ret);
			return (NULL);
		}
		i++;
	}
	if (!ret)
		ret = ft_calloc(1, sizeof(char *));
	return (ret);
}

char	**get_files_name(void)
{
	char	pwd[5000];
	DIR		*cdir;
	char	**files;

	if (!getcwd(pwd, 5000))
		return (NULL);
	cdir = opendir(pwd);
	if (!cdir)
		return (NULL);
	files = get_filename_arr(cdir);
	closedir(cdir);
	return (files);
}
