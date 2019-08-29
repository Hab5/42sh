/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 07:46:11 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/27 14:12:29 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef BUILTINS_H
#	define BUILTINS_H

#	define HT_HASH_HASH_ONE 3
#	define HT_HASH_HASH_TWO 7
#	define HT_HASH_BASE_SIZE 50

#	define FC_L (fc->flags[0] == 1)
#	define FC_N (fc->flags[1] == 1)
#	define FC_R (fc->flags[2] == 1)
#	define FC_E (fc->flags[3] == 1)
#	define FC_S (fc->flags[4] == 1)
#	define FC_NO_FLAGS  (!FC_L && !FC_N && !FC_R && !FC_E && !FC_S)

#include "env.h"
#include "job.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>

typedef struct			s_hist_rep
{
	int					isrep;
	char				*base;
	char				*value;
	struct s_hist_rep	*next;
}						t_hist_rep;

typedef struct			s_cd
{
	int					arg__;
	int					arg_l;
	int					arg_p;
	char				*directory;
	char				*curpath;
}						t_cd;

typedef struct			s_hash
{
	char				*key;
	char				*value;
}						t_hash;

typedef struct			s_ht_hash
{
	int					size;
	int					base_size;
	int					count;
	t_hash				**hash;
}						t_ht_hash;

typedef struct			s_hash_tree
{
	t_hash				*hash;
	struct s_hash_tree	*left;
	struct s_hash_tree	*right;
}						t_hash_tree;

typedef struct			s_repalias
{
	char				*key;
	char				*value;
	struct s_repalias	*next;
}						t_repalias;

typedef struct			s_unary_tab
{
	int					(*f)(char *str1, char *str2, char *str3);
	char				*str;
}						t_unary_tab;

int						bt_exit(t_job *j, t_pos *pos, t_redirection *r);
int						bt_echo(char **av, t_redirection *r);

int						bt_cd(char **av, t_redirection *r);
int						cd_dirnull(t_cd *cd);
int						cd_less(t_cd *cd);
int						cd_testcdpath(char *path, char *directory, char **test);
int						cd_testpath(char *path, char *directory, char **test);
int						cd_getnextpath(char *path, int tozero);
int						cd_test_cdpath(t_cd *cd, char *test);
int						cd_canonical(t_cd *cd);
int						cd_canonical_a(t_cd *cd);
int						cd_canonical_b(t_cd *cd);
int						cd_canonical_c(t_cd *cd);
int						is_env_empty(char *value);
int						cd_canonical_del(t_cd *cd, size_t a, \
						size_t b, size_t len);
int						cd_chdir(t_cd *cd);
int						cd_err(t_cd *cd);
int						cd_getopt(char ac, char **av, t_cd *cd);

/*
** bt_test.c
*/

int						bt_test(char **av, t_redirection *r);
int						is_binary(char *str2);
int						unary_test(char *str1, char *str2);
int						binary_test(char *str1, char *str2, char *str3);

int						bt_1(char *av1);
int						bt_2(char *av1, char *av2);
int						bt_3(char *av1, char *av2, char *av3);
int						bt_4(char *av1, char *av2, char *av3, char *av4);
int						bt_5(void);

void					create_unary_list(t_unary_tab **tab_lst);
void					create_binary_list(t_unary_tab **tab_lst);

int						b_test(char *str1, char *str2, char *str3);
int						c_test(char *str1, char *str2, char *str3);
int						d_test(char *str1, char *str2, char *str3);
int						e_test(char *str1, char *str2, char *str3);
int						f_test(char *str1, char *str2, char *str3);
int						g_test(char *str1, char *str2, char *str3);
int						upper_l_test(char *str1, char *str2, char *str3);
int						p_test(char *str1, char *str2, char *str3);
int						r_test(char *str1, char *str2, char *str3);
int						upper_s_test(char *str1, char *str2, char *str3);
int						s_test(char *str1, char *str2, char *str3);
int						u_test(char *str1, char *str2, char *str3);
int						w_test(char *str1, char *str2, char *str3);
int						x_test(char *str1, char *str2, char *str3);
int						z_test(char *str1, char *str2, char *str3);

int						verify_only_alpha(char *str1, char *str2);
int						equal_test(char *str1, char *str2, char *str3);
int						notequal_test(char *str1, char *str2, char *str3);
int						eq_test(char *str1, char *str2, char *str3);
int						ne_test(char *str1, char *str2, char *str3);
int						ge_test(char *str1, char *str2, char *str3);
int						lt_test(char *str1, char *str2, char *str3);
int						le_test(char *str1, char *str2, char *str3);

void					clean_test_tab(t_unary_tab **tab_lst);

/*
** bt_jobs.c
*/

int						bt_jobs(t_job *j, char **av, t_redirection *r);

/*
** bt_bg.c
*/

int						bt_bg(t_job *j, char **av, t_redirection *r);

/*
** bt_fg.c
*/

int						bt_fg(t_job *j, char **av, t_redirection *r);

/*
** bt_fg_bg_tools.c
*/

t_job					*job_for_bg_fg(char **av);
void					change_fg_var_job(t_job *j, int fg);

/*
** bt_jobs_tools.c
*/

char					*assembly_cmd_process(t_process *p);
char					*cmd_job_s(t_job *j);
char					*ft_inter_signal(int sig, t_job *j);

/*
** bt_jobs_tools_bis.c
*/

char					*ft_name_sig(int sig);
t_job					*ft_search_exist_job(char *av, int index);

/*
** bt_jobs_options.c
*/

t_job					*search_job(char *av);
void					display_jobs_options(void (*p)(t_job*, int), char **av);

/*
** bt_jobs_display.c
*/

char					value_char_job(int current, int max);
void					bt_jobs_p(t_job *j, int max_current);
void					bt_jobs_l(t_job *j, int max_current);
void					bt_jobs_s(t_job *j, int max_current);

/*
** search_job.c
*/

t_job					*last_jobs(void);
t_job					*previous_jobs(void);
t_job					*ft_search_pid_job(pid_t pid);
t_job					*ft_search_id_job(char *av, int index);
t_job					*ft_search_str_job(char *av, int index);

/*
** bt_export.c
*/
int						bt_export(char **value, t_redirection *r);

/*
** builtin_env.c
*/

int						builtin_env_display(t_redirection *r);

int						bt_alias(char **av, t_redirection *r);
int						bt_unalias(char **av, t_redirection *r);

void					hash_del(t_hash *hash);
t_hash					*hash_new_item(const char *k, const char *v);
t_ht_hash				*ht_hash_new(void);
t_ht_hash				*ht_hash_new_sized(const int base_size);
void					ht_hash_del(t_ht_hash *ht);
int						ht_hash_get_hash(const char *s, const int num, \
						const int attempt);
int						ht_hash_hash(const char *s, const int a, const int m);
void					ht_hash_insert(t_ht_hash *ht, \
						const char *key, char *val);
void					ht_hash_insert_item(t_ht_hash *ht, const char *key, \
						t_hash *item, int index);
char					*ht_hash_search(t_ht_hash *ht, const char *key);
void					ht_hash_delete(t_ht_hash *ht, const char *key);
void					ht_hash_delete_item(t_ht_hash *ht, const char *key, \
						t_hash *item, int index);
void					ht_hash_resize(t_ht_hash *ht, const int base_size);
void					ht_hash_copy(t_ht_hash *ht, t_ht_hash *new_ht);
void					ht_hash_resize_down(t_ht_hash *ht);
void					ht_hash_resize_up(t_ht_hash *ht);
void					ht_hash_table_null(t_hash **hash, int size);
void					ht_hash_show(t_ht_hash *ht, int quote);
void					ht_hash_reset(t_ht_hash **ht);

int						bt_hash(char **av, t_redirection *r);

int						bt_type(char **av, t_redirection *r);

int						ft_getopt(int ac, char *const *av, const char *optstr);
void					ft_getopt_reset(void);

char					*alias_replace(char *input, t_repalias *cur_alias);
t_repalias				*alias_rep_addalias(t_repalias *cur_alias, char *base, \
						char *val);
t_repalias				*alias_rep_delalias(t_repalias *cur_alias);
void					alias_handle_redir(t_lex **lex, t_lex *ptr);

char					*history_replace(char *input, t_pos *pos);
t_hist_rep				*hist_rep_save(char *input, int start, int i, \
						t_hist_rep *replace);
t_hist_rep				*hist_rep_saveexp(char *input, int start, int i, \
						t_hist_rep *replace);
char					*hist_rep_replace(t_hist_rep *replace, t_pos *pos);
void					hist_rep_delstruct(t_hist_rep *to_del);
int						hist_rep_getexp(char *input);
int						hist_rep_isvalid(char *input);
int						hist_rep_isbslashed(char *input, int i, int expand);
char					*hist_rep_reperr(char *new, t_hist_rep *curr);
char					*hist_rep_rep(char *bin, char *value);
int						hist_rep_exists(t_hist_rep *replace, t_pos *pos);
void					hist_rep_savenew(int start, int i, t_hist_rep *new, \
						char *input);
t_hist_rep				*history_replace_get(char *input, t_hist_rep *replace, \
						int i, int start);

/*
** history_fc.c
*/

int						fc_no_flags(char **av, t_fc *fc);
int						fc_flags_e(char **av, t_fc *fc);
int						fc_flags_s(char **av, t_fc *fc);
int						fc_get_args(char **av, int argc, t_fc *fc);
int						fc_flags_lnr(char **av, t_fc *fc);

int						fc_print_first_last(t_fc *fc, t_node *lstcursor, int i);
int						fc_print_last_first(t_fc *fc, t_node *lstcursor, int i);

char					*fc_rep(char *str, char *pat_rep);
int						fc_s_all(t_fc *fc, t_node *lstcursor, \
						t_pos *pos, int count);
int						fc_s(t_fc *fc, t_pos *pos);

int						fc_check_editor(t_fc *fc);
void					fc_filter_history(t_fc *fc, t_pos *pos);
int						fc_e_run_command(t_pos *pos);
int						fc_write_last_first(t_fc *fc, \
						t_node *lstcursor, int count);
int						fc_write_file(t_fc *fc, t_node *lstcursor, int count);
int						fc_e_basic(t_fc *fc, t_node *lstcursor, t_pos *pos);
int						fc_e_first(t_fc *fc, t_node *lstcursor, \
						t_pos *pos, int count);
int						fc_e_first_last(t_fc *fc, \
						t_node *lstcursor, t_pos *pos, int count);
int						fc_e(t_fc *fc, t_pos *pos);

int						fc_lr_basic(t_fc *fc, t_node *lstcursor, \
						int count, int i);
int						fc_l_basic(t_fc *fc, t_node *lstcursor, \
						int count, int i);
int						fc_lr_first_nb(t_fc *fc, t_node *lstcursor, \
						int count, int i);
int						fc_l_first_nb(t_fc *fc, t_node *lstcursor, \
						int count, int i);
int						fc_lr_first_word(t_fc *fc, t_node *lstcursor, \
						int count, int i);
int						fc_l_first_word(t_fc *fc, t_node *lstcursor, \
						int count, int i);
int						fc_l_first(t_fc *fc, t_node *lstcursor, \
						int count, int i);
int						fc_l_first_last(t_fc *fc, t_node *lstcursor, \
						int count, int i);
int						fc_l_minus(t_fc *fc, int count);
int						fc_l(t_fc *fc, t_pos *pos);

int						fc_usage(int return_value, t_fc *fc, int error);
void					fc_debug(t_fc *fc);
int						fc_count(t_node *history);
int						fc_get_index_len(t_node *lstcursor, \
						char *fc_first_last);
int						fc_get_index(t_node *lstcursor, int count, \
						int *fc_index, char *fc_first_last);
int						builtin_fc(char **av, t_pos *pos);
#	endif
