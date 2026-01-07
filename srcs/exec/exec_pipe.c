/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbez--du <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:55:03 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/07 09:36:01 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_cmd_pid(t_cmd *cmd)
{
	int	ret;

	while (cmd->next)
	{
		waitpid(cmd->pid, NULL, 0);
		cmd = cmd->next;
	}
	waitpid(cmd->pid, &ret, 0);
	return (WEXITSTATUS(ret));
}

char **get_path(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (!ft_strncmp(data->env[i], "PATH=", 5))
			return (ft_split(data->env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

int	exec_pipe(t_data *data, t_cmd *cmds)
{
	char	**path; 
	int		pipefd[2];
	t_cmd	*cmd;

	if (cmds->ast)
		return (exec_ast(data, cmds->ast));
	cmd = cmds;
	//expand_all_cmd(cmd);
	//if (!cmd->next && is_builtin(cmd))
	//	return (exec_builtin(data, cmd));
	int	save_in = dup(STDIN_FILENO);
	while (cmd)
	{
		if (cmd->next)
			pipe(pipefd);
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			close(save_in);
			path = get_path(data);
			if (cmd->next)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			exec_cmd(data, cmd, path);
		}
		else
		{
			if (cmd->next)
			{
				close(pipefd[1]);
				dup2(pipefd[0], STDIN_FILENO);
				close(pipefd[0]);
			}
		}
		cmd = cmd->next;
	}
	int ret = wait_cmd_pid(cmds);
	dup2(save_in, STDIN_FILENO);
	close(save_in);
	//dprintf(2, "fini d'attendre\n");
	return ret;
}
