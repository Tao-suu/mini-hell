/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:43:19 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/09 19:13:24 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(char **path, char *cmd)
{
	char	*ret;
	size_t	len;

	if (!cmd)
		return (ft_strdup(""));
	if ((!path || !path[0]) && access(cmd, X_OK) >= 0)
		return (ft_strdup(cmd));
	while (path && *path)
	{
		len = ft_strlen(cmd) + ft_strlen(*path) + 2;
		ret = malloc(len);
		if (!ret)
			return (NULL);
		ft_strlcpy(ret, *path, len);
		ft_strlcat(ret, "/", len);
		ft_strlcat(ret, cmd, len);
		if (access(ret, X_OK) >= 0)
			return (ret);
		free(ret);
		path++;
	}
	return (ft_strdup(cmd));
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
		{
			perror("");
			return (0);
		}
		if (!red->next)
			dup2(fd, STDOUT_FILENO);
		close(fd);
		red = red->next;
	}
	return (1);
}

int	redir_in(t_redirection *red)
{
	int	fd;

	while (red)
	{
		fd = open(red->name, O_RDONLY);
		if (fd < 0)
		{
			perror("");
			return (0);
		}
		if (!red->next)
			dup2(fd, STDIN_FILENO);
		close(fd);
		red = red->next;
	}
	return (1);
}

int	exec_cmd(t_data *data, t_cmd *cmd, char **path)
{
	//if (!cmd->ast && is_builtin(cmd))
	//	return (exec_builtin(data, cmd));
	if (!redir_in(cmd->in))
		exit(1);
	if (!redir_out(cmd->out))
		exit(1);
	if (cmd->ast)
		exec_ast(data, cmd->ast);
	else
	{
		cmd->path = get_cmd_path(path, cmd->argv[0]);
		execve(cmd->path, cmd->argv, data->env);
		free_data(data, TRUE);
		perror("");
	}
	ft_tabclear(path);
	exit(1);
}
