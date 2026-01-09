/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:55:03 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/09 19:13:54 by tbez--du         ###   ########.fr       */
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
	int	code = 0;
	if (WIFEXITED(ret))
		code = WEXITSTATUS(ret);
	else if (WIFSIGNALED(ret))
		code = WTERMSIG(ret);
	return (code);
}

char	**get_path(t_data *data)
{
	char	*path_var;

	path_var = get_env_var(data, "PATH");
	if (!path_var)
		return (NULL);
	return (ft_split(path_var, ':'));
}

int	exec_pipe(t_data *data, t_cmd *cmds)
{
	char	**path;
	int		pipefd[2];
	t_cmd	*cmd;
	int		save_in;
	int		ret;

	if (cmds->ast)
		return (exec_ast(data, cmds->ast));
	cmd = cmds;
	//expand_all_cmd(cmd);
	//if (!cmd->next && is_builtin(cmd))
	//	return (exec_cmd(data, cmd, NULL));
	save_in = dup(STDIN_FILENO);
	while (cmd)
	{
		if (cmd->next)
			pipe(pipefd);
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			close(save_in);
			path = get_path(data);
			dfl_signal();
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
	ret = wait_cmd_pid(cmds);
	dup2(save_in, STDIN_FILENO);
	close(save_in);
	//dprintf(2, "fini d'attendre\n");
	return (ret);
}
