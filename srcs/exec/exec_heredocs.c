/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:16:25 by picheval          #+#    #+#             */
/*   Updated: 2026/01/25 17:07:33 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	manage_heredoc(t_heredoc *elem)
{
	char	*line;
	size_t	delim_size;
	int		fd;

	delim_size = ft_strlen(elem->delimiter);
	fd = open(elem->filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (print_sys_error("manage_heredoc tmp file"));
	while (42)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, elem->delimiter, delim_size))
		{
			if (line)
				free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
	}
	close(fd);
	if (g_signal)
		return (FALSE);
	return (TRUE);
}

int	exec_heredocs(t_data *data)
{
	t_heredoc	*lst;
	pid_t		pid;
	int			ret;

	lst = data->heredocs;
	pid = fork();
	if (pid < 0)
		return (print_sys_error("fork"));
	if (pid == 0)
	{
		heredoc_signal();
		ret = TRUE;
		while (lst)
		{
			ret = manage_heredoc(lst);
			if (!ret)
				break ;
			lst = lst->next;
		}
		free_data(data, TRUE, FALSE);
		exit(ret);
	}
	waitpid(pid, &ret, 0);
	return (compute_exit_code(ret));
}
