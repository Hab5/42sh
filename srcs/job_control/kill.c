/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 13:59:26 by sbelondr          #+#    #+#             */
/*   Updated: 2019/08/27 09:29:57 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "sh21.h"

/*
** Kill job and restore shell value
** TCSADRAIN -> the change occurs after all output written to fildes has been
**				transmitted to the terminal.
** kill(-pgid, SIG) -> kill un groupe d'id
*/

void	kill_pgid(t_shell *shell, t_job *j)
{
	if (tcsetattr(shell->term, TCSADRAIN, &(j->tmodes)) == -1)
		display_error_tc(j->r, "tcsetattr");
	if (kill(-j->pgid, SIGCONT) < 0)
		display_kill_not_work(j->r, "fg");
}
