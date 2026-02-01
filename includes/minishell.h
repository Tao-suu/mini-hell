/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 14:28:07 by picheval          #+#    #+#             */
/*   Updated: 2026/02/01 01:43:20 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include "libft.h"

# define GRAMMAR_NB_FIELDS		6
# define GRAMMAR_FIELD_SEP		','
# define GRAMMAR_DEP_SEP		'|'
# define GRAMMAR_NULL			"NULL"

# define OP_START				"START"
# define OP_END					"END"

# define TMP_FILE_NAME			"/tmp/heredoc"

# define TAB_EXTRA_SPACE		2

# define NODE_TYPE_CMD			0
# define NODE_TYPE_AND			1
# define NODE_TYPE_OR			2

# define CLR_RED				"\x1b[1;38;2;255;0;0;49m"
# define CLR_GREEN				"\x1b[32m"
# define CLR_YELLOW				"\x1b[1;38;2;255;255;0;49m"
# define CLR_MAG				"\x1B[35m"
# define CLR_CYAN				"\x1B[36m"
# define CLR_RESET				"\x1b[0m"

# define LGBT					1
# define NB_PROMPT_COLOR		6
# define NB_PROMPT_MSG			1

extern int						g_signal;

typedef enum e_env_state		t_env_state;
typedef struct s_operator		t_operator;
typedef struct s_lexem			t_lexem;
typedef struct s_ast			t_ast;
typedef struct s_heredoc		t_heredoc;
typedef struct s_redirection	t_redirection;
typedef struct s_cmd			t_cmd;
typedef struct s_env			t_env;
typedef struct s_data			t_data;
typedef struct dirent			t_dirent;

enum e_env_state {
	STATE_ENV = 0,
	STATE_SET = 1,
	STATE_HIDDEN = 2,
	STATE_DEAD = 3
};

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
	char	node_type;
	t_cmd	*cmds;
	t_ast	*right;
	t_ast	*left;
};

struct s_heredoc {
	char		*delimiter;
	char		*filename;
	t_heredoc	*next;
};

struct s_redirection {
	char			*name;
	int				valid_wild;
	t_operator		*operator;
	t_heredoc		*heredoc;
	t_redirection	*next;
};

struct s_cmd {
	char			*path;
	int				argc;
	char			**argv;
	char			**argv_expanded;
	char			*to_expand;
	int				pid;
	t_ast			*ast;
	t_cmd			*next;
	t_redirection	*redir;
};

struct s_env {
	char		*key;
	char		*value;
	t_env_state	state;
	t_env		*next;
};

struct s_data {
	t_env		*env;
	t_operator	**operators;
	int			nb_execution;
	char		*line;
	t_lexem		*head;
	t_ast		*ast;
	t_heredoc	*heredocs;
	char		*color[NB_PROMPT_COLOR];
	char		*prompts[NB_PROMPT_MSG];
	int			prompt_n;
};

/*****************/
/*    STRUCTS    */
/*****************/

// struct_data.c
void			free_data(t_data *data, char full, char even_files);
int				init_data(t_data *data);

// struct_env.c
char			**get_env_tab_from_list(t_env *env);
int				create_or_update_env(t_env **env, char *key, char *value,
					t_env_state state);
int				create_env_from_string(t_env **env, char *string,
					t_env_state state);

					// struct_env_utils.c
void			free_env(t_env *elem);
void			free_env_list(t_env *list);
int				create_and_add_env_elem(t_env **env, char *key, char *value,
					t_env_state state);
t_env			*find_env_var(t_env *env, char *key);

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

// struct_list_utils.c
char			**create_tab_from_lst(t_list *lst);
int				create_lst_empty(t_list **lst);
int				lst_add_or_join_back(t_list **lst, char *value);

// struct_heredoc.c
void			free_heredoc_list(t_heredoc *list, char even_files);
int				manage_heredoc_elem(t_heredoc **lst, t_redirection *redir,
					char *delimiter);

/*****************/
/*    PARSING    */
/*****************/

// init_operators.c
int				create_operators_array(t_operator ***tab);

// operators_list.c
int				create_operators_list(t_operator **lst);

// manage_line.c
int				manage_line(t_data *data);

// manage_lexems.c
int				manage_lexems(t_data *data);

// ast.c
int				create_ast(t_data *data);

// ast_utlis.c
t_lexem			*find_last_operator_in_level(t_lexem *start, t_lexem *end,
					int level);
void			skip_parenthesis(t_lexem **start, t_lexem *end);
size_t			compute_nb_params(t_lexem *start, t_lexem *end);

/*******************/
/*    EXECUTION    */
/*******************/

// exec_*.c
int				exec_pipe(t_data *data, t_cmd *cmds);
int				exec_ast(t_data *data, t_ast *ast);
void			exec_cmd(t_data *data, t_cmd *cmd);
int				manage_redirections(t_redirection *red);
int				exec_heredocs(t_data *data);
//exit_code.c
int				set_exit_code(t_env **env, int code);
int				get_exit_code(t_data *data);
int				compute_exit_code(int status);
int				wait_cmd_pid(t_cmd *cmd, t_env **env);
//expand.c
int				expand_pipe(t_data *data, t_cmd *cmds);
//expand_utils.c
int				manage_env_var_token(t_data *data, t_list **lst, char *line,
					char expand);
int				manage_string_token(t_data *data, t_list **lst, char *line,
					int *i);
//expand_tools.c
int				count_var_key_size(char *arg);
int				expand_find_next_word(char *line);
int				expand_env_var(t_list **lst, char *line);
int				expand_token(t_data *data, t_list **lst, char *line,
					char expand);
//cmd_path_utils.c
char			*get_cmd_path(t_env *env, char **argv, int *exit_code);

/******************/
/*    BUILTINS    */
/******************/

// *.c
int				exec_builtin(t_data *data, t_cmd *cmd, int flag);
int				is_builtin(t_cmd *cmd);
int				builtin_pwd(void);
int				builtin_exit(t_data *data, t_cmd *cmd, int flag);
int				builtin_cd(t_env **env, t_cmd *cmd);
unsigned char	builtin_echo(t_cmd *cmd);
int				builtin_env(t_env *env);
int				builtin_unset(t_env *env, t_cmd *cmd);
int				builtin_export(t_env **env, t_cmd *cmd);

/****************/
/*    GLOBAL    */
/****************/

// signal.c
void			heredoc_signal(void);
void			dfl_signal(void);
void			ign_signal(void);
void			init_signal(void);

// signal_handler.c
void			handler(int signal);
void			heredoc_handler(int signal);

// loop.c
void			main_loop(t_data *data);

// prompt.c
void			free_prompt(t_data *data);
char			*get_prompt(t_data *data);
int				init_prompt(t_data *data);

// tools.c
int				merge_with_sep(char **ret, char *str1, char *str2, char *sep);
char			*create_file_name(char *base_file_name, size_t number);

// print.c
int				print_error(char *msg);
int				print_sys_error(char *msg);

// print_bash.c
void			print_bash_name(void);
int				print_bash_ambiguous_redirection(char *name);
void			print_bash_heredoc_warning(int nb_execution, char *delimiter);
int				print_bash_cmd_error(char *cmd, char *filename, char *msg);
int				print_bash_error(char *msg);

// print_syntax.c
int				print_syntax_error(char *token);
int				print_matching_error(char c);

// print_builtin.c
int				print_builtin_pwd_error(char *msg, char *syscall,
					char *syscall_msg);
int				print_builtin_echo_error(char *syscall_msg, char *msg);
int				print_builtin_exit_error(char *arg, char *msg);
int				print_builtin_cd_error(char *filename, char *msg);
int				print_builtin_export_error(char *arg);

// print_debug.c
void			print_tabs(int nb_tabs);
void			print_cmd(t_cmd *cmd, int lvl);
void			print_ast(t_ast *ast, int lvl);
void			print_operators(t_operator **tab);
void			print_debug_env(t_env *env);

// wildcards
char			**get_files_name(void);
int				expand_wildcards_cmd(t_cmd *cmd);
int				check_pattern(char *file, char *pattern);
int				expand_wildcards_redir(t_cmd *cmd, char **files);
void			sort_files(char **files);
void			its_just_void(void *content);
int				check_pattern(char *file, char *pattern);

#endif
