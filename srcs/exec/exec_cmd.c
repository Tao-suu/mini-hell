/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:43:19 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/17 12:21:26 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*get_cmd_path(char **path, char *cmd)
// {
// 	char	*ret;
// 	size_t	len;

// 	if (!cmd)
// 		return (ft_strdup(""));
// 	if ((!path || !path[0]) && access(cmd, X_OK) >= 0)
// 		return (ft_strdup(cmd));
// 	while (path && *path)
// 	{
// 		len = ft_strlen(cmd) + ft_strlen(*path) + 2;
// 		ret = (char *)ft_calloc(len, sizeof(char));
// 		if (!ret)
// 			return (NULL);
// 		ft_strlcpy(ret, *path, len);
// 		ft_strlcat(ret, "/", len);
// 		ft_strlcat(ret, cmd, len);
// 		if (access(ret, X_OK) >= 0)
// 			return (ret);
// 		free(ret);
// 		path++;
// 	}
// 	return (ft_strdup(cmd));
// }

static int	test_cmd_paths(char **path, char *cmd_name, char **cmd_path)
{
	size_t	size;
	int		i;

	i = -1;
	while (path && path[++i])
	{
		size = ft_strlen(cmd_name) + ft_strlen(path[i]) + 2;
		*cmd_path = (char *)ft_calloc(size, sizeof(char));
		if (!*cmd_path)
			return (print_sys_error("ft_strjoin malloc"));
		ft_strlcpy(*cmd_path, path[i], size);
		ft_strlcat(*cmd_path, "/", size);
		ft_strlcat(*cmd_path, cmd_name, size);
		if (!access(*cmd_path, F_OK))
			break ;
		free(*cmd_path);
		*cmd_path = NULL;
	}
	return (TRUE);
}

static int	create_cmd_path(char **path, char *cmd_name, char **cmd_path)
{
	int		ret;

	if (cmd_name[0] == '/' || !ft_strncmp(cmd_name, "./", 2))
	{
		if (access(cmd_name, F_OK) < 0)
			return (print_bash_cmd_error(NULL, cmd_name, NULL));
		*cmd_path = ft_strdup(cmd_name);
		if (!*cmd_path)
			return (print_sys_error("ft_strdup malloc"));
		return (TRUE);
	}
	ret = test_cmd_paths(path, cmd_name, cmd_path);
	if (ret && !*cmd_path)
		print_bash_cmd_error(NULL, cmd_name, "command not found");
	return (ret);
}

static char	*get_cmd_path(char **path, char **argv)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (!argv || !argv[0] || !create_cmd_path(path, argv[0], &cmd_path))
		return (NULL);
	if (cmd_path && access(cmd_path, X_OK))
	{
		print_bash_cmd_error(NULL, argv[0], NULL);
		free(cmd_path);
		cmd_path = NULL;
	}
	return (cmd_path);
}

static char	**get_path(t_env *env)
{
	t_env	*path_var;

	path_var = find_env_var(env, "PATH");
	if (!path_var || !path_var->value)
		return (NULL);
	return (ft_split(path_var->value, ':'));
}

static int	redir_is_last(t_redirection *redir, char is_out)
{
	redir = redir->next;
	while (redir)
	{
		if ((is_out && (ft_strcmp(redir->operator->value, ">>")
				|| ft_strcmp(redir->operator->value, ">")))
			|| (!is_out && (ft_strcmp(redir->operator->value, "<<")
				|| ft_strcmp(redir->operator->value, "<"))))
			return (FALSE);
		redir = redir->next;
	}
	return (TRUE);
}

int	manage_redirections(t_redirection *redir)
{

	int	fd;

	while (redir)
	{
		if (!ft_strcmp(redir->operator->value, ">>"))
			fd = open(redir->name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (!ft_strcmp(redir->operator->value, ">"))
			fd = open(redir->name, O_CREAT | O_APPEND | O_WRONLY, 0644);
		else if (!ft_strcmp(redir->operator->value, "<<"))
			// TODO: gerer le delimiter de <<
			fd = open(redir->name, O_RDONLY);
		else
			fd = open(redir->name, O_RDONLY); // <

		if (fd < 0)
			return (print_bash_cmd_error(NULL, redir->name, NULL));
		
		if ((!ft_strcmp(redir->operator->value, ">>")
				|| !ft_strcmp(redir->operator->value, ">"))
			&& redir_is_last(redir, TRUE))
			dup2(fd, STDOUT_FILENO);
		else if ((!ft_strcmp(redir->operator->value, "<<")
				|| !ft_strcmp(redir->operator->value, "<"))
			&& redir_is_last(redir, FALSE))
			dup2(fd, STDIN_FILENO);

		close(fd);
		redir = redir->next;
	}
	return (TRUE);
}

void	exec_cmd(t_data *data, t_cmd *cmd)
{
	char	**path;
	char	**env;
	
	if (!manage_redirections(cmd->redir))
	{
		free_data(data, TRUE);
		exit(1);
	}
	if (cmd->ast)
	{
		exec_ast(data, cmd->ast);
		exit(1);
	}
	path = get_path(data->env);
	cmd->path = get_cmd_path(path, cmd->argv);
	if (path)
		ft_tabclear(path);
	if (cmd->path)
	{
		env = get_env_tab_from_list(data->env);
		if (!env)
			print_sys_error("get_env_tab_from_list");
		else
		{
			execve(cmd->path, cmd->argv, env);
			perror(NULL);
			ft_tabclear(env);
		}
	}
	free_data(data, TRUE);
	exit(1);
}
