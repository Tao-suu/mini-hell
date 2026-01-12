/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:12:34 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/12 07:20:58 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_data *data, t_cmd *cmd, int flag)
{
	int	ret;
	int	fd[2];

	if (!ft_strcmp(cmd->argv[0], "exit"))
		builtin_exit(data, cmd);
	fd[0] = dup(0);
	fd[1] = dup(1);
	redir_in(cmd->in);
	redir_out(cmd->out);

	if (!ft_strcmp(cmd->argv[0], "pwd"))
		ret = builtin_pwd(data->env);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		ret = builtin_cd(&data->env, cmd);
	else if (!ft_strcmp(cmd->argv[0], "echo"))
	 	ret = builtin_echo(cmd);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		ret = builtin_env(data->env);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		ret = builtin_unset(data->env, cmd);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		ret = builtin_export(&data->env, cmd);
	else
		ret = 1;
	dup2(1, fd[1]);
	dup2(0, fd[0]);
	close(fd[0]);
	close(fd[1]);
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
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (1);
	return (0);
}
