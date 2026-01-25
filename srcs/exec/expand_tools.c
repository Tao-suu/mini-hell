/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:12:53 by picheval          #+#    #+#             */
/*   Updated: 2026/01/25 22:19:06 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_var_key_size(char *arg)
{
	int	size;

	size = 0;
	if (arg[0] == '?' || ft_isdigit(arg[0]))
		return (1);
	if (!ft_isalpha(arg[size]) && arg[size] != '_')
		return (size);
	size++;
	while (arg[size])
	{
		if (!ft_isalnum(arg[size]) && arg[size] != '_')
			return (size);
		size++;
	}
	return (size);
}

int	expand_skip_quoted_area(char *line, int *ret, char c)
{
	if (line[*ret] != c)
		return (FALSE);
	(*ret)++;
	while (line[*ret] && line[*ret] != c)
		(*ret)++;
	return (TRUE);
}

int	expand_find_next_word(char *line)
{
	int	ret;

	ret = 0;
	while (line[ret] && !ft_isspace(line[ret]) && line[ret] != '$')
	{
		if (ret > 0 && (line[ret] == '"' || line[ret] == '\''))
			return (ret);
		if (expand_skip_quoted_area(line, &ret, '\'')
			|| expand_skip_quoted_area(line, &ret, '"'))
			return (ret);
		ret++;
	}
	return (ret);
}

// Recupere chaque mot d'une variable d'environnement
// Supprime les espaces surnumeraires
int	expand_env_var(t_list **lst, char *line)
{
	int		i;
	int		ret;
	char	*tmp;

	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		ret = 0;
		while (line[i + ret] && !ft_isspace(line[i + ret]))
			ret++;
		if (!ret)
			continue ;
		tmp = ft_substr(line, i, ret);
		if (!tmp)
			return (print_sys_error("expand_env_var ft_substr"));
		if (!lst_add_or_join_back(lst, tmp))
			return (FALSE);
		i += ret;
		if (line[i])
			create_lst_empty(lst);
	}
	return (TRUE);
}
