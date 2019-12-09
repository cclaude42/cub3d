/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:00:04 by cclaude           #+#    #+#             */
/*   Updated: 2019/12/09 20:09:54 by cclaude          ###   ########.fr       */
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
	s->map.tab[3][6] = '1';
	s->map.tab[3][3] = '1';
	s->map.tab[7][2] = '1';
	s->map.tab[7][7] = '1';
	s->map.x = MAPSIZE;
	s->map.y = MAPSIZE;
}

void	ft_init(t_all *s)
{
	s->mlx.ptr = mlx_init();
	s->win.x = 1080;
	s->win.y = 720;
	s->win.ptr = mlx_new_window(s->mlx.ptr, s->win.x, s->win.y, "cub3d");
	s->pos.x = 7.12;
	s->pos.y = 7.12;
	s->dir.x = cos(45 * M_PI / 180);
	s->dir.y = sin(45 * M_PI / 180);
	map_fill(s);
}

void	ft_cubed(t_all s)
{
	t_map	map;
	t_pos	pos;
	t_dir	dir;

	s.map = map;
	s.pos = pos;
	s.dir = dir;
	ft_init(&s);
	ft_screen(&s);
	mlx_hook(s.win.ptr, 2, 0, ft_key, &s);
	mlx_loop(s.mlx.ptr);
}

int		main(void)
{
	t_all	s;
	t_mlx	mlx;
	t_win	win;
	t_img	img;

	s.mlx = mlx;
	s.win = win;
	s.img = img;
	ft_cubed(s);
	return (0);
}
