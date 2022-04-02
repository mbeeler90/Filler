/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_heat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:49:06 by jjuntune          #+#    #+#             */
/*   Updated: 2022/04/02 17:44:48 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

static int	ft_build_heat(t_filler *f, int j, int heat)
{
	int	changes;

	changes = 0;
	if (j % f->size_x > 0 && j / f->size_x > 0
		&& f->heat[j - f->size_x - 1] == MAX_U32 && ++changes)
		f->heat[j - f->size_x - 1] = heat;
	if (j / f->size_x > 0 && f->heat[j - f->size_x] == MAX_U32 && ++changes)
		f->heat[j - f->size_x] = heat;
	if (j % f->size_x < f->size_x - 1 && j / f->size_x > 0
		&& f->heat[j - f->size_x + 1] == MAX_U32 && ++changes)
		f->heat[j - f->size_x + 1] = heat;
	if (j % f->size_x > 0 && f->heat[j - 1] == MAX_U32 && ++changes)
		f->heat[j - 1] = heat;
	if (j % f->size_x < f->size_x - 1 && f->heat[j + 1] == MAX_U32 && ++changes)
		f->heat[j + 1] = heat;
	if (j % f->size_x > 0 && j / f->size_x < f->size_y - 1
		&& f->heat[j + f->size_x - 1] == MAX_U32 && ++changes)
		f->heat[j + f->size_x - 1] = heat;
	if (j / f->size_x < f->size_y - 1 && f->heat[j + f->size_x] == MAX_U32
		&& ++changes)
		f->heat[j + f->size_x] = heat;
	if (j % f->size_x < f->size_x - 1 && j / f->size_x < f->size_y - 1
		&& f->heat[j + f->size_x + 1] == MAX_U32 && ++changes)
		f->heat[j + f->size_x + 1] = heat;
	return (changes);
}

static void	ft_compare_heat_map(t_filler *f, int *i)
{
	int	j;

	j = -1;
	while (++j < f->size_x * f->size_y)
	{
		if (f->map[j] == f->o_char)
		{
			*i += 1;
			f->heat[j] = 0;
		}
		else
			f->heat[j] = MAX_U32;
	}
}

void	ft_get_heat(t_filler *f)
{
	int		i;
	int		j;
	int		heat;
	int		end;

	i = 0;
	heat = 1;
	end = 0;
	ft_compare_heat_map(f, &i);
	while (i < f->size_x * f->size_y && !end)
	{
		j = -1;
		while (++j < f->size_x * f->size_y)
		{
			if (f->heat[j] == heat - 1)
				i += ft_build_heat(f, j, heat);
		}
		if (heat < MAX_U32 - 1)
			heat++;
		else
			end = 1;
	}
}
