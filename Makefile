# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: picheval <picheval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/05 12:28:46 by picheval          #+#    #+#              #
#    Updated: 2026/01/24 14:49:04 by tbez--du         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 					= cc
CFLAGS				= -Wall -Wextra -Werror -g3
LIBS_FLAGS			= -lreadline

NAME				= minishell

SRCS_DIR			= ./srcs/
OBJS_DIR			= ./objs/
INC_DIR				= ./includes/
EXEC_DIR			= exec/
PARSE_DIR			= parse/
STRUCT_DIR			= structs/
BUILTIN_DIR			= builtins/
WILDCARDS_DIR		= wildcards/

SRCS_RAW			= main.c \
					  $(STRUCT_DIR)struct_data.c \
					  $(STRUCT_DIR)struct_env.c \
					  $(STRUCT_DIR)struct_operator.c \
					  $(STRUCT_DIR)struct_operator_utils.c \
					  $(STRUCT_DIR)struct_lexem.c \
					  $(STRUCT_DIR)struct_cmd.c \
					  $(STRUCT_DIR)struct_redirection.c \
					  $(STRUCT_DIR)struct_ast.c \
					  $(STRUCT_DIR)struct_list_utils.c \
					  $(PARSE_DIR)init_operators.c \
					  $(PARSE_DIR)manage_line.c \
					  $(PARSE_DIR)manage_lexems.c \
					  $(PARSE_DIR)ast.c \
					  $(PARSE_DIR)ast_utils.c \
					  $(EXEC_DIR)exec_cmd.c \
					  $(EXEC_DIR)exec_pipe.c \
					  $(EXEC_DIR)exec_ast.c \
					  $(EXEC_DIR)expand.c \
					  $(BUILTIN_DIR)exec_builtin.c \
 					  $(BUILTIN_DIR)pwd.c \
 					  $(BUILTIN_DIR)exit.c \
 					  $(BUILTIN_DIR)cd.c \
					  $(BUILTIN_DIR)echo.c \
					  $(BUILTIN_DIR)env.c \
					  $(BUILTIN_DIR)unset.c \
					  $(BUILTIN_DIR)export.c \
					  $(WILDCARDS_DIR)getfilename.c \
					  $(WILDCARDS_DIR)expand_wildcards.c \
					  signal.c \
					  loop.c \
					  print.c \
					  print_bash.c \
					  print_debug.c

OBJS_RAW			= $(SRCS_RAW:.c=.o)
SRCS				= $(addprefix $(SRCS_DIR), $(SRCS_RAW))
OBJS				= $(addprefix $(OBJS_DIR), $(OBJS_RAW))

LIBFT_DIR			= ./libft/
LIBFT_INC_DIR		= $(LIBFT_DIR)includes/
LIBFT_FLAGS			= -L$(LIBFT_DIR) -lft

C_NONE				= \033[0m
C_RED				= \033[31m
C_BLUE				= \033[36m

SYMBOL				= $(C_RED)==> $(C_NONE)


all: libft $(NAME)

re: fclean all

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(LIBS_FLAGS) $^ -o $@ $(LIBFT_FLAGS)
	@echo "$(SYMBOL)$(C_BLUE)$(NAME) compiled !$(C_NONE)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)$(STRUCT_DIR)
	@mkdir -p $(OBJS_DIR)$(PARSE_DIR)
	@mkdir -p $(OBJS_DIR)$(EXEC_DIR)
	@mkdir -p $(OBJS_DIR)$(BUILTIN_DIR)
	@mkdir -p $(OBJS_DIR)$(WILDCARDS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR) -I$(LIBFT_INC_DIR)

clean:
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS_DIR)
	@echo "$(SYMBOL)$(C_BLUE)$(NAME) clean done !$(C_NONE)"

fclean: clean
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(SYMBOL)$(C_BLUE)$(NAME) fclean done !$(C_NONE)"

libft:
	@make --no-print-directory -C $(LIBFT_DIR)

valgrind: re
	@valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes \
		--track-fds=yes \
		--trace-children-skip="*ls","*cat","*grep","*clear" \
		--suppressions=valgrind_filter.supp ./$(NAME)

.PHONY: all re clean fclean libft valgrind
