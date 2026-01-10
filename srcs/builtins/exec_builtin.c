/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbez--du <tbez--du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:12:34 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/10 12:56:20 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_data *data, t_cmd *cmd, int flag)
{
	int	ret;
	int	fd[2];

	fd[0] = dup(0);
	fd[1] = dup(1);
	redir_in(cmd->in);
	redir_out(cmd->out);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		ret = builtin_pwd(data);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		ret = builtin_env(data);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		ret = builtin_exit(data);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		ret = builtin_cd(data, cmd);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		ret = builtin_unset(data, cmd);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		ret = builtin_export(data, cmd);
	else
		ret = 1;
	dup2(1, fd[1]);
	dup2(0, fd[0]);
	if (flag)
	{
		free_data(data, TRUE);
		exit(ret);
	}
	return (ret);
}

int	is_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (1);
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (1);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (1);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (1);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (1);
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (1);
	return (0);
}
