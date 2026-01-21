/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:36:38 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/21 09:50:42 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_var_key_size(char *arg)
{
	int size;
	
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

static int	skip_quoted_area(char *line, int *ret, char c)
{
	if (line[*ret] != c)
		return (FALSE);
	(*ret)++;
	while (line[*ret] && line[*ret] != c)
		(*ret)++;
	return (TRUE);
}

static int	find_next_word(char *line)
{
	int	ret;

	ret = 0;
	while (line[ret] && !ft_isspace(line[ret]) && line[ret] != '$')
	{
		if (ret > 0 && (line[ret] == '"' || line[ret] == '\''))
			return (ret);
		if (skip_quoted_area(line, &ret, '\'')
			|| skip_quoted_area(line, &ret, '"'))
			return (ret);
		ret++;
	}
	return (ret);
}

// Recupere chaque mot d'une variable d'environnement
// Supprime les espaces surnumeraires
int	expand_env_var(char *line, t_list **lst)
{
	int		i;
	int		ret;

	i = 0;
	// dprintf(2, "expand env var\n");
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		ret = 0;
		while (line[i + ret] && !ft_isspace(line[i + ret]))
			ret++;
		if (!ret)
			continue ;
		char *tmp = ft_substr(line, i, ret);
		if (!tmp)
			return (print_sys_error("expand_env_var ft_substr"));
		// dprintf(2, "found var env value %s\n", tmp);

		if (!lst_add_or_join_back(lst, tmp))
		{
			free(tmp);
			return (FALSE);
		}
		i += ret;
		if (line[i])
			create_lst_empty(lst);
	}
	return (TRUE);
}

// Cherche la variable d'environnement
// Si il n'y a pas de key valide, on la remplace juste par $
// Sinon:
// 		Soit expand == TRUE (elle n'est pas entre "") et on expand et trim sa value
// 		Soit expand == FALSE et on join juste sa valeur
static int manage_env_var_token(t_data *data, t_list **lst, char *line, char expand)
{
	t_env	*tmp_env_var;
	char	*var_key;
	int		size;

	size = count_var_key_size(line);
	if (!size)
	{
		// dprintf(2, "no key $\n");
		var_key = ft_strdup("$");
		if (!var_key)
		{
			print_sys_error("manage_env_var_token ft_strdup $");
			return (-1);
		}
		// on ne free pas var_key si lst_add_or_join_back return FALSE
		// car la fonction l'a forcement deja fait
		if (!lst_add_or_join_back(lst, var_key))
			return (-1);
		return (size);
	}
	// dprintf(2, "Size %d\n", size);
	var_key = ft_substr(line, 0, size);
	if (!var_key)
	{
		print_sys_error("manage_env_var_token ft_substr");
		return (-1);
	}
	// dprintf(2, "var_key %s\n", var_key);
	tmp_env_var = find_env_var(data->env, var_key);
	free(var_key);
	if (tmp_env_var && tmp_env_var->value)
	{
		// dprintf(2, "var_value %s\n", tmp_env_var->value);
		if (expand)
		{
			if (!expand_env_var(tmp_env_var->value, lst))
				return (-1);
		}
		else
		{
			var_key = ft_strdup(tmp_env_var->value);
			if (!var_key)
			{
				print_sys_error("manage_env_var_token ft_strdup");
				return (-1);
			}
			if (!lst_add_or_join_back(lst, var_key))
				return (-1);
		}
	}
	// /else
		// dprintf(2, "no var_value\n");
	return (size);
}

static int	manage_quoted_token(t_data *data, t_list **lst, char *line)
{
	int		i;
	int		j;
	int		size;
	char	*str;

	i = 0;
	// dprintf(2, "manage_quoted_token %s\n", line);
	while (line[i])
	{
		j = 0;
		while (line[i + j] != '"' && line[i + j] != '$')
			j++;
		str = ft_substr(line, i, j);
		i += j;
		if (!str)
			return (print_sys_error("manage_quoted_token ft_substr"));
		// dprintf(2, "\t found %s\n", str);
		if (!lst_add_or_join_back(lst, str))
			return (FALSE);
		if (line[i] == '"')
			break ;
		// dprintf(2, "\t found $\n");
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
static int	manage_string_token(t_data *data, t_list **lst, char *line, int *i)
{
	int		word_size;
	char 	*tmp;

	word_size = find_next_word(&(line[*i]));
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
		// dprintf(2, "found value %s\n", tmp);
		if (!lst_add_or_join_back(lst, tmp))
			return (FALSE);
	}
	*i += word_size;
	return (TRUE);
}

// Expand une ligne. Pour chaque caractere:
// 		si c'est un $, expand la variable d'environement
// 		sinon, stock la chaine
static int	expand_token(t_data *data, t_list **lst, char *line, char expand)
{
	int		size;
	int		i;

	i = 0;
	// dprintf(2, "Arg %s\n", line);
	while (line[i])
	{
		// dprintf(2, "testing from %s\n", &(line[i]));
		if (line[i] == '$')
		{
			i++;
			size = manage_env_var_token(data, lst, line + i, expand);
			if (size < 0)
				return (FALSE);
			i += size;
			continue ;
		}
		if (!manage_string_token(data, lst, line, &i))
			return (FALSE);
	}
	return (TRUE);
}

// Cree une liste chainee contenant chaque argv expanded
// Transforme cette liste en tableau pour remplacer l'ancien cmd->argv
static int	expand_cmd(t_data *data, t_cmd *cmd)
{
	t_list	*lst;
	char	**argv;
	int		i;

	i = 0;
	lst = NULL;
	while (cmd->argv && cmd->argv[i])
	{
		if (!create_lst_empty(&lst) || !expand_token(data, &lst, cmd->argv[i], TRUE))
		{
			ft_lstclear(&lst, free);
			return (FALSE);
		}
		i++;
	}
	argv = create_tab_from_lst(lst);
	if (!argv)
	{
		ft_lstclear(&lst, free);
		return (print_sys_error("create_tab_from_lst"));
	}
	if (cmd->argv)
		ft_tabclear(cmd->argv);
	cmd->argv = argv;
	// ft_putchar('\n');
	// ft_tabprint(cmd->argv);
	// ft_putchar('\n');
	return (TRUE);
}

static int	expand_file(t_data *data, char **name)
{
	t_list	*lst;

	lst = NULL;
	if (!create_lst_empty(&lst) || !expand_token(data, &lst, *name, FALSE))
	{
		ft_lstclear(&lst, free);
		return (FALSE);
	}
	free(*name);
	*name = lst->content;
	free(lst);
	return (TRUE);
}

int	expand_pipe(t_data *data, t_cmd *cmds)
{
	t_redirection	*tmp;

	while (cmds)
	{
		if (!expand_cmd(data, cmds))
			return (FALSE);
		tmp = cmds->redir;
		while (tmp)
		{
			if (!expand_file(data, &(tmp->name)))
				return (FALSE);
			tmp = tmp->next;
		}
		cmds = cmds->next;
	}
	return (TRUE);
}
