/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 22:31:42 by picheval          #+#    #+#             */
/*   Updated: 2025/11/11 20:49:28 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_delete_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

static int	compute_nb_elem(char const *s, char c)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			ret++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (ret);
}

static char	*get_elem(char const *s, char c, unsigned int *i)
{
	size_t	j;
	char	*ret;

	while (s[*i] && s[*i] == c)
		(*i)++;
	j = 0;
	while (s[*i + j] && s[*i + j] != c)
		j++;
	ret = ft_substr(s, *i, j);
	*i += j;
	return (ret);
}

char	**ft_split(const char *s, char c)
{
	char			**tab;
	int				nb_elem;
	unsigned int	i;
	int				j;

	nb_elem = compute_nb_elem(s, c);
	tab = (char **)malloc(sizeof(char *) * (nb_elem + 1));
	if (!tab)
		return (NULL);
	ft_memset((void *)tab, '\0', sizeof(char *) * (nb_elem + 1));
	i = 0;
	j = -1;
	while (++j < nb_elem)
	{
		tab[j] = get_elem(s, c, &i);
		if (!tab[j])
		{
			ft_delete_tab(tab);
			return (NULL);
		}
	}
	return (tab);
}
