/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 09:17:14 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 09:48:59 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef JOB_H
#	define JOB_H

#include "sh21.h"
#include "env.h"

void			assembly_command_s(t_process *p, char **str);

/*
** job_running.c
*/

int				jobs_running(void);

/*
** shell_struct.c
*/

t_shell			**static_shell(void);
t_shell			*get_shell(void);
void			delete_shell(void);

/*
** signaux.c
*/

void			ign_signaux(void);
void			dfl_signaux(void);

/*
** list_job.c
*/

t_process		*init_process(void);
t_job			*init_job(void);
t_job			**static_job(void);
t_job			*get_first_job(t_job *new_job);
t_job			*create_new_job(char **argv, t_token *t,
					t_redirection *r, int fg);

/*
** tools_job.c
*/

t_job			*find_job(pid_t pid);
int				job_is_completed(t_job *job);
int				job_is_stopped(t_job *job);

/*
** free_job.c
*/

void			free_all_job(void);
void			free_job(t_job **j);

/*
** free_job_file.c
*/

void			free_redirection(t_redirection **r);
void			clean_file(t_job *j);
void			clean_redirection(t_redirection *r);

/*
** process.c
*/

int				launch_process(t_process *p, pid_t pgid, int fg);
int				launch_job(t_job *j, int fg);
void			act_job(t_job *j, int fg);

/*
** process_tools.c
*/

void			edit_pid_shell(int pid, t_job *j, t_process *p);
void			config_pid_process(pid_t pgid, int fg);
void			act_job(t_job *j, int fg);

/*
** process_pipe.c
*/

void			launch_job_pipe(t_job *j, int fg);

/*
** process_pipe_fd.c
*/

void			pipe_deplace_fd(t_job *j, t_process *p, int fd);

/*
** add_job.c
*/

void			add_in_fg(t_job *j, int value);
void			add_in_bg(t_job *j, int value);

/*
** gest_process.c
*/

void			wait_for_job(t_job *j);
void			update_status(void);
int				mark_process_status(pid_t pid, int status);

/*
** status_process.c
*/

void			job_notif(void);
void			job_running(t_job *j);
void			continue_job(t_job *j, int fg);

/*
** clean_commands.c
*/

void			display_lst_job(t_job *j);
void			clean_fuck_list(pid_t pid);
void			free_job_redirection(t_job **j);

/*
** manage_id_job.c
*/

int				manage_id_job(int action);
int				id_job(int value, int action);

#	endif
