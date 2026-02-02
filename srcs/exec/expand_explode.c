/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_explode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 01:49:34 by picheval          #+#    #+#             */
/*   Updated: 2026/02/02 17:57:40 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	manage_cmd_param_elem_env_var(t_cmd_param **param_elems,
	char *value, int *i, char quote)
{
	int			size;

	size = count_env_var_key_size(value + *i + 1) + 1;
	if (!new_cmd_param(param_elems, ft_substr(value, *i, size), NULL, quote))
		return (FALSE);
	*i += size;
	return (TRUE);
}

static int	explode_skip_quoted_area(char *line, int *ret, char c)
{
	if (line[*ret] != c)
		return (FALSE);
	(*ret)++;
	while (line[*ret] && line[*ret] != c)
		(*ret)++;
	return (TRUE);
}

static int	manage_cmd_param_elem_value(t_cmd_param **param_elems, char *value,
	int *i, char quote)
{
	int			size;

	if (value[*i] == '$')
		return (manage_cmd_param_elem_env_var(param_elems, value, i, quote));
	if (!quote && value[*i] == '*')
	{
		if (!new_cmd_param(param_elems, ft_strdup("*"), NULL, 0))
			return (FALSE);
		(*i)++;
		return (TRUE);
	}
	size = 0;
	while (value[*i + size] && value[*i + size] != '$'
		&& (quote || (value[*i + size] != '"' && value[*i + size] != '\''
				&& value[*i + size] != '*')))
		size++;
	if (!new_cmd_param(param_elems, ft_substr(value, *i, size), NULL, quote))
		return (FALSE);
	*i += size;
	return (TRUE);
}

static int	explode_quoted_param(t_cmd_param **param_elems, char *value,
	int size)
{
	char	*quoted_value;
	int		ret;

	quoted_value = ft_substr(value, 1, size - 1);
	if (!quoted_value)
		return (print_sys_error("explode_cmd_param ft_substr"));
	ret = explode_cmd_param(param_elems, quoted_value, *value);
	free(quoted_value);
	return (ret);
}

int	explode_cmd_param(t_cmd_param **param_elems, char *value, char quote)
{
	int	size;
	int	i;

	i = 0;
	if (!value[0])
		return (manage_cmd_param_elem_value(param_elems, value, &i, quote));
	while (value[i])
	{
		size = 0;
		if (!quote && (explode_skip_quoted_area(value + i, &size, '\'')
				|| explode_skip_quoted_area(value + i, &size, '"')))
		{
			if (!explode_quoted_param(param_elems, value + i, size))
				return (FALSE);
			i += size + 1;
			continue ;
		}
		if (!manage_cmd_param_elem_value(param_elems, value, &i, quote))
			return (FALSE);
	}
	return (TRUE);
}
