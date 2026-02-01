/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:43:19 by tbez--du          #+#    #+#             */
/*   Updated: 2026/02/02 11:40:46 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_is_last(t_redirection *redir, char is_out)
{
	redir = redir->next;
	while (redir)
	{
		if ((is_out && (!ft_strcmp(redir->operator->value, ">>")
					|| !ft_strcmp(redir->operator->value, ">")))
			|| (!is_out && (!ft_strcmp(redir->operator->value, "<")
					|| !ft_strcmp(redir->operator->value, "<<"))))
			return (FALSE);
		redir = redir->next;
	}
	return (TRUE);
}

static int	open_redir_file(t_redirection *redir)
{
	char	*name;

	name = redir->expanded_params->original_value;
	if (!ft_strcmp(redir->operator->value, ">>"))
		return (open(name, O_CREAT | O_APPEND | O_WRONLY, 0644));
	else if (!ft_strcmp(redir->operator->value, ">"))
		return (open(name, O_CREAT | O_TRUNC | O_WRONLY, 0644));
	else if (!ft_strcmp(redir->operator->value, "<<"))
		return (open(redir->heredoc->filename, O_RDONLY));
	return (open(name, O_RDONLY)); // <
}

int	manage_redirections(t_redirection *redir)
{
	int		fd;
	char	*op_value;

	while (redir)
	{
		if ((ft_strcmp(redir->operator->value, "<<") && !redir->expanded_params)
			|| !redir->valid_wild)
			return (print_bash_ambiguous_redirection(redir->name));
		fd = open_redir_file(redir);
		if (fd < 0)
			return (print_bash_cmd_error(NULL, redir->expanded_params->original_value, NULL));
		op_value = redir->operator->value;
		if ((!ft_strcmp(op_value, ">>") || !ft_strcmp(op_value, ">"))
			&& redir_is_last(redir, TRUE))
			dup2(fd, STDOUT_FILENO);
		else if ((!ft_strcmp(op_value, "<") || !ft_strcmp(op_value, "<<"))
			&& redir_is_last(redir, FALSE))
			dup2(fd, STDIN_FILENO);
		close(fd);
		redir = redir->next;
	}
	return (TRUE);
}

static void	exec_redir_ast(t_data *data, t_cmd *cmd)
{
	int	ret;

	if (!manage_redirections(cmd->redir))
	{
		free_data(data, TRUE, FALSE);
		exit(1);
	}
	if (!cmd->ast)
		return ;
	ret = exec_ast(data, cmd->ast);
	free_data(data, TRUE, FALSE);
	exit(ret);
}

void	exec_cmd(t_data *data, t_cmd *cmd)
{
	char	**env;
	int		exit_code;

	// exit(0); // debug
	exec_redir_ast(data, cmd);
	exit_code = 0;
	cmd->path = get_cmd_path(data->env, cmd->argv, &exit_code);
	if (cmd->path && !exit_code)
	{
		env = get_env_tab_from_list(data->env);
		if (!env)
			print_sys_error("get_env_tab_from_list");
		else
		{
			execve(cmd->path, cmd->argv, env);
			perror(NULL);
			ft_tabclear(env);
		}
	}
	free_data(data, TRUE, FALSE);
	exit(exit_code);
}
