/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 14:36:52 by picheval          #+#    #+#             */
/*   Updated: 2026/01/30 17:39:14 by picheval         ###   ########.fr       */
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

int	compute_exit_code(int status)
{
	int	code;

	code = 0;
	if (WIFEXITED(status))
		code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		code = WTERMSIG(status) + 128;
	return (code);
}

int	wait_cmd_pid(t_cmd *cmd, t_env **env)
{
	int	status;
	int	code;

	code = 0;
	while (cmd->next)
	{
		if (cmd->pid > 0)
			waitpid(cmd->pid, NULL, 0);
		cmd = cmd->next;
	}
	waitpid(cmd->pid, &status, 0);
	code = compute_exit_code(status);
	set_exit_code(env, code);
	return (code);
}
