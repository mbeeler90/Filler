/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:49:06 by jjuntune          #+#    #+#             */
/*   Updated: 2022/10/20 15:55:31 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

/*
** Function to copy the shape of the piece from the input to a structure.
*/
static void	ft_copy_piece(t_filler *f)
{
	int		i;
	char	*line;

	i = -1;
	f->piece = ft_strdup("");
	while (++i < f->piece_y)
	{
		get_next_line(0, &line);
		ft_strjoin_inplace(&f->piece, &line);
	}
}

/*
** Function to get the size and shape of the piece that needs to be placed.
*/
static int	ft_get_piece(t_filler *f)
{
	int		i;
	int		error;
	char	*line;

	error = 0;
	get_next_line(0, &line);
	if (ft_strncmp(line, "Piece ", 6) || *(line + 6) < '0' || *(line + 6) > '9')
		error = 1;
	f->piece_y = ft_atoi(line + 6);
	i = 1;
	while (line[6 + i] >= '0' && line[6 + i] <= '9')
		i++;
	if (*(line + 6 + i + 1) < '0' || *(line + 6 + i + 1) > '9')
		error = 1;
	f->piece_x = ft_atoi(line + 6 + i);
	ft_strdel(&line);
	if (error)
		return (0);
	ft_copy_piece(f);
	return (1);
}

/*
** Function to check that map only contains valid characters.
*/
static int	ft_check_map(t_filler *f, char *line)
{
	int		line_len;
	t_u32	i;

	line_len = -1;
	i = 0;
	while (++line_len < f->size_x)
	{
		if (*(line + line_len + 4) == f->p_char - 32
			|| *(line + line_len + 4) == f->o_char - 32
			|| *(line + line_len + 4) == '.')
			i++;
	}
	if (i == f->size_x)
		return (1);
	else
		return (0);
}

/*
** Function to update the map to include the last placed piece of the opponent.
*/
static int	ft_update_map(t_filler *f)
{
	char	*line;
	int		n_lines;
	int		line_len;

	n_lines = -1;
	while (++n_lines < f->size_y)
	{
		get_next_line(0, &line);
		if (!ft_check_map(f, line))
		{
			ft_strdel(&line);
			return (0);
		}
		line_len = -1;
		while (++line_len < f->size_x)
		{
			if (*(line + line_len + 4) == f->p_char - 32)
				f->map[line_len + n_lines * f->size_x] = f->p_char;
			else if (*(line + line_len + 4) == f->o_char - 32)
				f->map[line_len + n_lines * f->size_x] = f->o_char;
		}
		ft_strdel(&line);
	}
	return (1);
}

/*
** Function to read the input in each round, update the map and call the
** functions to place the new piece.
*/
void	ft_read_input(t_filler f, int *valid_solution)
{
	char		*line;

	get_next_line(0, &line);
	ft_strdel(&line);
	if (!ft_update_map(&f) || !ft_get_piece(&f))
	{
		*valid_solution = 0;
		ft_printf("%d %d\n", -1, -1);
	}
	else
	{
		ft_get_heat(&f);
		ft_place_piece(&f);
		ft_strdel(&f.piece);
		ft_printf("%d %d\n", f.result[1], f.result[0]);
		if (f.result[1] == -1)
			*valid_solution = 0;
		else
		{
			get_next_line(0, &line);
			ft_strdel(&line);
		}
	}
}
