/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 14:28:07 by picheval          #+#    #+#             */
/*   Updated: 2026/01/03 19:00:25 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>	// readline
# include <readline/history.h>	// readline
# include <fcntl.h>				// open
# include "libft.h"

# define GRAMMAR_FILE		"grammar.txt"
# define GRAMMAR_NB_FIELDS	6
# define GRAMMAR_FIELD_SEP	';'
# define GRAMMAR_DEP_SEP	'|'
# define GRAMMAR_NULL		"NULL"

# define OP_START			"START"
# define OP_END				"END"

# define CLR_RED			"\x1b[31m"
# define CLR_GREEN			"\x1b[32m"
# define CLR_RESET			"\x1b[0m"

typedef struct s_operator	t_operator;
typedef struct s_lexem		t_lexem;
typedef struct s_ast		t_ast;
typedef struct s_data		t_data;
typedef struct s_cmd		t_cmd;

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
	t_operator	*operator;
	t_cmd	*cmds;
	int		fd_in;
	int		fd_out;
	char	flag;
	t_ast	*right;
	t_ast	*left;
};

struct s_cmd {
	char	*path;
	char 	**argv;
	t_cmd	*next;
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

// struct_operator.c
t_operator	*find_operator_by_value(t_operator **tab, char *value);
t_operator	*find_operator_by_name(t_operator **tab, char *name);
void		free_operator_list(t_operator *list);
void		free_operator_tab(t_operator **tab);
void		add_operator_elem(t_operator **list, t_operator *elem);
t_operator	**create_operator_tab_from_list(t_operator *list);
t_operator	*create_operator_elem(char **fields);

// struct_lexem.c
void		free_lexem_elem(t_lexem *elem);
void		free_lexem_list(t_lexem *list);
void		add_lexem_elem(t_lexem **list, t_lexem *elem);
t_lexem		*create_lexem_elem(void);

// init_operators.c
int			create_operators_array(t_operator ***tab);

// manage_line.c
int			manage_line(t_data *data);

// manage_lexems.c
int			manage_lexems(t_data *data);

// signal.c
void	init_signal(void);

// loop.c
void	main_loop(t_data *data);

// ast.c
int		create_ast(t_data *data);

// print.c
int		print_error(char *msg);
int		print_sys_error(char *msg);
int			print_syntax_error(char *token);
int			print_matching_error(void);
int			print_bash_error(char *msg);

#endif