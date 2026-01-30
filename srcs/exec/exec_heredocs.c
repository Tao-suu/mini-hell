/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:16:25 by picheval          #+#    #+#             */
/*   Updated: 2026/01/30 17:56:43 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	manage_heredoc(t_data *data, t_heredoc *elem)
{
	char	*line;
	int		fd;

	fd = open(elem->filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (print_sys_error("manage_heredoc tmp file"));
	while (42)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, elem->delimiter))
			break ;
		ft_putendl_fd(line, fd);
	}
	close(fd);
	if (line)
		free(line);
	if (g_signal)
	{
		g_signal = 0;
		return (FALSE);
	}
	else if (!line)
		print_bash_heredoc_warning(data->nb_execution, elem->delimiter);
	return (TRUE);
}

static int	exec_heredocs_list(t_data *data)
{
	t_heredoc	*lst;
	int			ret;

	lst = data->heredocs;
	ret = TRUE;
	while (lst)
	{
		ret = manage_heredoc(data, lst);
		if (!ret)
			break ;
		lst = lst->next;
	}
	free_data(data, TRUE, FALSE);
	return (ret);
}

int	exec_heredocs(t_data *data)
{
	pid_t		pid;
	int			ret;
	int			status;

	if (!data->heredocs)
		return (TRUE);
	pid = fork();
	if (pid < 0)
		return (print_sys_error("fork"));
	if (pid == 0)
	{
		heredoc_signal();
		ret = exec_heredocs_list(data);
		exit(ret);
	}
	waitpid(pid, &status, 0);
	return (compute_exit_code(status));
}
