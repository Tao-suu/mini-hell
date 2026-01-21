/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:55:03 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/21 06:42:52 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_exit_code(t_env **env, int code)
{
	char	*value;
	int		ret;

	value = ft_itoa(code);
	if (!value)
		return (print_sys_error("ft_itoa"));
	ret = create_or_update_env(env, "?", value, STATE_HIDDEN);
	free(value);
	return (ret);
}

static int	wait_cmd_pid(t_cmd *cmd, t_env **env)
{
	int	ret;
	int	code;

	code = 0;
	while (cmd->next)
	{
		waitpid(cmd->pid, NULL, 0);
		cmd = cmd->next;
	}
	waitpid(cmd->pid, &ret, 0);
	if (WIFEXITED(ret))
		code = WEXITSTATUS(ret);
	else if (WIFSIGNALED(ret))
		code = WTERMSIG(ret);
	set_exit_code(env, code);
	return (code);
}

int	exec_pipe(t_data *data, t_cmd *cmds)
{
	int		pipefd[2];
	t_cmd	*cmd;
	int		save_in;
	int		ret;

	if (cmds->ast)
		return (exec_ast(data, cmds->ast));
	cmd = cmds;
	if (!expand_pipe(data, cmd))
		return (FALSE);
	if (!cmd->next && is_builtin(cmd))
		return (exec_builtin(data, cmd, 0));
	save_in = dup(STDIN_FILENO);
	while (cmd)
	{
		if (cmd->next)
			pipe(pipefd);
		cmd->pid = fork();
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
				return (exec_builtin(data, cmd, 1));
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
	ret = wait_cmd_pid(cmds, &data->env);
	dup2(save_in, STDIN_FILENO);
	close(save_in);
	return (ret);
}
