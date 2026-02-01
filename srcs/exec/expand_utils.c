/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:10:35 by picheval          #+#    #+#             */
/*   Updated: 2026/02/01 00:10:20 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	manage_empty_env_var(t_list **lst, char *line,
	char expand, int size)
{
	char	*dollar;

	if (expand && *line)
		return (0);
	dollar = ft_strdup("$");
	if (!dollar)
	{
		print_sys_error("manage_env_var_token ft_strdup $");
		return (-1);
	}
	if (!lst_add_or_join_back(lst, dollar))
		return (-1);
	return (size);
}

static int	manage_env_var_value(t_list **lst, t_env *env_var, int size,
	char expand)
{
	char	*var_value;

	if (expand)
	{
		if (!expand_env_var(lst, env_var->value))
			return (-1);
		return (size);
	}
	var_value = ft_strdup(env_var->value);
	if (!var_value)
	{
		print_sys_error("manage_env_var_token ft_strdup");
		return (-1);
	}
	if (!lst_add_or_join_back(lst, var_value))
		return (-1);
	return (size);
}

// Cherche la variable d'environnement
// Si il n'y a pas de key valide, on la remplace juste par $ (si pas expand)
// Sinon:
// 		Soit expand == TRUE (pas entre "") et on expand et trim sa value
// 		Soit expand == FALSE et on join juste sa valeur
int	manage_env_var_token(t_data *data, t_list **lst, char *line, char expand)
{
	t_env	*env_var;
	char	*var_key;
	int		size;

	size = count_var_key_size(line);
	if (!size)
		return (manage_empty_env_var(lst, line, expand, size));
	var_key = ft_substr(line, 0, size);
	if (!var_key)
	{
		print_sys_error("manage_env_var_token ft_substr");
		return (-1);
	}
	env_var = find_env_var(data->env, var_key);
	free(var_key);
	if (!env_var || !env_var->value || !ft_strlen(env_var->value))
		return (size);
	return (manage_env_var_value(lst, env_var, size, expand));
}

static int	manage_quoted_token(t_data *data, t_list **lst, char *line)
{
	int		i;
	int		j;
	int		size;
	char	*str;

	i = 0;
	while (line[i])
	{
		j = 0;
		while (line[i + j] != '"' && line[i + j] != '$')
			j++;
		str = ft_substr(line, i, j);
		i += j;
		if (!str)
			return (print_sys_error("manage_quoted_token ft_substr"));
		if (!lst_add_or_join_back(lst, str))
			return (FALSE);
		if (line[i] == '"')
			break ;
		size = manage_env_var_token(data, lst, line + ++i, FALSE);
		if (size < 0)
			return (FALSE);
		i += size;
	}
	return (TRUE);
}

// Manage une chaine de caracteres trouvee dans un token
// Si elle contient des variables d'environement,
// elles sont expand EN GARDANT LES ESPACES
int	manage_string_token(t_data *data, t_list **lst, char *line, int *i)
{
	int		word_size;
	char	*tmp;

	word_size = expand_find_next_word(&(line[*i]));
	if (word_size == 0)
		return (TRUE);
	if (line[*i] == '"')
	{
		if (!manage_quoted_token(data, lst, line + ++(*i)))
			return (FALSE);
	}
	else
	{
		if (line[*i] == '\'')
			tmp = ft_substr(line, ++(*i), word_size - 1);
		else
			tmp = ft_substr(line, *i, word_size);
		if (!tmp)
			return (print_sys_error("manage_string_token ft_substr"));
		if (!lst_add_or_join_back(lst, tmp))
			return (FALSE);
	}
	*i += word_size;
	return (TRUE);
}
