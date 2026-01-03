# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: picheval <picheval@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/05 12:28:46 by picheval          #+#    #+#              #
#    Updated: 2026/01/03 15:37:31 by picheval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			= cc
CFLAGS		= -Wall -Wextra -Werror

NAME		= libft.a
SRCS_DIR	= ./srcs/
INC_DIR		= ./includes/
OBJS_DIR	= ./objs/
SRCS_RAW	= ft_isalpha.c \
			  ft_isdigit.c \
			  ft_isalnum.c \
			  ft_isascii.c \
			  ft_isprint.c \
			  ft_isspace.c \
			  ft_strlen.c \
			  ft_memset.c \
			  ft_bzero.c \
			  ft_memcpy.c \
			  ft_memmove.c \
			  ft_strlcpy.c \
			  ft_strlcat.c \
			  ft_toupper.c \
			  ft_tolower.c \
			  ft_strchr.c \
			  ft_strrchr.c \
			  ft_strcmp.c \
			  ft_strncmp.c \
			  ft_nbrcmp.c \
			  ft_memchr.c \
			  ft_memcmp.c \
			  ft_strnstr.c \
			  ft_strnew.c \
			  ft_atoi.c \
			  ft_calloc.c \
			  ft_strdup.c \
			  ft_substr.c \
			  ft_strjoin.c \
			  ft_strtrim.c \
			  ft_split.c \
			  ft_itoa.c \
			  ft_strmapi.c \
			  ft_striteri.c \
			  ft_putchar_fd.c \
			  ft_putstr_fd.c \
			  ft_putendl_fd.c \
			  ft_putnbr_fd.c \
			  ft_putchar.c \
			  ft_putstr.c \
			  ft_putendl.c \
			  ft_putnbr.c \
			  ft_putnbr_base.c \
			  ft_putnbr_ull_base.c \
			  ft_tabclear.c \
			  ft_tabjoin.c \
			  ft_tablen.c \
			  ft_tabdup.c \
			  ft_tabprint.c \
			  ft_abs.c \
			  ft_max.c \
			  ft_min.c \
			  ft_lstnew.c \
			  ft_lstadd_front.c \
			  ft_lstsize.c \
			  ft_lstlast.c \
			  ft_lstadd_back.c \
			  ft_lstdelone.c \
			  ft_lstclear.c \
			  ft_lstiter.c \
			  ft_lstmap.c \
			  ft_printf.c \
			  ft_printf_param.c \
			  ft_printf_conversions.c \
			  ft_printf_conversions_hex.c \
			  ft_printf_tools.c \
			  ft_printf_env.c \
			  get_next_line.c \
			  get_next_line_utils.c
OBJS_RAW	= $(SRCS_RAW:.c=.o)
SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_RAW))
OBJS		= $(addprefix $(OBJS_DIR), $(OBJS_RAW))

C_NONE		= \033[0m
C_RED		= \033[31m
C_BLUE		= \033[36m

SYMBOL		= $(C_RED)==> $(C_NONE)


all: $(NAME)

re: fclean all

$(NAME): $(OBJS)
	@echo "$(SYMBOL)$(C_BLUE)$(NAME) compiled !$(C_NONE)"
	@ar rc $@ $^

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

clean:
	@echo "$(SYMBOL)$(C_BLUE)$(NAME) clean done !$(C_NONE)"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "$(SYMBOL)$(C_BLUE)$(NAME) fclean done !$(C_NONE)"
	@rm -f $(NAME)
