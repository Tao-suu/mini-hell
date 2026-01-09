/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:02:19 by picheval          #+#    #+#             */
/*   Updated: 2026/01/09 02:49:05 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char **tab, char *var_name)
{
	size_t	var_name_len;
	int		i;

	var_name_len = ft_strlen(var_name);
	i = -1;
	while (tab[++i])
		if (!ft_strncmp(tab[i], var_name, var_name_len)
			&& tab[i][var_name_len] == '=')
			return (tab[i] + var_name_len + 1);
	return (NULL);
}

// !! var is not strduped, so always send a malloced values to this function
// tab_size : tab malloc'ed size / tab_len : tab actual content length
static int	add_var(char ***tab, size_t *tab_size, char *var)
{
	size_t	tab_len;
	char	**tmp_tab;

	tab_len = ft_tablen(*tab);
	if (tab_len >= *tab_size)
	{
		tmp_tab = (char **)ft_calloc(sizeof(char *),
				*tab_size + TAB_EXTRA_SPACE + 1);
		if (!tmp_tab)
			return (print_sys_error("ft_calloc"));
		tab_len = -1;
		while ((*tab)[++tab_len])
			tmp_tab[tab_len] = (*tab)[tab_len];
		free(*tab);
		*tab = tmp_tab;
		*tab_size += TAB_EXTRA_SPACE;
	}
	(*tab)[tab_len] = var;
	return (TRUE);
}

int	unset_key(char **tab, char *key)
{
	int		i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = -1;
	while (tab[++i])
		if (!ft_strncmp(tab[i], key, key_len)
			&& tab[i][key_len] == '=')
			break ;
	if (!tab[i])
		return (TRUE);
	free(tab[i]);
	while (tab[i])
	{
		tab[i] = tab[i + 1];
		i++;
	}
	return (TRUE);
}

// Doesn't free var
// Returns status
int	set_var(char ***tab, size_t *tab_size, char *var)
{
	char	*equal_index;
	char	*var_dup;
	size_t	var_name_len;
	int		i;

	equal_index = ft_strchr(var, '=');
	if (!equal_index)
		return (print_error("set_var: no '=' in var"));
	var_name_len = equal_index - var;
	i = -1;
	while ((*tab)[++i])
		if (!ft_strncmp((*tab)[i], var, var_name_len))
			break ;
	var_dup = ft_strdup(var);
	if (!var_dup)
		return (print_sys_error("ft_strdup malloc"));
	if (!(*tab)[i])
		return (add_var(tab, tab_size, var_dup));
	free((*tab)[i]);
	(*tab)[i] = var_dup;
	return (TRUE);
}

// Doesn't free key or value
int	set_key_value(char ***tab, size_t *tab_size, char *key, char *value)
{
	char	*var;
	char	*tmp;
	int		ret;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (print_sys_error("ft_strjoin malloc"));
	var = ft_strjoin(tmp, value);
	free(tmp);
	if (!var)
		return (print_sys_error("ft_strjoin malloc"));
	ret = set_var(tab, tab_size, var);
	free(var);
	return (ret);
}
