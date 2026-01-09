/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbez--du <tbez--du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:12:34 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/09 18:49:32 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_data *data, t_cmd *cmd)
{
	int	ret;
	int	fd[2];

	fd[0] = dup(0);
	fd[1] = dup(1);
	redir_in(cmd->in);
	redir_out(cmd->out);
	if (ft_strcmp(cmd->argv[0], "pwd"))
		ret = pwd(data);
	else
		ret = 1;
	dup2(1, fd[1]);
	dup2(0, fd[0]);
	return (ret);
}

int	is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "pwd"))
		return (1);
	return (0);
}
