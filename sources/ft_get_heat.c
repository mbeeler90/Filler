/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_heat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:49:06 by jjuntune          #+#    #+#             */
/*   Updated: 2022/10/20 16:09:56 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

/*
** This function assigns the value on x + 1 to the fields next to the filed
** with the value x (if the value of the field to be changed is MAX_U32).
*/
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

/*
** Set heat map value to 0 for fields which are occupied by a piece of the
** opponent, set an initial value of MAX_U32 otherwise.
*/
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

/*
** Make a heat map with the same size as the solution map. On each empty field,
** the heat map shows the distance to the closest piece of the opponent.
** The heat map gets values of 0 for places which are occupied by pieces of the
** opponent. First, pieces next to those get a value of 1 (unless they are 0),
** next, the pieces next to the 1s get a value of 2 (unless they are 0 or 1).
** This is repeated until all fields got a value.
*/
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
