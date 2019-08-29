/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:19:28 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/26 05:05:26 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "job.h"
#include "builtins.h"

void				welcome(void)
{
	ft_putstr("\033[2J\033[H");
	ft_putstr("\033[1;32m\n");
	ft_putstr("██╗  ██╗██████╗ ███████╗██╗  ██╗    \n");
	usleep(100000);
	ft_putstr("██║  ██║╚════██╗██╔════╝██║  ██║    \n");
	usleep(100000);
	ft_putstr("███████║ █████╔╝███████╗███████║    \n");
	usleep(100000);
	ft_putstr("╚════██║██╔═══╝ ╚════██║██╔══██║    \n");
	usleep(100000);
	ft_putstr("     ██║███████╗███████║██║  ██║    \n");
	usleep(100000);
	ft_putstr("     ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝    \n");
	usleep(100000);
	ft_putendl("\033[0m");
}

void				default_term_mode(void)
{
	struct termios	term;
	t_shell			*s;
	int				pgid;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ECHO | ICANON | ISIG);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &term);
	ft_putstr(tgetstr("ei", NULL));
	ign_signaux();
	pgid = getpid();
	if (setpgid(pgid, pgid) < 0)
		exit(1);
	s = get_shell();
	s->pgid = pgid;
	s->term = STDIN_FILENO;
	s->interactive = isatty(STDIN_FILENO);
	s->term_shell = term;
}

void				fill_shell_dumb_mode(void)
{
	t_shell			*s;
	int				interactive;
	int				pgid;
	struct termios	term;
	static int		pass;

	if (pass > 0)
		return ;
	ign_signaux();
	++pass;
	interactive = isatty(STDIN_FILENO);
	if (!interactive)
		return ;
	pgid = getpid();
	tcsetpgrp(STDIN_FILENO, getpid());
	tcgetattr(STDIN_FILENO, &term);
	s = get_shell();
	s->pgid = pgid;
	s->term = STDIN_FILENO;
	s->interactive = interactive;
	s->term_shell = term;
}

void				fill_shell(int interactive, struct termios term,
							int pgid)
{
	t_shell			*s;

	s = get_shell();
	s->pgid = pgid;
	s->term = STDIN_FILENO;
	s->interactive = interactive;
	s->term_shell = term;
}

void				raw_term_mode(void)
{
	struct termios	term;
	int				pgid;
	int				interactive;

	interactive = isatty(STDIN_FILENO);
	if (interactive)
	{
		pgid = getpgrp();
		while (tcgetpgrp(STDIN_FILENO) != (pgid = getpgrp()))
			kill(-pgid, SIGTTIN);
		ign_signaux();
		pgid = getpid();
		if (setpgid(pgid, pgid) < 0)
			exit(1);
		tcsetpgrp(STDIN_FILENO, getpid());
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		tgetent(NULL, getenv("TERM"));
		fill_shell(interactive, term, pgid);
	}
}
