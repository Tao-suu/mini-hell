/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:55:03 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/14 18:07:46 by picheval         ###   ########.fr       */
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

static char	**get_path(t_env *env)
{
	t_env	*path_var;

	path_var = find_env_var(env, "PATH");
	if (!path_var || !path_var->value)
		return (NULL);
	return (ft_split(path_var->value, ':'));
}

int	exec_pipe(t_data *data, t_cmd *cmds)
{
	char	**path;
	char	**env;
	int		pipefd[2];
	t_cmd	*cmd;
	int		save_in;
	int		ret;

	if (cmds->ast)
		return (exec_ast(data, cmds->ast));
	cmd = cmds;
	//expand_all_cmd(cmd);
	if (!cmd->next && is_builtin(cmd))
		return (exec_builtin(data, cmd, 0));
	path = get_path(data->env);
	env = get_env_tab_from_list(data->env);
	if (!env)
		return (print_sys_error("get_env_tab_from_list"));
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
			exec_cmd(data, cmd, env, path);
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
	if (path)
		ft_tabclear(path);
	ft_tabclear(env);
	ret = wait_cmd_pid(cmds);
	dup2(save_in, STDIN_FILENO);
	close(save_in);
	return (ret);
}
