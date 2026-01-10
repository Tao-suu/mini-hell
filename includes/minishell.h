/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 14:28:07 by picheval          #+#    #+#             */
/*   Updated: 2026/01/10 01:09:14 by tbez--du         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "libft.h"
# include <sys/wait.h>
# include <unistd.h>

# define GRAMMAR_FILE		"grammar.txt"
# define GRAMMAR_NB_FIELDS	6
# define GRAMMAR_FIELD_SEP	';'
# define GRAMMAR_DEP_SEP	'|'
# define GRAMMAR_NULL		"NULL"

# define OP_START			"START"
# define OP_END				"END"

# define TAB_EXTRA_SPACE	2

# define CLR_RED			"\x1b[31m"
# define CLR_GREEN			"\x1b[32m"
# define CLR_MAG			"\x1B[35m"
# define CLR_CYAN			"\x1B[36m"
# define CLR_RESET			"\x1b[0m"

typedef struct s_operator		t_operator;
typedef struct s_lexem			t_lexem;
typedef struct s_ast			t_ast;
typedef struct s_redirection	t_redirection;
typedef struct s_cmd			t_cmd;
typedef struct s_data			t_data;

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
	int				lvl;
	t_lexem			*prev;
	t_lexem			*next;
};

struct s_ast {
	char	*node_type;
	t_cmd	*cmds;
	t_ast	*right;
	t_ast	*left;
};

struct s_redirection {
	char			*name;
	t_operator		*operator;
	t_redirection	*next;
};

struct s_cmd {
	char			*path;
	char			**argv;
	int				pid;
	t_ast			*ast;
	t_cmd			*next;
	t_redirection	*in;
	t_redirection	*out;
};

struct s_data {
	char		**env;
	char		**set;
	size_t		env_size; // total size of env, not just it's content length
	size_t		set_size; // total size of env, not just it's content length
	t_operator	**operators;
	char		*line;
	t_lexem		*head;
	t_ast		*ast;
};

// struct_data.c
void			free_data(t_data *data, char full);
int				init_data(t_data *data);

// struct_operator.c
void			free_operator_list(t_operator *list);
void			free_operator_tab(t_operator **tab);
t_operator		*create_operator_elem(char **fields);

// struct_operator_tools.c
void			add_operator_elem(t_operator **list, t_operator *elem);
t_operator		**create_operator_tab_from_list(t_operator *list);
t_operator		*find_operator_by_value(t_operator **tab, char *value);
t_operator		*find_operator_by_name(t_operator **tab, char *name);

// struct_lexem.c
void			free_lexem_elem(t_lexem *elem);
void			free_lexem_list(t_lexem *list);
void			add_lexem_elem(t_lexem **list, t_lexem *elem);
t_lexem			*create_lexem_elem(void);

// struct_cmd.c
void			free_cmd(t_cmd *elem);
void			free_cmds_list(t_cmd *list);
void			add_cmd_elem_in_list(t_cmd **list, t_cmd *elem);
t_cmd			*create_cmd_elem(size_t nb_argv);

// struct_redirection.c
void			free_redirection(t_redirection *elem);
void			free_redirection_list(t_redirection *list);
void			add_redirection_in_list(t_redirection **list,
					t_redirection *elem);
t_redirection	*create_redirection_elem(t_operator *operator, char *name);

// struct_ast.c
t_ast			*create_ast_elem(void);
void			free_ast_tree(t_ast *ast);

// init_operators.c
int				create_operators_array(t_operator ***tab);

// manage_line.c
int				manage_line(t_data *data);

// manage_lexems.c
int				manage_lexems(t_data *data);

// signal.c
void			init_signal(void);
void			ign_signal(void);
void			dfl_signal(void);
// loop.c
void			main_loop(t_data *data);

// ast.c
int				create_ast(t_data *data);

// ast_utlis.c
t_lexem			*find_first_operator_in_level(t_lexem *start, t_lexem *end,
					int level);
void			skip_parenthesis(t_lexem **start, t_lexem *end);
size_t			compute_nb_params(t_lexem *start, t_lexem *end);

// print.c
int				print_error(char *msg);
int				print_sys_error(char *msg);

// print_bash.c
int				print_syntax_error(char *token);
int				print_matching_error(void);
int				print_bash_error(char *msg);

// print_debug.c
void			print_tabs(int nb_tabs);
void			print_cmd(t_cmd *cmd, int lvl);
void			print_ast(t_ast *ast, int lvl);
void			print_operators(t_operator **tab);

// exec/*.c
int				exec_pipe(t_data *data, t_cmd *cmds);
int				exec_ast(t_data *data, t_ast *ast);
int				exec_cmd(t_data *data, t_cmd *cmd, char **path);
int				redir_out(t_redirection *red);
int				redir_in(t_redirection *red);

// env_set_utils.c
char			*get_var(char **tab, char *var_name);
int				unset_key(char **tab, char *key);
int				set_var(char ***tab, size_t *tab_size, char *var);
int				set_key_value(char ***tab, size_t *tab_size, char *key,
					char *value);

// env_utils.c
char			*get_env_var(t_data *data, char *var_name);
int				unset_env_key(t_data *data, char *key);
int				set_env_var(t_data *data, char *var);
int				set_env_key_value(t_data *data, char *key, char *value);

// set_utils.c
char			*get_set_var(t_data *data, char *var_name);
int				unset_set_key(t_data *data, char *key);
int				set_set_var(t_data *data, char *var);
int				set_set_key_value(t_data *data, char *key, char *value);

// builtin
int				exec_builtin(t_data *data, t_cmd *cmd, int flag);
int				is_builtin(t_cmd *cmd);
int				pwd(t_data *data);

#endif
