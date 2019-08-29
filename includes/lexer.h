/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:15:13 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 10:03:08 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "libft.h"

typedef struct s_lex		t_lex;
typedef struct s_token		t_token;
typedef enum e_token_type	t_type;
typedef	struct s_tab_type	t_tab_type;
typedef	struct s_redir		t_redir;

enum	e_token_type
{
	SPIPE,
	SCOLON,
	LESS,
	DLESS,
	LESSAMP,
	GREAT,
	DGREAT,
	GREATPIPE,
	GREATAMP,
	LESSGREAT,
	SPACE,
	AMPGREAT,
	LESSAMPHYPH,
	GREATAMPHYPH,
	AMP,
	DAMP,
	DPIPE,
	NUMBER,
	WORD,
	CMD,
	DELIM,
	REDIR,
	NUL,
};

struct	s_token
{
	char	*data;
	t_lex	*command;
	t_type	type;
};

struct	s_lex
{
	t_token	*token;
	t_redir	*redir;
	t_lex	*next;
	t_lex	*prev;
};

struct	s_tab_type
{
	char	*str;
	t_type	type;
};

struct	s_redir
{
	char	**src_fd;
	char	*dest_fd;
	t_type	type;
	char	*filename;
	char	*heredoc;
	int		close;
};

void	reading_input(char *input, t_lex **lex);
void	reading_loop(char *input, t_lex **lex, t_token **tok, t_tab_type **t);

int		init_variables(t_token **tok, int *to_check, int *i, t_tab_type **t);

void	set_tab_types(t_tab_type **tab_of_types);
void	set_tab_types_2(t_tab_type **tab_of_types);
void	compare_types(t_tab_type **tab_of_types, t_token **token, char *word);

t_lex	*lexer(char *input);
void	reading_input(char *input, t_lex **lex);
int		handle_tok(t_token **tok, t_lex **lex);
int		handle_classic_case(int *i, int *last_t, char **input);
void	handle_word_case(int *i, char **input, int *last_t, int *to_check);
int		handle_string_case(int *i, int *last_t, char **input, t_token **tok);
t_token	*check_type(t_tab_type **tab_of_types, char *input, int start, int end);
int		handle_whitespace(char *input, int i, t_lex **lex);
int		ft_isnumbers(char *str);
int		is_in_tab(t_tab_type **tab_of_type, char c);
int		is_amper(char c);
int		ft_isreallyspace(char c);
int		is_lesser_greater(char c);
int		is_greater(char c);
int		is_hyph(char c);
int		skip_whitespace(char *str, int i);
int		dub_possible(char c);
void	check_double(char *input, int *i);
t_token	*handle_string(char *input, int *i, int *last_t, char c);
t_token	*handle_string_squote(char *input, int *i, int *last_t, char c);

t_token	*create_token(char *str, t_type types);
t_token	*create_command_token(t_lex **command, t_type types);
t_token	*word_or_number(char *data);
t_lex	*add_delim(t_lex **lex);
void	add_token(t_lex **lexer, t_token **token);

void	simple_command(t_lex **head);

void	set_delim(t_lex **head, t_lex **start, t_lex **end);
t_lex	*identify_delim(t_lex **start, t_lex **end);

int		type_to_ignore(t_type type);
int		type_to_end_on(t_type type);

void	detach(t_lex **start, t_lex **end);
void	attach(t_lex **head, t_lex **node, t_lex **end);
t_lex	*detaching(t_lex **start, t_lex **end);
void	attach_redir_node(t_redir **redir_info, t_lex **before_start);

int		handle_redir(t_lex **lex);
int		cycle_redirect(t_lex **command_node);
int		handle_needed_redir(t_lex **command_node, t_lex **redir_node);
void	ft_default(t_redir **redir_info);

int		handle_great(t_lex **command_node);
int		handle_great_and(t_lex **command_node);
int		handle_and_great(t_lex **command_node);
int		handle_append(t_lex **command_node);
int		handle_less(t_lex **command_node);
int		handle_less_and(t_lex **command_node);
int		handle_heredoc(t_lex **command_node);
int		handle_great_hyph(t_lex **command_node);
int		handle_less_hyph(t_lex **command_node);

t_redir	*redir_struct_great(t_lex **start);
t_redir	*redir_struct_great_and(t_lex **start);
t_redir	*redir_struct_and_great(t_lex **start);
t_redir	*redir_struct_append(t_lex **start);
t_redir	*redir_struct_less(t_lex **start);
t_redir	*redir_struct_less_and(t_lex **start);
t_redir	*redir_struct_heredoc(t_lex **start);
t_redir	*redir_struct_great_hyph(t_lex **start);
t_redir	*redir_struct_less_hyph(t_lex **start);

void	start_grammar_great(t_lex **start);
int		end_grammar_great(t_lex **start, t_lex **end, t_type type_check);
int		is_a_redirect(t_type type);

void	remove_space_token(t_lex **lexer);
void	remove_node(t_lex **node_cmd_space);
int		is_only_space(t_lex **node_cmd);

t_lex	*new_node(t_token **tok);
t_lex	*new_redir_node(t_token **tok, t_redir **redir_info);

void	dllinsfront(t_lex **head, t_lex **node);
void	dllinsback(t_lex **tail, t_lex **node);
void	dllinsafter(t_lex **prev_node, t_lex **node);
void	dllinsbefore(t_lex **next_node, t_lex **node);

void	dllprinthead(t_lex **head);
void	dllprinttail(t_lex **tail);
t_lex	*dlllastnode(t_lex **head);
int		dlliter(t_lex **head);

void	dlldelfirst(t_lex **head);
t_lex	*dlldellast(t_lex **tail);
t_lex	*dlldelone(t_lex **head, char *data);
void	dll_del_node(t_lex **node);

void	ft_error(int code_error);

void	clean_lex(t_lex **lex);
void	clean_inside_token(t_token **token);
void	clean_redir(t_redir **redir);

/*
** add_quote.c
*/

char	*add_dquote_to_str(char *str);
char	*add_squote_to_str(char **str_addr);

/*
** Handle_quotes
*/

void	handle_quotes(t_lex **head);
void	merge_string_token(t_lex **start, t_lex **end);
char	*create_merged_string(t_lex **head);
t_lex	*create_the_node(char **str);

t_lex	*identify_start(t_lex **head);
t_lex	*identify_end(t_lex **start);

#endif
