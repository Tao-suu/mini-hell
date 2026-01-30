/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:29:44 by picheval          #+#    #+#             */
/*   Updated: 2026/01/30 17:49:04 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_paths(t_env *env, char ***paths)
{
	t_env	*path_var;

	path_var = find_env_var(env, "PATH");
	if (!path_var || !path_var->value)
		return (TRUE);
	*paths = ft_split(path_var->value, ':');
	if (!*paths)
		return (print_sys_error("get_path ft_split"));
	return (TRUE);
}

static int	test_cmd_paths(t_env *env, char *cmd_name, char **cmd_path)
{
	char	**paths;
	int		ret;
	int		i;

	paths = NULL;
	if (!get_paths(env, &paths))
		return (FALSE);
	i = -1;
	ret = TRUE;
	while (*cmd_name && paths && paths[++i])
	{
		if (!merge_with_sep(cmd_path, paths[i], cmd_name, "/"))
		{
			ret = FALSE;
			break ;
		}
		if (!access(*cmd_path, F_OK))
			break ;
		free(*cmd_path);
		*cmd_path = NULL;
	}
	if (paths)
		ft_tabclear(paths);
	return (ret);
}

static int	create_cmd_path(t_env *env, char *cmd_name, char **cmd_path,
	int *exit_code)
{
	int		ret;

	if (ft_strchr(cmd_name, '/'))
	{
		if (access(cmd_name, F_OK) < 0)
		{
			*exit_code = 127;
			return (print_bash_cmd_error(NULL, cmd_name, NULL));
		}
		*cmd_path = ft_strdup(cmd_name);
		if (!*cmd_path)
			return (print_sys_error("ft_strdup malloc"));
		return (TRUE);
	}
	ret = 1;
	if (ft_strcmp(".", cmd_name))
		ret = test_cmd_paths(env, cmd_name, cmd_path);
	if (ret && !*cmd_path)
	{
		*exit_code = 127;
		print_bash_cmd_error(NULL, cmd_name, "command not found");
	}
	return (ret);
}

char	*get_cmd_path(t_env *env, char **argv, int *exit_code)
{
	char		*cmd_path;
	struct stat	st;

	cmd_path = NULL;
	if (!argv || !argv[0]
		|| !create_cmd_path(env, argv[0], &cmd_path, exit_code))
		return (NULL);
	if (!cmd_path)
		return (NULL);
	if (stat(cmd_path, &st) == -1)
		print_sys_error("stat");
	else if (S_ISDIR(st.st_mode))
		print_bash_cmd_error(NULL, argv[0], "Is a directory");
	else if (access(cmd_path, X_OK))
		print_bash_cmd_error(NULL, argv[0], NULL);
	else
		return (cmd_path);
	free(cmd_path);
	*exit_code = 126;
	return (NULL);
}
