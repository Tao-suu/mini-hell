/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 14:35:28 by picheval          #+#    #+#             */
/*   Updated: 2026/01/31 18:14:11 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_quoted(char *line, int *i, char c)
{
	int	j;

	j = *i;
	if (line[j] != c)
		return (TRUE);
	j++;
	while (line[j] && line[j] != c)
		j++;
	if (!line[j])
		return (print_matching_error(c));
	*i = j;
	return (TRUE);
}

static int	detect_operator(t_data *data, char *line, int *i,
	t_operator **tmp_op)
{
	t_operator	*operator;

	operator = find_operator_by_value(data->operators, &(line[*i]));
	if (!operator)
		return (FALSE);
	if (*i > 0)
		return (TRUE);
	*tmp_op = operator;
	*i += ft_strlen(operator->value);
	return (TRUE);
}

static t_operator	*find_appropriate_string_op(t_data *data)
{
	t_lexem	*prev_lexem;
	int		i;
	int		j;

	if (!data->head)
		return (data->operators[0]);
	prev_lexem = data->head;
	while (prev_lexem->next)
		prev_lexem = prev_lexem->next;
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (data->operators[i]->before[++j])
			if (data->operators[i]->before[j]->id == prev_lexem->type->id)
				return (data->operators[i]);
	}
	return (data->operators[0]);
}

static int	find_next_word(t_data *data, char *line, t_lexem *new_elem)
{
	t_operator	*tmp_op;
	int			i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
	{
		tmp_op = NULL;
		if (detect_operator(data, line, &i, &tmp_op))
			break ;
		if (!skip_quoted(line, &i, '\'') || !skip_quoted(line, &i, '"'))
			return (-1);
		i++;
	}
	if (i == 0)
		return (0);
	new_elem->value = ft_substr(line, 0, i);
	if (!new_elem->value)
	{
		print_sys_error("ft_substr()");
		return (-1);
	}
	if (!tmp_op)
		tmp_op = find_appropriate_string_op(data);
	new_elem->type = tmp_op;
	return (i);
}

int	manage_line(t_data *data)
{
	int		i;
	int		ret;
	t_lexem	*tmp_elem;

	i = 0;
	ret = 0;
	while (data->line[i])
	{
		while (ft_isspace(data->line[i]))
			i++;
		if (data->line[i] == '#')
			break ;
		tmp_elem = create_lexem_elem();
		if (!tmp_elem)
			return (FALSE);
		ret = find_next_word(data, &(data->line[i]), tmp_elem);
		if (ret <= 0)
		{
			free_lexem_elem(tmp_elem);
			break ;
		}
		add_lexem_elem(&data->head, tmp_elem);
		i += ret;
	}
	return (ret >= 0);
}
