/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 21:22:57 by picheval          #+#    #+#             */
/*   Updated: 2026/02/02 10:42:52 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	get_random_value(int min, int max)
// {
// 	char	buff;
// 	int		fd;

// 	fd = open("/dev/urandom", O_RDONLY);
// 	if (fd < 0)
// 		return (0);
// 	if (read(fd, &buff, 1) < 0)
// 		return (1);
// 	return (((int)buff + 128 + min) % max);
// }

void	free_prompt(t_data *data)
{
	int	i;

	i = -1;
	while (++i < NB_PROMPT_COLOR)
	{
		if (data->color[i])
			free(data->color[i]);
	}
	i = -1;
	while (++i < NB_PROMPT_MSG)
	{
		if (data->prompts[i])
			free(data->prompts[i]);
	}
}

char	*get_prompt(t_data *data)
{
	return (data->prompts[0]);
}

static int	init_prompt_color(t_data *data)
{
	if (LGBT)
	{
		data->color[0] = ft_strdup("\x1b[1;38;2;228;3;3;49m");
		data->color[1] = ft_strdup("\x1b[1;38;2;255;140;0;49m");
		data->color[2] = ft_strdup("\x1b[1;38;2;255;237;0;49m");
		data->color[3] = ft_strdup("\x1b[1;38;2;0;128;38;49m");
		data->color[4] = ft_strdup("\x1b[1;38;2;0;77;255;49m");
		data->color[5] = ft_strdup("\x1b[1;38;2;117;7;135;49m");
	}
	else
	{
		data->color[0] = ft_strdup(CLR_RESET);
		data->color[1] = ft_strdup(CLR_RESET);
		data->color[2] = ft_strdup(CLR_RESET);
		data->color[3] = ft_strdup(CLR_RESET);
		data->color[4] = ft_strdup(CLR_RESET);
		data->color[5] = ft_strdup(CLR_RESET);
	}
	if (!data->color[0] || !data->color[1] || !data->color[2]
		|| !data->color[3] || !data->color[4] || !data->color[5])
		return (FALSE);
	return (TRUE);
}

static int	init_prompt_msg(t_data *data)
{
	t_env	*env_user;
	char	*user;

	env_user = find_env_var(data->env, "USER");
	if (!env_user)
		user = ft_strdup("PTSD > /dev/null");
	else
		user = ft_strdup(env_user->value);
	if (!user)
		return (FALSE);
	// prompts[0] = ft_strjoin(ft_strjoin(CLR_YELLOW, data->user),
		// CLR_RED" $> "CLR_RESET);
	// prompts[1] = ft_strjoin(ft_strjoin(CLR_RED, data->user),
		// CLR_YELLOW" $> "CLR_RESET);
	// prompts[2] = ft_strdup(CLR_YELLOW" ~o~"CLR_RED" $> "CLR_RESET);
	// prompts[3] = ft_strdup(CLR_RED" ~o~"CLR_YELLOW" $> "CLR_RESET);
	// prompts[0] = ft_strjoin(data->color[get_random_value(0, 6)],
	// 	ft_strjoin(data->user, 
	// 	ft_strjoin(data->color[get_random_value(0, 6)], 
	// 	ft_strjoin(" $>", CLR_RESET))));
	data->prompts[0] = ft_strjoin(user, " <3 ");
	free(user);
	if (!data->prompts[0])
		return (FALSE);
	return (TRUE);
}

int	init_prompt(t_data *data)
{
	data->prompt_n = 0;
	if (!init_prompt_msg(data) || !init_prompt_color(data))
		return (FALSE);
	return (TRUE);
}
