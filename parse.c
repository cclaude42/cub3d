/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 23:01:17 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/11 18:19:09 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_fill(t_all *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < MAPSIZE)
	{
		while (j < MAPSIZE)
		{
			if (i == 0 || i == MAPSIZE - 1 || j == 0 || j == MAPSIZE - 1)
				s->map.tab[i][j] = '1';
			else
				s->map.tab[i][j] = '0';
			j++;
		}
		i++;
		j = 0;
	}
	s->map.tab[5][5] = 'E';
	s->map.tab[3][6] = '1';
	s->map.tab[3][3] = '1';
	s->map.tab[7][2] = '1';
	s->map.tab[7][7] = '1';
	s->map.x = MAPSIZE;
	s->map.y = MAPSIZE;
}

void	ft_parse(t_all *s)
{
	s->win.x = 1080;
	s->win.y = 720;
	map_fill(s);
}
