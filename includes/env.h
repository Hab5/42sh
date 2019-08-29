/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 13:33:53 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 19:15:02 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef ENV_H
#	define ENV_H

#include "sh21.h"
#include "lexer.h"
#include "parser.h"
#include "libft.h"
#include <curses.h>
#include <term.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#	ifdef __linux__
#	define OS 1
#	else
#	define OS 0
#	endif

typedef struct		s_fc
{
	char		*editor;
	int			flags[5];
	char		*first;
	char		*last;
	char		*pat_rep;
	char		*cmd;
	int			first_index;
	int			last_index;
}					t_fc;

typedef struct		s_redirect
{
	int					base;
	int					new_fd;
	int					type;
	char				*name_file;
	struct s_redirect	*next;
}					t_redirect;

typedef struct		s_redirection
{
	int			in;
	int			out;
	int			error;
	t_redirect	*redirect;
}					t_redirection;

typedef struct		s_env
{
	char			*key;
	char			*value;
	int				see_env;
	struct s_env	*next;
}					t_env;

typedef struct		s_shell
{
	pid_t			pgid;
	char			*name_shell;
	struct termios	term_shell;
	int				interactive;
	int				term;
	int				max_job_current;
}					t_shell;

typedef struct		s_process
{
	char				*final_str;
	char				*cmd_path;
	char				**cmd;
	pid_t				pid;
	int					completed;
	int					stopped;
	int					status;
	int					return_value;
	int					fg;
	int					last_status;
	t_redirection		*r;
	struct s_process	*next;
}					t_process;

/*
**	current = 1 if current, 2 if previous, 0 if other
*/

typedef struct		s_job
{
	t_process		*first_process;
	pid_t			pgid;
	char			*cmd;
	int				fg;
	int				process_id;
	int				notified;
	int				notif_stop;
	int				signal;
	struct termios	tmodes;
	int				len_close;
	int				*close_fd;
	t_redirection	*r;
	struct s_job	*next;
	int				current;
}					t_job;

int					exec_ft_simple_command(t_job *j, t_process *p,
		t_pos *pos, int fg);
void				edit_current_value(int value);
char				*ft_construct_redirection(t_token *token);
void				reset_hash_verif(char *key);

int					ft_simple_command_fc(char *editor);

void				fill_shell_dumb_mode(void);

int					convert_value_signal(int status);

char				*name_exec_error(void);

void				kill_pgid(t_shell *shell, t_job *j);

/*
** redirection.c
*/

void				redirection_fd(t_redirection *r);
void				standard_redirection(t_redirection *r);
int					this_signal(t_process *p);

/*
** redirection_bis.c
*/

void				redirection_fd_bis(t_redirection *r);

/*
** rediretion_bis.c
*/

void				redir_in(t_redirection *r);
void				redir_out(t_redirection *r);
void				redir_error(t_redirection *r);
void				other_redir(t_redirect *r);

/*
** check_last.c
*/

int					check_last_command(void);
int					check_is_exec(char *src, t_redirection *r);

/*
** manage_variable.c
*/

char				*manage_var(char *str);
int					manage_home(char *src, char **dst, int index);
int					modify_dst(char *tmp, char **dst);

/*
** list_redirection.c
*/

t_redirection		*init_redirection(void);
t_redirection		*base_redirection(void);

/*
** apply_redirection.c
*/

t_redirection		*fill_redirection(t_token *t);

/*
** delete_redirection.c
*/

void				delete_redirection(t_redirection **r);
int					verif_close(int fd);

/*
** other_tools.c
*/

int					gest_error_path(char *cmd, t_redirection *r);
int					gest_return(int verif);
char				*is_in_path(char *command, int hash);
t_env				*get_env(int is_end, t_env *head);

/*
** check_path.c
*/

void				check_exec_path(char **str);

/*
** restore_redir_builtin.c
*/

void				restore_and_return_builtin(int verif);

/*
** is_builtin.c
*/

int					builtin_exist(char *cmd);
int					builtin(t_job *j, t_process *p, t_pos *pos, int fg);
int					is_builtin(t_job *j, t_process *p, t_pos *pos);

/*
** parser_var.c
*/

void				parser_var(char ***value);
void				parser_var_simple(char **value, uint8_t flag);

/*
** parser_var_bis.c
*/

void				copy_value(char *src, char **dst, int start, int end);
char				*search_var(char *src);
int					manage_is_quote(char *value, int index, int expand);
int					is_expand_tild(char *value, int index, int expand);

/*
** apply_parser_var.c
*/

int					apply_rules(char *src, char **dst, int index);

/*
** manage_env.c
*/

int					edit_setenv(char *key, char *value);
int					edit_export(char *key);
int					ft_unsetenv(char **key);
char				**create_list_env(t_env *my_env, int env);

/*
** manage_set.c
*/

int					edit_set(char **value, t_redirection *r, t_pos *pos);
int					ft_unset(char **value);
int					edit_set_command_env(char *str, t_env *my_env);

/*
** manage_set_bis.c
*/

int					verif_syntax_key(char *key);
int					edit_set_no_command(char **value, int env);
void				apply_edit_set_no_command_env(char *key, char **value,
			int i, int cnt);

/*
** manage_export.c
*/

int					edit_export(char *key);

/*
** add_set_value.c
*/
int					add_set_value_perm(char *key, char *value, int perm);
int					add_set_value(char *key, char *value);

/*
** tools_env.c
*/

char				*value_line_path(char *key, int env);
int					create_new_line_env(t_env *my_env, char *key, char *value,
		int env);
int					value_is_empty(char *key);

/*
** builtin_env.c
*/

int					builtin_set(t_redirection *r);
int					builtin_env(t_redirection *r, char **argv, t_pos *pos);

/*
** builtin_cd.c
*/

int					builtin_cd(char **arguments);

/*
** builtin_cd_verif.c
*/

int					ft_lastchr(const char *s, int c);
void				check_arg(char **str);
void				error_cd(int code, char *str);

/*
** list_env.c
*/

t_env				*init_env(void);
t_env				*init_maillon_env(void);
void				init_variable(void);
t_env				*ft_cpy_env(void);

/*
** free_env.c
*/

void				free_env(t_env **env);
int					free_maillon_env(char *key, int env);

/*
** manage_file.c
*/

void				whois_type(int type);
int					open_file_command(t_redir *redir, t_pos *pos);

/*
** action_file.c
*/

int					file_exist(char *name, int type);
int					open_file_great(t_redir *redir);
int					open_file_dless(t_redir *redir, t_pos *pos);

/*
** commands.c
*/

int					ft_simple_command(char **argv, t_token *lex, t_pos *pos,
						int bg);
int					ft_simple_command_redirection(char **argv,
						t_redirection *r, t_pos *pos, int fg);
int					is_not_builtin(t_job *j, t_process *p, int fg);

/*
** errors.c
*/

void				execve_bin_test(void);
void				display_command_not_found(t_redirection *r, char *cmd);
void				display_permission_denied(t_redirection *r, char *cmd);
void				display_error_fork(t_redirection *r);
void				display_too_many_arg(t_redirection *r, char *name);
void				display_too_few_arg(t_redirection *r, char *name);
void				display_nothing_value(t_redirection *r, char *name);
void				display_bad_file_descriptor(int error);
void				display_no_such_job(char *name_blt, char *name);
void				display_invalid_option_job(t_redirection *r, char *name);
void				display_no_current_job(char *name);
void				display_no_job_control(char *name);
void				display_job_stopped(void);
void				display_kill_not_work(t_redirection *r, char *name);
void				display_error_tc(t_redirection *r, char *name);
void				display_other_error(int fd_error, char *name, char *error);
void				display_error_expansion(char *src);
void				display_error_syntax(char *key, char *value);

/*
** commands_pipe.c
*/

int					ft_pipe(char **argv, t_token *lex, int end_pipe, int bg);
int					add_pipe_process(char **cmd, t_redirection *r);

/*
** main.c
*/

void				run(char *input, t_pos *pos);

/*
** parameter_expansion.c
*/

void				parameter_expansion(char *tmp, char **dst);

/*
** gest_exansion.c
*/

char				*gest_expansion(char *key, char *value);

/*
** formats_parameter_bis.c
*/

char				*parameter_moins(char *parameter, char *word);
char				*parameter_equals(char *parameter, char *word);
char				*parameter_interrogation(char *parameter, char *word);
char				*parameter_plus(char *parameter, char *word);

/*
** expansion_hash.c
*/

char				*parameter_hash_first(char *parameter);
char				*parameter_hash_end(char *parameter);

/*
** expansion_percent.c
*/

char				*parameter_percents(char *parameter);

/*
** expansion_tools.c
*/

int					check_format_variable(char *str);

/*
** list_redirect.c
*/

int					ft_create_maillon_redirect(t_redirect *r, int base,
						int new_fd, t_redir *redir);
int					ft_create_maillon_redirect_env(t_redirect *r,
		t_redirect *old);
t_redirect			*ft_init_redirect(void);
int					ft_fd_redirect_exist(t_redirect *r, int base);

/*
** add_process.c
*/

t_job				*get_end_job(void);
void				add_process(char **av, t_token *t, int fg);

/*
**  debug
*/

void				display_redirection(t_redirection *r);

/*
** test_quote.c
*/

int					test_quote(char *name);

/*
** close_redirection.c
*/

int					file_to_close(t_token *t, t_job *j);
int					close_file_command(t_lex *lex, t_redirection **r);

/*
** remove_quote.c
*/

void				remove_quote(char ***value);
void				remove_quote_line(char **line);
void				removebackslash(char **line);

int					ft_remove_element(char **line, int i, int expand);

/*
** dup_restore.c
*/

void				stock_fd_base(void);
void				dup_restore(void);

/*
** display.c
*/

void				display_prompt(void);

#	endif
