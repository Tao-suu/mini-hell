/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbez--du <tbez--du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 17:13:08 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/31 17:16:05 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	swap_str(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static char	minimize(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int	weird_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (minimize(s1[i]) != minimize(s2[i]))
			break ;
		i++;
	}
	return (minimize(s1[i]) - minimize(s2[i]));
}

void	sort_files(char **files)
{
	int	i;
	int	j;

	i = 0;
	while (files[i])
	{
		j = i + 1;
		while (files[j])
		{
			if (weird_strcmp(files[i], files[j]) > 0)
				swap_str(&files[i], &files[j]);
			j++;
		}
		i++;
	}
}
