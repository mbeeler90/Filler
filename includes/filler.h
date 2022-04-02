/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:54:28 by jjuntune          #+#    #+#             */
/*   Updated: 2022/04/02 17:16:29 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "../libft/libft.h"
# define MAX_U32 0xFFFFFFFF

typedef struct s_filler
{
	char	p_num;
	char	p_char;
	char	o_char;
	int		size_x;
	int		size_y;
	char	*map;
	t_u32	*heat;
	int		piece_x;
	int		piece_y;
	char	*piece;
	int		result[2];
	int		min_heat;
}	t_filler;

void	ft_read_input(t_filler f, int *valid_solution);
void	ft_get_heat(t_filler *f);
void	ft_place_piece(t_filler *f);

#endif
