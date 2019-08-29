/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mergesort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 18:38:12 by skuppers          #+#    #+#             */
/*   Updated: 2018/02/10 10:35:26 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

static void		merge(int arr[], int l, int m, int r)
{
	t_merge		stat;
	int			left[m - l + 1];
	int			right[r - m];

	stat.i = -1;
	stat.j = -1;
	while (++stat.i < (m - l + 1))
		left[stat.i] = arr[l + stat.i];
	while (++stat.j < (r - m))
		right[stat.j] = arr[m + 1 + stat.j];
	stat.i = 0;
	stat.j = 0;
	stat.k = l;
	while (stat.i < (m - l + 1) && stat.j < (r - m))
	{
		if (left[stat.i] <= right[stat.j])
			arr[stat.k] = left[stat.i++];
		else
			arr[stat.k] = right[stat.j++];
		stat.k++;
	}
	while (stat.i < (m - l + 1))
		arr[stat.k++] = left[stat.i++];
	while (stat.j < (r - m))
		arr[stat.k++] = right[stat.j++];
}

void			ft_mergesort(int array[], int min, int max)
{
	int	middle;

	if (min < max)
	{
		middle = min + ((max - min) / 2);
		ft_mergesort(array, min, middle);
		ft_mergesort(array, middle + 1, max);
		merge(array, min, middle, max);
	}
}
