/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:43:19 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/14 22:06:12 by picheval         ###   ########.fr       */
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

static int	test_command_paths(char **path, char *cmd_name, char **cmd_path)
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

static int	find_command_to_execute(char **path, char *cmd_name, char **cmd_path)
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
	ret = test_command_paths(path, cmd_name, cmd_path);
	if (ret && !*cmd_path)
		print_bash_cmd_error(NULL, cmd_name, "command not found");
	return (ret);
}

static char	*get_cmd_path(char **path, char **argv)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (!argv || !argv[0] || !find_command_to_execute(path, argv[0], &cmd_path))
		return (NULL);
	if (cmd_path && access(cmd_path, X_OK))
	{
		print_bash_cmd_error(NULL, argv[0], NULL);
		free(cmd_path);
		cmd_path = NULL;
	}
	return (cmd_path);
}

int	redir_out(t_redirection *red)
{
	int	fd;

	while (red)
	{
		if (ft_strncmp(red->operator->value, ">>", 2))
			fd = open(red->name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else
			fd = open(red->name, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd < 0)
			return (print_bash_cmd_error(NULL, red->name, NULL));
		if (!red->next)
			dup2(fd, STDOUT_FILENO);
		close(fd);
		red = red->next;
	}
	return (TRUE);
}

int	redir_in(t_redirection *red)
{
	int	fd;

	while (red)
	{
		fd = open(red->name, O_RDONLY);
		if (fd < 0)
			return (print_bash_cmd_error(NULL, red->name, NULL));
		if (!red->next)
			dup2(fd, STDIN_FILENO);
		close(fd);
		red = red->next;
	}
	return (TRUE);
}

int	exec_cmd(t_data *data, t_cmd *cmd, char **env, char **path)
{
	//if (!cmd->ast && is_builtin(cmd))
	//	return (exec_builtin(data, cmd));
	if (!redir_in(cmd->in) || !redir_out(cmd->out))
	{
		free_data(data, TRUE);
		exit(1);
	}
	if (cmd->ast)
		exec_ast(data, cmd->ast);
	else
	{
		cmd->path = get_cmd_path(path, cmd->argv);
		if (cmd->path)
		{
			execve(cmd->path, cmd->argv, env);
			perror(NULL);
		}
		free_data(data, TRUE);
	}
	ft_tabclear(env);
	if (path)
		ft_tabclear(path);
	exit(1);
}
