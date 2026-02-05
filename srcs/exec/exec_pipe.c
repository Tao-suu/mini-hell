/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:55:03 by tbez--du          #+#    #+#             */
/*   Updated: 2026/02/05 14:14:16 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup_and_close_fds(t_cmd *cmd, int pipefd[2], int mode)
{
	if (!cmd->next)
		return ;
	if (mode == STDOUT_FILENO)
		dup2(pipefd[1], STDOUT_FILENO);
	if (mode == STDIN_FILENO)
		dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
}

static int	create_pipe_fork(t_cmd *cmd, int pipefd[2])
{
	if (cmd->next && pipe(pipefd) < 0)
		return (print_sys_error("pipe"));
	cmd->pid = fork();
	if (cmd->pid < 0)
	{
		dup_and_close_fds(cmd, pipefd, -1);
		return (print_sys_error("fork"));
	}
	return (TRUE);
}

static void	exec_pipe_child(t_data *data, t_cmd *cmd, int pipefd[2],
	int save_in)
{
	if (cmd->pid != 0)
		return ;
	close(save_in);
	dfl_signal();
	dup_and_close_fds(cmd, pipefd, STDOUT_FILENO);
	if (is_builtin(cmd))
		exec_builtin(data, cmd, 1);
	exec_cmd(data, cmd);
}

int	exec_pipe(t_data *data, t_cmd *cmds)
{
	int		pipefd[2];
	t_cmd	*cursor;
	int		save_in;
	int		ret;

	ft_printf("%s", data->color[data->prompt_n++ % 6]);
	if (!expand_pipe(data, cmds) || !expand_wildcards_cmd(cmds))
		return (FALSE);
	//print_final_cmds(cmds);
	if (!cmds->next && is_builtin(cmds))
		return (exec_builtin(data, cmds, 0));
	save_in = dup(STDIN_FILENO);
	cursor = cmds;
	while (cursor)
	{
		if (!create_pipe_fork(cursor, pipefd))
			break ;
		exec_pipe_child(data, cursor, pipefd, save_in);
		dup_and_close_fds(cursor, pipefd, STDIN_FILENO);
		cursor = cursor->next;
	}
	close(STDIN_FILENO);
	ret = wait_cmd_pid(cmds, &data->env);

	int		exit_code;
	exit_code = get_exit_code(data);
	if (exit_code == 130)
		printf("\n");
	else if (exit_code == 131)
		printf("Quit (core dumped)\n");

	dup2(save_in, STDIN_FILENO);
	close(save_in);
	return (ret);
}
