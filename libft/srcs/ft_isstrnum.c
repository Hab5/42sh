/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstrnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apruvost <apruvost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:38:12 by apruvost          #+#    #+#             */
/*   Updated: 2019/08/27 10:44:54 by apruvost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_over_llongmaxquad(char *s, int neg, int i)
{
	if (s[++i] < '7')
		return (1);
	else if (s[i] > '7')
		return (0);
	if (s[++i] < '7')
		return (1);
	else if (s[i] > '7')
		return (0);
	if (s[++i] < '5')
		return (1);
	else if (s[i] > '5')
		return (0);
	if (s[++i] < '8')
		return (1);
	else if (s[i] > '8')
		return (0);
	if (s[++i] < '0')
		return (1);
	else if (s[i] > '0')
		return (0);
	if (s[++i] <= '7' && neg == 0)
		return (1);
	if (s[i] <= '8' && neg == 1)
		return (1);
	return (0);
}

static int		ft_is_over_llongmaxtri(char *s, int neg, int i)
{
	if (s[++i] < '0')
		return (1);
	else if (s[i] > '0')
		return (0);
	if (s[++i] < '3')
		return (1);
	else if (s[i] > '3')
		return (0);
	if (s[++i] < '6')
		return (1);
	else if (s[i] > '6')
		return (0);
	if (s[++i] < '8')
		return (1);
	else if (s[i] > '8')
		return (0);
	if (s[++i] < '5')
		return (1);
	else if (s[i] > '5')
		return (0);
	if (s[++i] < '4')
		return (1);
	else if (s[i] > '4')
		return (0);
	return (ft_is_over_llongmaxquad(s, neg, i));
}

static int		ft_is_over_llongmaxbis(char *s, int neg, int i)
{
	if (s[++i] < '3')
		return (1);
	else if (s[i] > '3')
		return (0);
	if (s[++i] < '7')
		return (1);
	else if (s[i] > '7')
		return (0);
	if (s[++i] < '2')
		return (1);
	else if (s[i] > '2')
		return (0);
	return (ft_is_over_llongmaxtri(s, neg, i));
}

static int		ft_is_over_llongmax(char *s)
{
	int	neg;
	int	i;

	neg = 0;
	i = 0;
	if (s[i] == '-')
	{
		neg = 1;
		++i;
	}
	if (s[i] < '9')
		return (1);
	if (s[++i] < '2')
		return (1);
	else if (s[i] > '2')
		return (0);
	if (s[++i] < '2')
		return (1);
	else if (s[i] > '2')
		return (0);
	if (s[++i] < '3')
		return (1);
	else if (s[i] > '3')
		return (0);
	return (ft_is_over_llongmaxbis(s, neg, i));
}

int				ft_isstrnum(char *s)
{
	int		len;
	char	*t;

	len = 0;
	if (s)
	{
		t = s;
		if (*s == '-')
			s++;
		while (*s)
		{
			if (!(ft_isdigit(*s)))
				return (0);
			++len;
			s++;
		}
		if (len > 19)
			return (0);
		else if (len == 19)
			return (ft_is_over_llongmax(t));
		return (1);
	}
	return (0);
}
