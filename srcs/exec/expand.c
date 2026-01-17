/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbez--du <tbez--du@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:36:38 by tbez--du          #+#    #+#             */
/*   Updated: 2026/01/17 13:58:29 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_env_char(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

int	get_token_len(t_data *data, char **token)
{
	int	start;
	int	count;
	int	end;

	start = 0;
	count = 0;
	while ((*token)[start])
	{
		if ((*token)[start] == '$')
		{
			start++;
			if (ft_isalpha((*token)[start]) || (*token)[start] == '_')
			{
				end = start;
				while (is_env_char((*token)[end]))
					end++;
				char	*env_key;
				env_key = ft_substr(*token, start, end - start);
					if (find_env_var(data->env, env_key))
					count += ft_strlen(find_env_var(data->env, env_key)->value);
				start = end;
			}
			else 
				count++;
		}
		else
		{
			count++;
			start++;
		}
	}
	return (count);
}

int	expand_token(t_data *data, char **token)
{
	int		len;
	int		start;
	int		end;
	char	*new;

	len = get_token_len(data, token);
	new = ft_calloc(len + 1, 1);
	if (!new)
		return (0);
	start = 0;
	while ((size_t)start < ft_strlen(*token))
	{
		if ((*token)[start] == '$')
		{
			start++;
			if (ft_isalpha((*token)[start]) || (*token)[start] == '_')
			{
				end = start;
				while (is_env_char((*token)[end]))
					end++;
				char	*env_key;
				env_key = ft_substr(*token, start, end - start);
					if (find_env_var(data->env, env_key))
					ft_strlcat(new, find_env_var(data->env, env_key)->value, len + 1);
				start = end;
			}
			else
			{
				ft_strlcat(new, *token + start, ft_strlen(new) + 2);
				start++;
			}
		}
		else
		{
			ft_strlcat(new, *token + start, ft_strlen(new) + 2);
			start++;
		}
	}
	free(*token);
	*token = new;
	return (1);
}

int	expand_cmd(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
	{
		if (!expand_token(data, &cmd->argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	expand_pipe(t_data *data, t_cmd *cmds)
{
	while (cmds)
	{
		if (!expand_cmd(data, cmds))
			return (0);
		cmds = cmds->next;
	}
	return (1);
}
