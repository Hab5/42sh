/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   othertools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbellaic <mbellaic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:19:04 by aleduc            #+#    #+#             */
/*   Updated: 2019/08/26 03:49:53 by mbellaic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

char		*reverse_str(char *inputstr)
{
	char	*start;
	int		len;
	char	*end;

	start = inputstr;
	len = ft_strlen(inputstr);
	end = (inputstr + len - 1);
	while (start < end)
	{
		*start = *start ^ *end;
		*end = *end ^ *start;
		*start = *end ^ *start;
		start++;
		end--;
	}
	return (inputstr);
}

t_node		*find_tail(t_node *lstcursor, t_pos *pos)
{
	int		backup;

	backup = 0;
	savecursor(pos);
	while (lstcursor && lstcursor->prev != NULL)
	{
		stalk_cursor(pos);
		if (pos->column != pos->termsize.ws_col)
			ft_putstr(tgetstr("nd", NULL));
		else
			go_downleft(pos);
		backup++;
		lstcursor = lstcursor->prev;
	}
	while (lstcursor && backup-- > 1)
		lstcursor = lstcursor->next;
	stalk_cursor(pos);
	pos->tailcolumn = pos->column;
	pos->tailrow = pos->row;
	cursorback(pos);
	return (lstcursor);
}

char		*lst_to_str_mod(t_multi *lstcursor, char *temp)
{
	int		i;
	int		len;
	t_node	*cpycursor;

	i = 0;
	len = 0;
	cpycursor = lstcursor->input->next;
	while (cpycursor)
	{
		len++;
		cpycursor = cpycursor->next;
	}
	cpycursor = lstcursor->input->next;
	if (!(temp = malloc(sizeof(char) * len + 2)))
		return (NULL);
	while (cpycursor)
	{
		temp[i++] = cpycursor->key;
		cpycursor = cpycursor->next;
	}
	temp[i++] = '\n';
	temp[i] = '\0';
	temp = reverse_str(temp);
	return (temp);
}

char		*lst_to_str_loop(t_multi *lstcursor, char *inputstr)
{
	char	*temp;
	char	*trash;

	temp = NULL;
	while (lstcursor)
	{
		temp = lst_to_str_mod(lstcursor, temp);
		trash = inputstr;
		inputstr = ft_strjoin(inputstr, temp);
		free(temp);
		if (trash != NULL)
			free(trash);
		lstcursor = lstcursor->prev;
	}
	return (inputstr);
}

char		*lst_to_str(t_multi **multi, char *inputstr)
{
	t_multi	*lstcursor;
	char	*finalstr;
	int		i;

	inputstr = ft_strdup("\0");
	lstcursor = *multi;
	while (lstcursor->next)
		lstcursor = lstcursor->next;
	inputstr = lst_to_str_loop(lstcursor, inputstr);
	inputstr++;
	finalstr = ft_strdup(inputstr);
	inputstr--;
	ft_strdel(&inputstr);
	i = 0;
	while (finalstr[i])
		if (finalstr[i++] != ' ' || finalstr[i] != '\t')
			return (finalstr);
	ft_strdel(&finalstr);
	return (NULL);
}
