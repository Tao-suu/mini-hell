/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:17:04 by picheval          #+#    #+#             */
/*   Updated: 2026/01/25 18:01:39 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putendl_fd(char *s, int fd)
{
	ssize_t	s_size;

	s_size = ft_putstr_fd(s, fd);
	if (s_size < 0 || ft_putchar_fd('\n', fd) < 0)
		return (-1);
	return (s_size + 1);
}
