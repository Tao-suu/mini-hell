/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 14:28:07 by picheval          #+#    #+#             */
/*   Updated: 2026/01/03 16:08:06 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>	// readline
#include <readline/history.h>	// readline
# include "libft.h"

typedef struct s_operator	t_operator;
typedef struct s_lexem		t_lexem;
typedef struct s_ast		t_ast;
typedef struct s_data		t_data;

struct s_operator {
	int					id;
	char				*name;
	char				*value;
	int					lvl_up;
	char				*tmp_before;
	char				*tmp_after;
	struct s_operator	**before;
	struct s_operator	**after;
	struct s_operator	*next;
};

struct s_lexem {
	char			*value;
	t_operator		*type;
	int				lvl; // usefull ?
	t_lexem			*prev;
	t_lexem			*next;
};

struct s_ast {
	// global
		// type (&& || pipeline)

	// pipeline
		// cmd list
		// fds
};

struct s_data {
	char		**env;
	char		**set;
	t_operator	**operators;

	char		*line;
	t_lexem		*head;
	t_ast		*ast;
};

// struct_data.c
void	free_data(t_data *data, char full);
int		init_data(t_data *data);

// signal.c
void	init_signal(void);

// loop.c
void	main_loop(t_data *data);

// print.c
int		print_error(char *msg);
int		print_sys_error(char *msg);

#endif