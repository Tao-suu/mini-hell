# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: picheval <picheval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/05 12:28:46 by picheval          #+#    #+#              #
#    Updated: 2026/01/07 04:53:50 by tbez--du         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 					= cc
CFLAGS				= -Wall -Wextra -Werror -g3
LIBS_FLAGS			= -lreadline

NAME				= minishell
SRCS_RAW			= main.c \
					  struct_data.c \
					  struct_operator.c \
					  struct_lexem.c \
					  struct_cmd.c \
					  struct_redirection.c \
					  struct_ast.c \
					  init_operators.c \
					  signal.c \
					  loop.c \
					  manage_line.c \
					  manage_lexems.c \
					  ast.c \
					  print.c \
					  print_debug.c \
					  exec/exec_cmd.c \
					  exec/exec_pipe.c \
					  exec/exec_ast.c \

SRCS_DIR			= ./srcs/
OBJS_DIR			= ./objs/
INC_DIR				= ./includes/

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


all: libft_cc $(NAME)

re: fclean all

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(LIBS_FLAGS) $^ -o $@ $(LIBFT_FLAGS)
	@echo "$(SYMBOL)$(C_BLUE)$(NAME) compiled !$(C_NONE)"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)exec
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR) -I$(LIBFT_INC_DIR)

clean:
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS_DIR)
	@echo "$(SYMBOL)$(C_BLUE)$(NAME) clean done !$(C_NONE)"

fclean: clean
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(SYMBOL)$(C_BLUE)$(NAME) fclean done !$(C_NONE)"

libft_cc:
	@make --no-print-directory -C $(LIBFT_DIR)
