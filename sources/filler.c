/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 12:49:06 by jjuntune          #+#    #+#             */
/*   Updated: 2022/04/02 18:07:03 by manuelbeele      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

static void	ft_assign_character_to_player(t_filler *f)
{
	if (f->p_num == 1)
	{
		f->p_char = 'o';
		f->o_char = 'x';
	}
	else
	{
		f->p_char = 'x';
		f->o_char = 'o';
	}
}

static int	ft_setup_map(t_filler *f)
{
	char	*line;
	int		i;

	get_next_line(0, &line);
	if (ft_strncmp(line, "Plateau ", 8) || *(line + 8) < '0'
		|| *(line + 8) > '9')
	{
		ft_strdel(&line);
		return (0);
	}
	f->size_y = ft_atoi(line + 8);
	i = 1;
	while (line[8 + i] >= '0' && line[8 + i] <= '9')
		i++;
	if (*(line + 9 + i) < '0' || *(line + 9 + i) > '9')
	{
		ft_strdel(&line);
		return (0);
	}
	f->size_x = ft_atoi(line + 9 + i);
	ft_strdel(&line);
	f->map = ft_strnew(f->size_x * f->size_y);
	f->heat = (t_u32 *)malloc(sizeof(t_u32) * f->size_x * f->size_y);
	ft_memset(f->map, '.', f->size_x * f->size_y);
	return (1);
}

int	main(void)
{
	t_filler	f;
	char		*line;
	int			valid_solution;

	if (get_next_line(0, &line) == -1 || !line[10]
		|| ft_strncmp("$$$ exec p", line, 10)
		|| ft_strncmp(" : [", line + 11, 4)
		|| !ft_strstr(line, "mbeeler.filler")
		|| (line[10] != '1' && line[10] != '2'))
	{
		ft_strdel(&line);
		return (1);
	}
	f.p_num = line[10] - '0';
	ft_strdel(&line);
	if (!ft_setup_map(&f))
		return (1);
	ft_assign_character_to_player(&f);
	valid_solution = 1;
	while (valid_solution)
		ft_read_input(f, &valid_solution);
	ft_strdel(&f.map);
	free(f.heat);
	return (0);
}
