/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 16:33:26 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 11:02:08 by sbelondr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef LIBFT_H
#	define LIBFT_H

#define BUF_S 1024
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "ft_printf.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_dlist
{
	void			*data;
	size_t			data_size;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}					t_dlist;

typedef struct		s_lst
{
	char			*key;
	char			*value;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_merge
{
	int				i;
	int				j;
	int				k;
}					t_merge;

void				ft_strremove_char(char **src, int i);
char				*ft_strsubfree(char *s, unsigned int start, size_t len);
int					ft_strnchr(char *line, char c);
char				*ft_strjoinfree(char *s1, char *s2, int tofree);
int					ft_strendswith(char *string, char *suffix);
int					ft_strbeginswith(const char *string, char *prefix);
void				ft_putnbrln(int n);
void				ft_print_word_table(char **words);
void				ft_mergesort(int array[], int min, int max);
t_list				*ft_lstflip(t_list *head);
void				ft_lstextend(t_list *list, t_list *neew);
t_list				*ft_lst_element_at(t_list *list, unsigned int index);
void				ft_bzero(void *s, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *s1);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *str);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
		size_t len);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memalloc(size_t size);
char				*ft_strnew(size_t size);
void				ft_memdel(void **ap);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				**ft_split_whitespaces(char const *str);
char				*ft_itoa(int n);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *node);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_lstsize(t_lst **head);
int					ft_isspace(char c);
char				*ft_strrev(char *str);
void				ft_swap(int *a, int *b);
int					*ft_sort_integer_table(int *table, int size);
void				ft_lsttail(t_list **alst, t_list *node);
void				ft_fill_str(char *dst, char *src1, char *src2);
char				**split_once(char *str, char c);
t_dlist				*ft_dlstnew(void *data, size_t data_size);
void				ft_dlstinsfront(t_dlist **head, t_dlist **node);
void				ft_dlstinsback(t_dlist **tail, t_dlist **node);
void				ft_dlstinsafter(t_dlist **next_node, t_dlist **node);
void				ft_dlstinsbefore(t_dlist **prev_node, t_dlist **node);
t_dlist				*ft_dlstdelfirst(t_dlist **head);
t_dlist				*ft_dlstdellast(t_dlist **tail);
t_dlist				*ft_dlstdelone(t_dlist **head, void *data);
void				ft_dlstprinthead(t_dlist **head);
void				ft_dlstprinttail(t_dlist **tail);
int					ft_dlstiter(t_dlist **head);
int					ft_madeby(void);
int					ft_debug(void);
int					get_next_line(const int fd, char **line);
int					get_end_line(char *file);

void				ft_arraydel(char ***line);
void				ft_arraydelline(char ***src, int line);
void				ft_arraydisplay(char **src);
char				**ft_arraydup(char **line);
char				**ft_arrayjoin(char **src, char *str);
int					ft_arraylen(char **src);
char				**ft_arraysub(char **src, int start, int len);
int					ft_chr_index(char *s, char c);
int					ft_strchr_exist(char *s, char c);

int					ft_numlen(int n);
void				ft_pow_array_fix(int i, char (*nb)[BUF_S]);
void				ft_reverse_tablo(char (*lst)[BUF_S]);
void				ft_strsub_tab_fix(char (*lst)[BUF_S], char src[BUF_S],
		int start, int len);
void				ft_deplace(char (*lst)[BUF_S]);
int					ft_isstrnum(char *s);
char				*ft_jointhree(char *s1, char *s2, char *s3);
void				ft_remove_last_chr(char **str);
char				**ft_strsplit_commands(char *s);
long				ft_lpow(long a, long b);
int					ft_nextprime(int x);
int					ft_sqrt(int x);
void				ft_strptrdel(char ***as);

#	endif
