/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh21.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 02:17:27 by mbellaic          #+#    #+#             */
/*   Updated: 2019/08/27 08:34:21 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH21_H
# define SH21_H

# include <termios.h>
# include <term.h>
# include <unistd.h>
# include <stdlib.h>
# include <pwd.h>
# include <sys/ioctl.h>
# include "libft.h"
# include "get_next_line.h"

# define PRINTABLE (buffer[0] >= 32 && buffer[0] < 127)

# define ALT_X (buffer[0] == -30 && buffer[1] == -119 && buffer[2] == -120)
# define ALT_C (buffer[0] == -61 && buffer[1] == -89)
# define ALT_V (buffer[0] == -30 && buffer[1] == -120 && buffer[2] == -102)

# define CTRL_D (buffer[0] == 4 && buffer[1] == 0)
# define CTRL_C (buffer[0] == 3 && buffer[1] == 0)
# define CTRL_R (buffer[0] == 18 && buffer[1] == 0)

# define DELETE (buffer[0] == 27 && buffer[2] == '3')
# define BACKSPACE (buffer[0] == 127 && buffer[1] == 0)

# define HOME (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 72)
# define END (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 70)
# define PG_UP (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 53)
# define PG_DOWN (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 54)

# define ARROW_UP   (buffer[0] == 27 && buffer[2] == 'A')
# define ARROW_DOWN   (buffer[0] == 27 && buffer[2] == 'B')
# define ARROW_RIGHT (buffer[0] == 27 && buffer[2] == 'C')
# define ARROW_LEFT (buffer[0] == 27 && buffer[2] == 'D')

# define SHIFT_UP (buffer[0] == 27 && buffer[1] == 91 && buffer[5] == 'A')
# define SHIFT_DOWN (buffer[0] == 27 && buffer[1] == 91 && buffer[5] == 'B')
# define SHIFT_RIGHT (buffer[0] == 27 && buffer[1] == 91 && buffer[5] == 'C')
# define SHIFT_LEFT (buffer[0] == 27 && buffer[1] == 91 && buffer[5] == 'D')

# define ENTER (buffer[0] == 10 && buffer[1] == 0)

char **g_env;
int		g_in;

typedef struct		s_node
{
	char			key;
	char			*line;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;

typedef struct		s_multi
{
	t_node			*input;
	struct s_multi	*prev;
	struct s_multi	*next;
}					t_multi;

typedef struct		s_integerity
{
	int				quote;
	int				dquote;
}					t_integrity;

typedef struct		s_pos
{
	size_t			inputlen;
	size_t			nblines;
	size_t			currentline;

	struct winsize	termsize;

	size_t			row;
	size_t			column;
	size_t			startrow;
	size_t			startcolumn;
	size_t			tailrow;
	int				tailcolumn;
	size_t			saverow;
	size_t			savecolumn;

	t_node			*history;
	char			*hisbackup;
	int				historycount;
	int				historysum;

	char			*clipboard;
	int				selection;
	int				selectcount;

	int				multiline;
	int				stop;
}					t_pos;

void				welcome(void);
void				default_term_mode(void);
void				raw_term_mode(void);

void				init_heredoc(t_pos *pos);

t_node				*check_input(t_node *lstcursor, t_node **input, \
										char buffer[], t_pos *pos);
void				wrapping(t_pos *pos);
void				redraw(t_pos *pos, t_node *lstcursor);
void				actualize(t_pos *pos, t_node *lstcursor, \
								t_node **input, char buffer);
t_node				*editline(t_pos *pos, t_node *lstcursor, \
								t_node **input, char buffer[]);
t_node				*read_input(t_node **input, t_pos *pos);

void				savecursor(t_pos *pos);
void				cursorback(t_pos *pos);
void				get_cursor(int i, int j, char answer[], t_pos *pos);
void				stalk_cursor(t_pos *pos);
void				go_upright(t_pos *pos);
void				go_downleft(t_pos *pos);

t_node				*left(t_node *lstcursor, char buffer[], t_pos *pos);
t_node				*right(t_node *lstcursor, char buffer[], t_pos *pos);
t_node				*up(t_node *lstcursor, t_node **input, \
								char buffer[], t_pos *pos);
t_node				*down(t_node *lstcursor, t_node **input, \
								char buffer[], t_pos *pos);
t_node				*backspace(t_node *lstcursor, t_node **input, \
										char buffer[], t_pos *pos);
t_node				*del_key(t_node *lstcursor, t_node **input, \
									char buffer[], t_pos *pos);
t_node				*home_end(t_node *lstcursor, char buffer[], t_pos *pos);
t_node				*backwardjump(t_node *lstcursor, char buffer[], t_pos *pos);
t_node				*forwardjump(t_node *lstcursor, char buffer[], t_pos *pos);
t_node				*ctrl_n_friends(t_node *lstcursor, t_node **input, \
											char buffer[], t_pos *pos);

void				cpy_std(int in, int out, int error);
void				ft_name_exec(char *name_exec);
void				init_alias(void);
int					check_whitespace_input(char *input);

void				dpush(t_node **head, char key);
void				dprintlist(t_node *node, int direction);
void				insert(t_node *prev_node, char key);
void				ddel(t_node **head, t_node *del);
void				ddelmul(t_multi **head, t_multi *del);
void				ddellist(t_multi *head);
void				multi_push(t_multi **head);

void				print_prompt(void);
char				*reverse_str(char *inputstr);
char				*lst_to_str(t_multi **input, char *inputstr);
int					ft_outc(int c);
void				get_inputlen(t_pos *pos, t_node *input);
void				get_startingpos(t_pos *pos);
void				get_tail(t_pos *pos);
t_node				*travel_to_last(t_node *lstcursor, t_pos *pos);

void				inserthistory(t_node *prev_node, char *line, t_pos *pos);
t_node				*clean_for_history(t_node *lstcursor, t_node **input,\
															t_pos *pos);
t_node				*history_to_lst(t_node *lstcursor, char *historyline, \
											t_node **input, t_pos *pos);
t_node				*history_downcase(t_node *lstcursor, t_node **input, \
															t_pos *pos);
void				history_file(t_node *history);
void				file_to_history(t_pos *pos);
char				*prompt_search(t_node *input, t_pos *pos, int *ret);
char				*history_no_double(t_pos *pos);
char				*search_to_str(t_node *input);

t_node				*selectmode(t_node **input, t_node *lstcursor, \
										char buffer[], t_pos *pos);
t_node				*paste_clipboard(t_node **input, t_node *lstcursor, \
															t_pos *pos);
t_node				*shift_left(t_node *lstcursor, char buffer[], t_pos *pos);
t_node				*shift_right(t_node *lstcursor, char buffer[], t_pos *pos);
void				copy_selection(t_node *lstcursor, t_pos *pos);
t_node				*anchor_selection(t_node *lstcursor, t_pos *pos, \
													int direction);
t_node				*delete_selection(t_node **input, t_node *lstcursor, \
															t_pos *pos);
t_node				*undo_selection(t_node *lstcursor, t_pos *pos);
t_node				*find_tail(t_node *lstcursor, t_pos *pos);

void				reset_multi(t_pos *pos);
void				reset_stop(char **inputstr, t_pos *pos, t_integrity *count);
void				key_occurence(t_node *cursor, t_integrity *count);
void				dquote(t_multi *lstcursor, t_multi **multi, t_pos *pos);
void				quote(t_multi *lstcursor, t_multi **multi, t_pos *pos);
char				*heredoc(char *heredoc, t_pos *pos);
int					check_integrity(t_node *input, t_multi **multi, \
								t_pos *pos, t_integrity *count);

void				init_prompt(t_pos *pos);
t_node				*read_input(t_node **input, t_pos *pos);
int					count_escape_backslash(t_node *input);
int					check_backslash(t_node *input, t_multi **multi, \
		t_pos *pos, t_integrity *count);
void				line_to_history(char **inputstr, t_pos *pos);
char				*prompt(t_multi *input, t_pos *pos);

char				*expand_double_schriek(t_pos *pos);
char				*expand_schriek_word(t_pos *pos, char *word);
char				*expand_schriek_number(t_pos *pos, int number);
char				*expand_schriek_less(t_pos *pos, int number);

void				run(char *input, t_pos *pos);
#endif
