/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: picheval <picheval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:48:44 by picheval          #+#    #+#             */
/*   Updated: 2026/01/25 18:20:34 by picheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define TRUE					1
# define FALSE					0
# define CONVERSIONS			"cspdiuxX%\0"
# define NB_CONVERSION			9
# define LOWERCASE				0
# define UPPERCASE				1
# define BASE16_UPPERCASE		"0123456789ABCDEF\0"
# define BASE16_LOWERCASE		"0123456789abcdef\0"
# define BASE10					"0123456789\0"
# define HEX_UPPERCASE_PREFIX	"0X\0"
# define HEX_LOWERCASE_PREFIX	"0x\0"
# define BUFFER_SIZE			32

# include <sys/types.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_point {
	int	x;
	int	y;
}		t_point;

typedef struct s_list {
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_printf_param {
	char	conversion;
	char	minus;
	char	zero;
	char	hashtag;
	char	space;
	char	plus;
	int		dot;
	int		min_width;
}			t_printf_param;

typedef struct s_printf_env {
	const char		*str;
	size_t			str_i;
	t_printf_param	param;
	va_list			ap;
	void			(*conv_function[NB_CONVERSION])(struct s_printf_env *);
	int				ret;
}					t_printf_env;

typedef struct s_file {
	int				fd;
	char			*rest;
	size_t			rest_size;
	struct s_file	*next;
}					t_file;

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
size_t			ft_strlen(const char *s);
void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t siz);
size_t			ft_strlcat(char *dst, const char *src, size_t siz);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_nbrcmp(const char *nbr1, const char *nbr2);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t n);
char			*ft_strnew(size_t size);
int				ft_atoi(const char *nptr);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strdup(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
ssize_t			ft_putchar_fd(char c, int fd);
ssize_t			ft_putstr_fd(char *s, int fd);
ssize_t			ft_putendl_fd(char *s, int fd);
ssize_t			ft_putnbr_fd(int n, int fd);
ssize_t			ft_putchar(char c);
ssize_t			ft_putstr(char *s);
ssize_t			ft_putendl(char *s);
ssize_t			ft_putnbr(int n);
ssize_t			ft_putnbr_base(int value, char *base, char dry);
ssize_t			ft_putnbr_ull_base(unsigned long long value, char *base,
					char dry);
void			ft_tabclear(char **tab);
char			*ft_tabjoin(char **tab, char *sep);
size_t			ft_tablen(char **tab);
char			**ft_tabdup(char **tab, size_t extra_space);
void			ft_tabprint(char **tab);
int				ft_abs(int nb);
int				ft_max(int nb1, int nb2);
int				ft_min(int nb1, int nb2);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

int				ft_printf(const char *str, ...);
void			ft_printf_parse_param(t_printf_env *e);
void			print_character(t_printf_env *e);
void			print_string(t_printf_env *e);
void			print_decimal(t_printf_env *e);
void			print_unsigned_decimal(t_printf_env *e);
void			print_percent(t_printf_env *e);
void			print_pointer(t_printf_env *e);
void			print_hex_lowercase(t_printf_env *e);
void			print_hex_uppercase(t_printf_env *e);
int				add_number_prefix(t_printf_param p, ssize_t size, char sign);
int				add_number_suffix(t_printf_param p, ssize_t size);
int				add_padding(t_printf_param p, ssize_t size, char before);
void			free_printf_env(t_printf_env *e);
void			init_printf_env(t_printf_env *e, const char *str);

char			*get_next_line(int c, int purge);
int				remove_file(t_file **files, t_file *file);
t_file			*find_or_create_file(t_file **files, int fd);
char			*ft_submem(char const *s, size_t s_size, unsigned int start,
					size_t len);
int				ft_realloc(t_file *file, int size_up);

#endif
