/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:12:34 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/25 21:31:17 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_dup(int flag, int *std)
{
	if (flag)
		return ;
	dup2(std[0], 0);
	dup2(std[1], 1);
	close(std[0]);
	close(std[1]);
}

static int	exec_builtin_cmd(t_data *data, t_cmd *cmd, int flag, int fd[2])
{
	if (!ft_strcmp(cmd->argv[0], "exit"))
	{
		close_dup(flag, fd);
		return (builtin_exit(data, cmd, flag));
	}
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (builtin_cd(&data->env, cmd));
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (builtin_echo(cmd));
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (builtin_env(data->env));
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (builtin_unset(data->env, cmd));
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (builtin_export(&data->env, cmd));
	return (1);
}

static int	quit_properly(t_data *data, int flag, int fd[2], int ret)
{
	if (flag)
	{
		free_data(data, TRUE, FALSE);
		exit(ret);
	}
	close_dup(flag, fd);
	set_exit_code(&(data->env), ret);
	return (ret);
}

int	exec_builtin(t_data *data, t_cmd *cmd, int flag)
{
	int	ret;
	int	fd[2];

	if (!flag)
	{
		fd[0] = dup(0);
		fd[1] = dup(1);
	}
	if (!manage_redirections(cmd->redir))
		return (quit_properly(data, flag, fd, 1));
	ret = exec_builtin_cmd(data, cmd, flag, fd);
	return (quit_properly(data, flag, fd, ret));
}

int	is_builtin(t_cmd *cmd)
{
	if (!cmd->argv || !cmd->argv[0])
		return (FALSE);
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (TRUE);
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (TRUE);
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (TRUE);
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (TRUE);
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (TRUE);
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (TRUE);
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (TRUE);
	return (FALSE);
}
