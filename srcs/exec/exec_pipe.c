/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:55:03 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/25 17:09:44 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipe(t_data *data, t_cmd *cmds)
{
	int		pipefd[2];
	t_cmd	*cmd;
	int		save_in;
	int		ret;

	if (cmds->ast)
	{
		int toto = fork();
		if (toto == 0)
		{
			manage_redirections(cmds->redir);
			ret = exec_ast(data, cmds->ast);
			free_data(data, TRUE, FALSE);
			exit(ret);
		}
		waitpid(toto, &ret, 0);
		return (ret);
	}
	cmd = cmds;
	if (!expand_pipe(data, cmd))
		return (FALSE);
	if (!cmd->next && is_builtin(cmd))
		return (exec_builtin(data, cmd, 0));
	save_in = dup(STDIN_FILENO);
	while (cmd)
	{
		if (cmd->next && pipe(pipefd) < 0)
		{
			print_sys_error("pipe");
			break ;
		}
		cmd->pid = fork();
		if (cmd->pid < 0)
		{
			print_sys_error("fork");
			if (cmd->next)
			{
				close(pipefd[0]);
				close(pipefd[1]);
			}
			break ;
		}
		if (cmd->pid == 0)
		{
			close(save_in);
			dfl_signal();
			if (cmd->next)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			if (is_builtin(cmd))
				exec_builtin(data, cmd, 1);
			exec_cmd(data, cmd);
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
	close(0);
	ret = wait_cmd_pid(cmds, &data->env);
	dup2(save_in, STDIN_FILENO);
	close(save_in);
	return (ret);
}
