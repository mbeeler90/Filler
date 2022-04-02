/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_place_piece.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:49:06 by jjuntune          #+#    #+#             */
/*   Updated: 2022/04/02 17:45:25 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

static void	ft_find_lowest_heat(t_filler *f, int pos)
{
	int	piece;

	piece = -1;
	while (++piece < f->piece_x * f->piece_y)
	{
		if (*(f->piece + piece) != '.'
			&& *(f->heat + pos + piece) < f->min_heat)
		{
			f->min_heat = *(f->heat + pos + piece);
			f->result[0] = pos % f->size_x;
			f->result[1] = pos / f->size_x;
		}
	}
}

static void	ft_try_to_make_it_fit(t_filler *f, int pos)
{
	int		piece;
	char	overlap;
	char	crash;
	char	position;

	piece = -1;
	crash = 0;
	overlap = 0;
	while (++piece < f->piece_x * f->piece_y)
	{
		position = *(f->map + pos + piece % f->piece_x + f->size_x
				* (piece / f->piece_x));
		if (position == f->o_char && *(f->piece + piece) != '.')
			crash++;
		else if (position == f->p_char && *(f->piece + piece) != '.')
			overlap++;
	}
	if (overlap == 1 && !crash)
		ft_find_lowest_heat(f, pos);
}

void	ft_place_piece(t_filler *f)
{
	int		pos;

	f->min_heat = MAX_U32;
	pos = -1;
	f->result[0] = -1;
	f->result[1] = -1;
	while (++pos < f->size_y * f->size_x)
	{
		if (f->piece_x + pos % f->size_x <= f->size_x
			&& f->piece_y + pos / f->size_x <= f->size_y)
			ft_try_to_make_it_fit(f, pos);
	}
}
